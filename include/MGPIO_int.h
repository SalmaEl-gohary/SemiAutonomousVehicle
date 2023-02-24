#ifndef MGPIO_int
#define MGPIO_int


/**********************************************************************/
/*							GPIOA NAME								  */
/**********************************************************************/

typedef enum
{
	MGPIOA_REG,
	MGPIOB_REG,
	MGPIOC_REG
}PORT_t;

/**********************************************************************/
/*							GPIOA PINS								  */
/**********************************************************************/

typedef enum
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}PIN_t;

/**********************************************************************/
/*							SPEED_NAME								  */
/**********************************************************************/

typedef enum
{
	MGPIO_SPEED_LOW,
	MGPIO_SPEED_MID,
	MGPIO_SPEED_HIGH,
	MGPIO_SPEED_VHIGH
}SPEED_t;

/**********************************************************************/
/*							PIN_MODE								  */
/**********************************************************************/

typedef enum
{
	MGPIO_PIN_INPUT,
	MGPIO_PIN_OUTPUT,
	MGPIO_PIN_ALTFN,
	MGPIO_PIN_ANALOG
}MODE_t;

/**********************************************************************/
/*							OUTPUT_MODE								  */
/**********************************************************************/

typedef enum
{
	MGPIO_PUSH_PULL,
	MGPIO_OPEN_DRAIN
}OutputType_t;

/**********************************************************************/
/*							PULL_MODE								  */
/**********************************************************************/

typedef enum
{
	MGPIO_PIN_FLOAT,
	MGPIO_PIN_PULLUP,
	MGPIO_PIN_PULLDOWN
}PULL_t;

/**********************************************************************/
/*							PIN_VALUE								  */
/**********************************************************************/

#define MGPIO_PIN_HIGH		1
#define MGPIO_PIN_LOW		0

#define FIRST_HALF			0
#define LAST_HALF			1

/**********************************************************************/
/*							ALT FN         							  */
/**********************************************************************/

typedef enum
{
	AF0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}ALT_t;

#define AFR_H		0
#define AFR_L		1

/*####################################################################*/
/*						FUNCTION PROTOTYPES							  */
/*####################################################################*/


/***********************************************************************************/
/*                         04- MGPIO_vidSetPinMode()                    		   */
/*-------------------------------------------------------------------------------- */
/* @fu MGPIO_vidSetPinMode                                 						   */
/* @brief  This Function used to set pin mode									   */
/* 				- INPUT															   */
/* 				- OUTPUT														   */
/* 				- ALTF															   */
/* 				- ANALOG	          								    		   */
/* @param[in] Copy_uddtPortNum: The port of the pin								   */
/* 			  [MGPIOA_REG, MGPIOB_REG, MGPIOC_REG] Detect required register  	   */
/* @param[in] Copy_uddtPinNum: the Pin number									   */
/* 		      [PIN0: PIN15]														   */
/* @param[in] Copy_uddtPinMode:  												   */
/* 			  [MGPIO_PIN_INPUT, MGPIO_PIN_OUTPUT, MGPIO_PIN_ALTF, MGPIO_PIN_ANALOG]*/
/***********************************************************************************/

void MGPIO_vidSetPinMode(PORT_t Copy_uddtPortNum, PIN_t Copy_uddtPinNum, MODE_t Copy_uddtPinMode);

void MGPIO_vidSetOutputType(PORT_t Copy_uddtPortNum, PIN_t Copy_uddtPinNum, OutputType_t Copy_uddtOutputType);

void MGPIO_vidSetOutputSpeed(PORT_t Copy_uddtPortNum, PIN_t Copy_uddtPinNum, SPEED_t Copy_uddtSpeed);

void MGPIO_vidSetPinPullType(PORT_t Copy_uddtPortNum, PIN_t Copy_uddtPinNum, PULL_t Copy_uddtPullType);

void MGPIO_vidSetPinValue(PORT_t Copy_uddtPortNum, PIN_t Copy_uddtPinNum, u8 Copy_u8Value);

u8 MGPIO_u8GetPinValue(PORT_t Copy_uddtPortNum, PIN_t Copy_uddtPinNum);

void MGPIO_vidSetPortValue(PORT_t Copy_uddtPortNum, u32 Copy_u32Value);

void MGPIO_vidSetPortMode(PORT_t Copy_uddtPortNum,  u32 Copy_u32Value);

void MGPIO_vidChangePortValue(PORT_t Copy_uddtPortNum, u32 Copy_u32Value);

void MGPIO_voidSetPinAltFn( u8 Copy_u8PortNum ,u8 Copy_u8PinNum, u8 Copy_u8ALF );




#endif
