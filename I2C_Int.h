
#ifndef I2C_INT_H_
#define I2C_INT_H_


#define I2C_WRITE_BIT_RATE(value)					(TWBR=value)	
#define I2C_ENABLE_ACK_BIT()						(SET_BIT(TWCR,TWEA))
#define I2C_DISABLE_ACK_BIT()						(CLR_BIT(TWCR,TWEA))
#define I2C_CLEAR_INTERRUPT_FLAG()					(SET_BIT(TWCR,TWINT))
#define I2C_INTERRUPT_ENABLE()						(SET_BIT(TWCR,TWIE))
#define I2C_INTERRUPT_DISABLE()						(CLR_BIT(TWCR,TWIE))
#define I2C_ENABLE_START_CONDITION()				(SET_BIT(TWCR,TWSTA))
#define I2C_DISABLE_START_CONDITION()				(CLR_BIT(TWCR,TWSTA))
#define I2C_ENABLE_STOP_CONDITION()					(SET_BIT(TWCR,TWSTO))
#define I2C_DISABLE_STOP_CONDITION()				(CLR_BIT(TWCR,TWSTO))
#define I2C_ENABLE_COMMUNICATION_PROTOCOL()			(SET_BIT(TWCR,TWEN))
#define I2C_DISABLE_COMMUNICATION_PROTOCOL()		(CLR_BIT(TWCR,TWEN))
#define I2C_WRITE_DATA(data)						(TWDR = data)
#define I2C_READ_DATA(pdata)						(*pdata=TWDR)
#define I2C_RECONAGIZE_GENERAL_CALL()				(SET_BIT(TWAR,TWGCE))
#define I2C_IGNORE_GENERAL_CALL()					(CLR_BIT(TWAR,TWGCE))
#define I2C_WRITE_SLAVE_ADDRESS(add)				((TWAR)|=(((add)&&(0x7F))<<1))

/*********************************************************************************/

/* Status Register Values */

/* Master Send Commands */
#define MASTER_START_COMMAND												0x08
#define MASTER_REPEATED_START_COMMAND										0x10
#define MASTER_ADDRESS_SENT_WRITE_ACK_RECEIVED_COMMAND						0x18
#define MASTER_ADDRESS_SENT_WRITE_NO_ACK_RECEIVED_COMMAND					0x20
#define MASTER_DATA_TRANS_WRITE_ACK_RECEIVED_COMMAND						0x28
#define MASTER_DATA_TRANS_WRITE_NO_ACK_RECEIVED_COMMAND						0x30
#define ARIBTRIATION_LOST_COMMAND											0x38
/* Master Receive Commands */
#define MASTER_ADDRESS_SENT_READ_ACK_RECEIVED_COMMAND						0x40
#define MASTER_ADDRESS_SENT_READ_NO_ACK_RECEIVED_COMMAND					0x48
#define MASTER_DATA_RECEIVED_READ_ACK_RETURNED_COMMAND						0x50
#define MASTER_DATA_RECEIVED_READ_NO_ACK_RETURNED_COMMAND					0x58
/* Slave Receive Commands */
/* Write Request From Master */
#define SLAVE_ADDRESS_READ_RECEIVED_ACK_RETURNED_COMMAND					0x60
#define SLAVE_ADDRESS_READ_RECEIVED_NO_ACK_RETURNED_COMMAND				    0x68
#define SLAVE_GENERAL_CALL_RECEIVED_ACK_RETURNED_COMMAND					0x70
#define SLAVE_ARBITRATION_SLAW_LOST_ACK_RETURNED							0x78
/* Byte is Received */
#define SLAVE_PERVIOUSLY_READ_ADDRESSED_ACK_RETURNED						0x80
#define SLAVE_PERVIOUSLY_READ_ADDRESSED_NO_ACK_RETURNED						0x88
#define SLAVE_PERVIOUSLY_ADDRESSED_GENERAL_CALL_ACK_RETURNED				0x90
#define SLAVE_STOP_OR_REPEATED_CODITION_RECEIVED							0xA0
/* Slave Send Commands */
/* Read request From Master */
#define SLAVE_WRITE_ACK_RETURNED_COMMAND									0xA8
#define SLAVE_ARBITRATION_SLAR_RECEIVED_LOST_ACK_RETURNED					0xB0
/* Data Transmitted */					
#define SLAVE_DATA_TRANSMITTED_ACK_RECEIVED									0xB8
#define SLAVE_DATA_TRANSMITTED_NO_ACK_RECEIVED								0xC0
#define SLAVE_LAST_DATA_TRANSMITTED_ACK_RECEIVED							0xC8
#define SLAVE_STOP_OR_REPEATED_CODITION_RECEIVED							0xA0
/* General Commands */
#define NO_RELEVANT_STATE_AVAILABLE											0xF8
#define BUS_ERROR_ILLEGAL_CONDITION											0x00	

/*********************************************************************************/




typedef enum 
{
	I2C_PRESCALER_1 = 0 ,
	I2C_PRESCALER_4,
	I2C_PRESCALER_16,
	I2C_PRESCALER_64
}I2C_prescaler_t;

typedef enum 
{
	MASTER_WRITE = 0 , 
	MASTER_READ = 1
}master_tranmit_state_t;

#define GENERAL_CALL_ON				1
#define GENERAL_CALL_OFF			0
#define GENERAL_CALL_CHOICE			GENERAL_CALL_OFF

#define SCALER_VAL			I2C_PRESCALER_4
#define CONSTANT_VAL		((u8)4)
#define I2C_SLAVE_ADDRESS		0x05

typedef enum 
{
	I2C_OK ,
	I2C_START_CONDITION_ERROR ,
	I2C_REPEATED_START_CONDITION_ERROR,
	I2C_MASTER_ADDRESS_WRITE_ACK_ERROR ,
	I2C_MASTER_ADDRESS_READ_ACK_ERROR ,
	I2C_MASTER_DATA_WRITE_ERROR,
	I2C_MASTER_DATA_READ_ERROR	,
	I2C_SLAVE_WRITE_ERROR,
	I2C_SLAVE_READ_ERROR
}i2c_error_t;

/* APIS */

void I2C_Init(void);

i2c_error_t I2C_Master_Start_Condition(void) ;
i2c_error_t I2C_Repeated_Start_Condition(void) ;
void I2C_Master_Stop_Condition(void);

void I2C_Master_Gen_Clk_Val_KHZ(u16 freq_KHZ);
void I2C_Master_Gen_Clk_Val_HZ(u16 freq_HZ);

i2c_error_t I2C_Master_Select_Slave_address (u8 slave_addr , master_tranmit_state_t mode) ;
i2c_error_t I2C_Master_Write_Data(u8 data) ;
u8 I2C_Read_Status_val (void);
i2c_error_t I2C_Master_Read_Val (u8 *pdata);

i2c_error_t I2C_Slave_Write_Data (u8 copyu8_data );
i2c_error_t I2C_Slave_Read_Data (u8* copypu8_pdata );

void I2C_Set_Call_Back (void (*pf)(void));

#endif /* I2C_INT_H_ */