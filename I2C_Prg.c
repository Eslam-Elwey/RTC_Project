
#include "Std_Types.h"
#include "Bit_Math.h"
#include "MemMap.h"
#include "I2C_Int.h"
#define F_CPU		16000000UL
#include <util/delay.h>


static u16 pow_func (u8 num , u8 pow);
static void (*I2C_PF)(void)= NULLPTR ;

static u16 pow_func (u8 num , u8 pow)
{
	u16 res = 1 ;
	for (u8 i=0 ;i<pow ;i++)
	{
		res *= num ;
	}
	return res ;
}


void I2C_Master_Gen_Clk_Val_HZ(u16 freq_HZ)
{
	/* Scaler */
	TWSR &= 0xFC ;
	TWSR |= SCALER_VAL ;
	
	u16 pow_val = pow_func (CONSTANT_VAL,SCALER_VAL);
	
	TWBR =(u8) (((u32)F_CPU/freq_HZ) - 16) /((u16)2*pow_val) ;
}

void I2C_Master_Gen_Clk_Val_KHZ(u16 freq_KHZ)
{
	/* Scaler */
	TWSR &= 0xFC ;
	TWSR |= SCALER_VAL ;
	
	u16 pow_val = pow_func (CONSTANT_VAL,SCALER_VAL);
	
	TWBR =(u8) (((u32)F_CPU/((u32)freq_KHZ*1000)) - 16) /((u16)2*pow_val) ; 
}

void I2C_Init(void)
{
	I2C_Master_Gen_Clk_Val_HZ(9600);
	/* General Call Response */
#if GENERAL_CALL_CHOICE == GENERAL_CALL_ON
	I2C_RECONAGIZE_GENERAL_CALL() ;
#else 
	I2C_IGNORE_GENERAL_CALL() ;
#endif
	/*Enable Acknowledge Bit */
	I2C_ENABLE_ACK_BIT();
	/*Customize Slave Address */
	u8 address = I2C_SLAVE_ADDRESS ;
	for (u8 i=0;i<7;i++)
	{
		WRITE_BIT_VAL(TWAR,i+1,(READ_BIT(address,i)));
	}
	/* Enable I2C */
	I2C_ENABLE_COMMUNICATION_PROTOCOL() ;
}


i2c_error_t I2C_Master_Start_Condition(void)
{
	i2c_error_t ret_val = I2C_OK ;
	
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)|(1<<TWEA);
	while(READ_BIT(TWCR,TWINT)==0);
	if (I2C_Read_Status_val()!=MASTER_START_COMMAND)
	{
		ret_val = I2C_START_CONDITION_ERROR ;
	}
	return ret_val ;
}

i2c_error_t I2C_Repeated_Start_Condition(void)
{
	i2c_error_t ret_val = I2C_OK ;
	
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)|(1<<TWEA);
	
	while(READ_BIT(TWCR,TWINT)==0);
	
	if (I2C_Read_Status_val()!=MASTER_REPEATED_START_COMMAND)
	{
		ret_val = I2C_REPEATED_START_CONDITION_ERROR ;
	}
	
	return ret_val ;
}


void I2C_Master_Stop_Condition(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

u8 I2C_Read_Status_val (void)
{
	return (TWSR&0xF8) ;
}

i2c_error_t I2C_Master_Write_Data(u8 data)
{
	i2c_error_t ret_val = I2C_OK ;
	
	TWDR = data ;
	
	I2C_DISABLE_START_CONDITION();
	
	TWCR = (1<<TWINT) | (1<<TWEN) ;
	
	while(READ_BIT(TWCR,TWINT)==0);
	
	if (I2C_Read_Status_val()!=MASTER_DATA_TRANS_WRITE_ACK_RECEIVED_COMMAND)
	{
		ret_val = I2C_MASTER_DATA_WRITE_ERROR ;
	}
	
	return ret_val ;
}


i2c_error_t I2C_Master_Read_Val (u8 *pdata)
{
	i2c_error_t ret_val = I2C_OK ;
	
	I2C_DISABLE_START_CONDITION();
	
	TWCR = (1<<TWINT) | (1<<TWEN)|(1<<TWEA) ;
	
	while(READ_BIT(TWCR,TWINT)==0);
	
	if (I2C_Read_Status_val()!=MASTER_DATA_RECEIVED_READ_ACK_RETURNED_COMMAND)
	{
		ret_val = I2C_MASTER_DATA_READ_ERROR ;
	}
	else 
	{
		*pdata = TWDR ;
	}
	
	
	
	return ret_val ;
}


i2c_error_t I2C_Master_Select_Slave_address (u8 slave_addr , master_tranmit_state_t mode) 
{
	i2c_error_t ret_val = I2C_OK ;

	slave_addr &= 0x7F ;
	slave_addr <<= 1 ;
	if (mode==MASTER_READ)
	{
		slave_addr |= 0x01 ;
	}
	else 
	{
		slave_addr &= 0xFE ;
	}
	
	TWDR = slave_addr ;
	
	I2C_DISABLE_START_CONDITION();
	
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	while(READ_BIT(TWCR,TWINT)==0);
	
	
	if (mode==MASTER_READ)
	{
		if (I2C_Read_Status_val()!=MASTER_ADDRESS_SENT_READ_ACK_RECEIVED_COMMAND)
		{
			ret_val = I2C_MASTER_ADDRESS_READ_ACK_ERROR ;
		}
		
	}
	else
	{
		if (I2C_Read_Status_val()!=MASTER_ADDRESS_SENT_WRITE_ACK_RECEIVED_COMMAND)
		{
			ret_val = I2C_MASTER_ADDRESS_WRITE_ACK_ERROR ;
		}
	}
	
	
	return ret_val ;
	
}





void I2C_Set_Call_Back (void (*pf)(void))
{
	I2C_PF = pf ;
}

ISR (TWI_vect)
{
	if (I2C_PF!=NULLPTR)
	{
		I2C_PF() ;
	}
}

i2c_error_t I2C_Slave_Write_Data (u8 copyu8_data )
{
	i2c_error_t ret_val = I2C_OK ;
	
	TWDR = copyu8_data ;
	
	TWCR = (1<<TWINT) | (1<<TWEN) ;
	
	while(READ_BIT(TWCR,TWINT)==0);
	
	if (I2C_Read_Status_val()!=SLAVE_DATA_TRANSMITTED_ACK_RECEIVED)
	{
		ret_val = I2C_SLAVE_WRITE_ERROR ;
	}
	
	return ret_val ;
}


i2c_error_t I2C_Slave_Read_Data (u8* copypu8_pdata )
{
	i2c_error_t ret_val = I2C_OK ;
	
	TWCR = (1<<TWINT) | (1<<TWEN) ;
	
	while(READ_BIT(TWCR,TWINT)==0);
	
	if (I2C_Read_Status_val()!=SLAVE_ADDRESS_READ_RECEIVED_ACK_RETURNED_COMMAND)
	{
		ret_val = I2C_SLAVE_READ_ERROR ;
	}
	
	TWCR = (1<<TWINT) | (1<<TWEN) ;
	
	while(READ_BIT(TWCR,TWINT)==0);
	
	if (I2C_Read_Status_val()!=SLAVE_PERVIOUSLY_READ_ADDRESSED_ACK_RETURNED)
	{
		ret_val = I2C_SLAVE_READ_ERROR ;
	}
	else
	{
		*copypu8_pdata = TWDR ;
	}
	
	
	
	return ret_val ;
}