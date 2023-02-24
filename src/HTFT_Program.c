

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"

#include "MGPIO_int.h"
#include "MSPI_Interface.h"
#include "MSTK_int.h"

#include "HTFT_Interface.h"
#include "HTFT_Private.h"
#include "HTFT_Config.h"

u16 D[]={0, 0, 8184, 16380, 24582, 49155, 49155, 49155, 49155, 49155, 49155, 65535, 65535, 0, 0};
u16 I[]={0, 0, 0, 49155, 49155, 49155, 65535, 65535, 65535, 49155, 49155, 49155, 0, 0, 0};
u16 S[]={0, 0, 0, 4156, 8318, 24710, 24710, 24710, 24710, 16134, 7680, 0, 0, 0, 0};
u16 T[]={0, 0, 24576, 24576, 24576, 24576, 32767, 32767, 32767, 24576, 24576, 24576, 24576, 0, 0};
u16 A[]={0, 0, 8190, 16382, 25344, 25344, 25344, 25344, 25344, 25344, 16382, 8190, 0, 0, 0};
u16 E[]={0, 0, 24582, 24966, 24966, 24966, 24966, 24966, 24966, 24966, 32766, 32766, 0, 0, 0};
u16 P[]={0, 0, 0, 7936, 16128, 24960, 24960, 24960, 24960, 24960, 24960, 16382, 8190, 0, 0};
u16 C[]={0, 0, 0, 0, 2064, 12300, 12300, 12300, 12300, 12300, 16380, 8176, 0, 0, 0};
u16 N[]={32766, 32766, 28, 56, 112, 224, 448, 896, 1792, 3584, 7168, 6144, 28672, 32766, 32766};
u16 R[]={0, 0, 0, 15366, 32270, 25116, 25144, 25200, 25312, 25536, 25472, 32766, 32766, 0, 0};
u16 M[]={0, 16382, 32766, 24576, 24576, 24576, 24576, 16382, 24576, 24576, 24576, 24576, 32766, 16382, 0};
u16 L[]={0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 32766, 32766, 0};
u16 V[]={4096, 6144, 3072, 1536, 768, 384, 192, 96, 192, 384, 768, 1536, 3072, 6144, 4096};


//NUMBERS*********************************************/
u16 zero[]={0, 0, 0, 2032, 4088, 6156, 12294, 12294, 12294, 12294, 6156, 4088, 2032, 0, 0};
u16 one[]={0, 0, 0, 0, 0, 6, 6, 32766, 32766, 24582, 16390, 0, 0, 0, 0};
u16 two[]={0, 0, 0, 7936, 16134, 24710, 24710, 24710, 24710, 24828, 8316, 4096, 0, 0, 0};
u16 three[]={0, 0, 0, 16380, 32766, 24966, 24966, 24966, 24966, 24966, 8196, 4104, 0, 0, 0};
u16 four[]={0, 0, 0, 0, 32764, 32764, 768, 768, 768, 768, 768, 32512, 32512, 0, 0};
u16 five[]={0, 0, 0, 0, 25086, 25086, 24966, 24966, 24966, 24966, 32646, 32646, 0, 0, 0};

u16 six[]={0, 0, 0, 24830, 24830, 24774, 24774, 24774, 24774, 24774, 32766, 32766, 0, 0, 0};
u16 seven[]={0, 0, 30720, 27648, 26112, 25344, 24960, 24768, 24672, 24624, 24600, 24588, 24580, 0, 0};
u16 eight[]={0, 0, 0, 0, 7280, 14040, 25228, 16644, 25228, 14040, 7280, 0, 0, 0, 0};
u16 nine[]={0, 0, 0, 32766, 32766, 25350, 25350, 25350, 25350, 25350, 32518, 32518, 0, 0, 0};
u16 *numbers[]={
		zero,one,two,three,four,five,six,seven,eight,nine
};


void HTFT_voidInitialize   (void)
{
	/* Reset Pulse */
	MGPIO_vidSetPinValue(TFT_RST_PIN,MGPIO_PIN_HIGH);
	MSTK_voidDelayMs(100);
	MGPIO_vidSetPinValue(TFT_RST_PIN,MGPIO_PIN_LOW);
	MSTK_voidDelayMs(1);
	MGPIO_vidSetPinValue(TFT_RST_PIN,MGPIO_PIN_HIGH);
	MSTK_voidDelayMs(100);
	MGPIO_vidSetPinValue(TFT_RST_PIN,MGPIO_PIN_LOW);
	MSTK_voidDelayMs(100);
	MGPIO_vidSetPinValue(TFT_RST_PIN,MGPIO_PIN_HIGH);
	MSTK_voidDelayMs(120000);

	/* Sleep Out Command */
	voidWriteCommand(0x11);

	/* Wait 150 ms */
	MSTK_voidDelayMs(150000);
	/* Color Mode Command */
	voidWriteCommand(0x3A);
	voidWriteData   (0x05);

	/* Display On Command */
	voidWriteCommand(0x29);
}

void HTFT_voidDrawRect (u8 x1,u8 x2,u8 y1,u8 y2,u16 Copy_u16color)
{
		u16 counter;
		u8 Data;
		u16 SIZE=(x2-x1)*(y2-y1);
		/* Set X Address */
		voidWriteCommand(0x2A);
		voidWriteData(0);
		voidWriteData(x1);
		voidWriteData(0);
		voidWriteData(x2);

		/* Set Y Address */
		voidWriteCommand(0x2B);
		voidWriteData(0);
		voidWriteData(y1);
		voidWriteData(0);
		voidWriteData(y2);

		/* RAM Write */
		voidWriteCommand(0x2C);

		for(counter = 0; counter< SIZE;counter++)
		{
			Data = Copy_u16color >> 8;

			/* Write the high byte */
			voidWriteData(Data);
			/* Write the low byte */
			Data = Copy_u16color & 0x00ff;
			voidWriteData(Data);
		}

}
void HTFT_voidDisplayImage (const u16* Copy_Image)
{
	u16 counter;
	u8 Data;

	/* Set X Address */
	voidWriteCommand(0x2A);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(127);

	/* Set Y Address */
	voidWriteCommand(0x2B);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(159);

	/* RAM Write */
	voidWriteCommand(0x2C);

	for(counter = 0; counter< 20480;counter++)
	{
		Data = Copy_Image[counter] >> 8;

		/* Write the MGPIO_PIN_HIGH byte */
		voidWriteData(Data);
		/* Write the MGPIO_PIN_LOW byte */
		Data = Copy_Image[counter] & 0x00ff;
		voidWriteData(Data);
	}


}

static void voidWriteCommand(u8 Copy_u8Command)
{

	/* Set A0 Pin to MGPIO_PIN_LOW */
	MGPIO_vidSetPinValue(TFT_A0_PIN,MGPIO_PIN_LOW);

	/* Send Command over SPI */
	MSPI2_voidSendDataU8(Copy_u8Command) ;
}

static void voidWriteData   (u8 Copy_u8Data)
{

	/* Set A0 Pin to MGPIO_PIN_HIGH */
	MGPIO_vidSetPinValue(TFT_A0_PIN,MGPIO_PIN_HIGH);

	/* Send data over SPI */
	MSPI2_voidSendDataU8(Copy_u8Data) ;
}

void TFT_VidWriteChar( u8 * Cop_u8Char , u8 Xaxis , u8 Yaxis , u16 Copy_u8Color ){

	u8  LOC_u8Mask = 0x80 ;
	u8  LOC_u8DataMasked  ;
	u16 LOC_u8Pixel       ;

	for( u8 LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 5 ; LOC_u8Iterator1++ ){//5

		for( u8 LOC_u8Iterator2 = 0 ; LOC_u8Iterator2 < 7 ; LOC_u8Iterator2++ ){//7

			/* Set The Position Of 5x7 Character */
			voidWriteCommand( CASET ); // set column range (x0,x1)

			voidWriteData( Xaxis +  LOC_u8Iterator1 );
			voidWriteData( Xaxis +  LOC_u8Iterator1 );

			voidWriteCommand( RASET ); // set row range (y0,y1)

			voidWriteData( Yaxis +  LOC_u8Iterator2 );
			voidWriteData( Yaxis +  LOC_u8Iterator2 );

			voidWriteCommand( RAMWR ); // memory write

			LOC_u8DataMasked = Cop_u8Char[ LOC_u8Iterator1 ] & LOC_u8Mask ;

			if( LOC_u8DataMasked == 0  ) { LOC_u8Pixel = 0x0000       ; }
			else                         { LOC_u8Pixel = Copy_u8Color ; }

			voidWriteData ( LOC_u8Pixel >> 8   ); // write hi byte
			voidWriteData ( LOC_u8Pixel & 0xFF ); // write lo byte

			LOC_u8Mask >>= 1 ;

		}

		LOC_u8Mask = 0x80 ;

	}

}

void TFT_VidFillColor ( u16 Copy_u16Color ) {

	u8 LOC_u8CountX ;
	u8 LOC_u8CountY ;

	for( LOC_u8CountY = 0 ; LOC_u8CountY < 160 ; LOC_u8CountY++ )
	{
		voidWriteCommand( CASET        ) ; // set column range (x0,x1)
		voidWriteData   ( 0            ) ;
		voidWriteData   ( 0            ) ;
		voidWriteCommand( RASET        ) ; // set row range (y0,y1)
		voidWriteData   ( 0            ) ;
		voidWriteData   ( LOC_u8CountY ) ;

		voidWriteCommand( RAMWR        ); // memory write

		for ( LOC_u8CountX = 0 ; LOC_u8CountX < 128 ; LOC_u8CountX++ )
		{
			voidWriteData ( Copy_u16Color >> 8   ) ; // write hi byte
			voidWriteData ( Copy_u16Color & 0xFF ) ; // write lo byte

		}
	}

}
void HTFT_VidWriteChar( u16 * Cop_u8Char , u8 Xaxis , u8 Yaxis , u16 Copy_u8Color ){

	u16  LOC_u8Mask = 0x01 ;
	u16  LOC_u8DataMasked  ;
	u16 LOC_u8Pixel       ;

	for( u8 LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 15 ; LOC_u8Iterator1++ ){

		for( u8 LOC_u8Iterator2 = 0 ; LOC_u8Iterator2 < 16 ; LOC_u8Iterator2++ ){

			/* Set The Position Of 5x7 Character */
			voidWriteCommand( 0x2A ); // set column range (x0,x1)

			voidWriteData( Xaxis +  LOC_u8Iterator1 );
			voidWriteData( Xaxis +  LOC_u8Iterator1 );

			voidWriteCommand( 0x2B ); // set row range (y0,y1)

			voidWriteData( Yaxis +  LOC_u8Iterator2 );
			voidWriteData( Yaxis +  LOC_u8Iterator2 );

			voidWriteCommand( 0x2C ); // memory write

			LOC_u8DataMasked = Cop_u8Char[ LOC_u8Iterator1 ] & LOC_u8Mask ;

			if( LOC_u8DataMasked == 0  ) { LOC_u8Pixel = 0x0000       ; }
			else                         { LOC_u8Pixel = Copy_u8Color ; }

			voidWriteData( LOC_u8Pixel >> 8   ); // write hi byte
			voidWriteData( LOC_u8Pixel & 0x00FF ); // write lo byte

			LOC_u8Mask <<= 1 ;

		}

		LOC_u8Mask = 0x01 ;
	}
}
void HTFT_vidSendNum(s32 num)
{
	u8 x=114;
	u8 y=122;
	TFT_VidFillColor(BLACK);
	HTFT_VidWriteChar ( S     , x , y+22 , GREEN     );
	HTFT_VidWriteChar ( P     , x-14 , y+22 , GREEN     );
	HTFT_VidWriteChar ( E     , x-28 , y+22 , GREEN     );
	HTFT_VidWriteChar ( E     , x-42 , y+22 , GREEN     );
	HTFT_VidWriteChar ( D     , x-56 , y+22 , GREEN     );

	u8 i=0,k;
	u8 s=112;
	u16 str[20];
	s8 j=0;
	if(num==0)
	{
		HTFT_VidWriteChar ( numbers[0]     , x  , 0 , 0x07FF);
		return ;
	}
	if(num<0)
	{
		//			HLCD_vidSendChar('-');
		//			num=num*-1;
	}
	while (num)
	{
		str[i]=num%10;
		num/=10;
		i++;
	}

	for(j=i-1;j>=0;j--)
	{
		for(k=0;k<10;k++)
		{
			if(str[j]==k)
			{
				HTFT_VidWriteChar ( numbers[k]     , s  , y , 0x07FF);
				s=s-15;
			}
		}
	}

}
/***********SPEED    x=112,y=122**************/
/***********Distance x=112,y=122**************/
/***********for speed z=0,and for distance z=1**************/

void HTFT_vidSendNumAdaptive(s32 num,s32 num1)
{
	u8 x=114;
	u8 y=122;
	u8 z=16;
	static u8 c=0;
	if(c==0){
	TFT_VidFillColor(BLACK);
	}
	HTFT_voidDrawRect (0, 128,122,144,BLACK);
	HTFT_voidDrawRect (0, 128,68, 90,BLACK);
	HTFT_VidWriteChar ( S     , x , y+22 , RED     );
	HTFT_VidWriteChar ( P     , x-14 , y+22 , RED     );
	HTFT_VidWriteChar ( E     , x-28 , y+22 , RED     );
	HTFT_VidWriteChar ( E     , x-42 , y+22 , RED     );
	HTFT_VidWriteChar ( D     , x-56 , y+22 , RED     );

	HTFT_VidWriteChar ( D     , x ,    90 , YELLOW     );
	HTFT_VidWriteChar ( I     , x-14 , 90 , YELLOW     );
	HTFT_VidWriteChar ( S     , x-28 , 90 , YELLOW     );
	HTFT_VidWriteChar ( T     , x-42 , 90 , YELLOW     );
	HTFT_VidWriteChar ( A     , x-56 , 90 , YELLOW     );
	HTFT_VidWriteChar ( N     , x-70 , 90 , YELLOW     );
	HTFT_VidWriteChar ( C     , x-84 , 90 , YELLOW     );
	HTFT_VidWriteChar ( E     , x-98 , 90 , YELLOW     );

	//HTFT_VidWriteChar ( S     , x-z ,    40 , YELLOW     );
	//HTFT_VidWriteChar ( S     , x-14-z , 40 , YELLOW     );
	//HTFT_VidWriteChar ( I     , x-28-z , 40 , YELLOW     );
	//HTFT_VidWriteChar ( T     , x-42-z , 40 , YELLOW     );
	//HTFT_VidWriteChar ( C     , x-56-z , 40 , YELLOW     );
	//HTFT_VidWriteChar ( S     , x-70-z , 40 , YELLOW     );
	//HTFT_VidWriteChar ( numbers[0]     , x  , 40 , 0x07FF);

	u8 i=0,k;
	u8 s=112;
	u16 str[10],str1[10];
	s8 j=0;
	if(num==0)
	{
		HTFT_VidWriteChar ( numbers[0]     , 114  , 122 , 0x07FF);
		//			return ;
	}
	if(num<0)
	{
		//			HLCD_vidSendChar('-');
		//			num=num*-1;
	}
	while (num)
	{
		str[i]=num%10;
		num/=10;
		i++;
	}

	for(j=i-1;j>=0;j--)
	{
		for(k=0;k<10;k++)
		{
			if(str[j]==k)
			{
				HTFT_VidWriteChar ( numbers[k]     , s  , y , 0x07FF);
				s=s-15;
			}
		}
	}
	/*************************DISTANCE************************/
	s=112;
	i=0;
	if(num1==0)
	{
		HTFT_VidWriteChar ( numbers[0]     , 114  , 68 , 0x07FF);
		//				return ;
	}
	if(num1<0)
	{
		//			HLCD_vidSendChar('-');
		//			num=num*-1;
	}
	while (num1)
	{
		str1[i]=num1%10;
		num1/=10;
		i++;
	}

	for(j=i-1;j>=0;j--)
	{
		for(k=0;k<10;k++)
		{
			if(str1[j]==k)
			{
				HTFT_VidWriteChar ( numbers[k]     , s  , 68 , 0x07FF);
				s=s-15;
			}
		}
	}
c=1;
}
void HTFT_vidSendNumDIST(s32 num)
{
	u8 x=112;
	TFT_VidFillColor(BLACK);
	HTFT_VidWriteChar ( D     , x ,    112 , GREEN     );
	HTFT_VidWriteChar ( I     , x-14 , 112 , GREEN     );
	HTFT_VidWriteChar ( S     , x-28 , 112 , GREEN     );
	HTFT_VidWriteChar ( T     , x-42 , 112 , GREEN     );
	HTFT_VidWriteChar ( A     , x-56 , 112 , GREEN     );
	HTFT_VidWriteChar ( N     , x-70 , 112 , GREEN     );
	HTFT_VidWriteChar ( C     , x-84 , 112 , GREEN     );
	HTFT_VidWriteChar ( E     , x-98 , 112 , GREEN     );

	u8 i=0,k;
	u8 s=112;
	u16 str[20];
	s8 j=0;
	if(num==0)
	{
		HTFT_VidWriteChar ( numbers[0]     , s  , 0 , 0x07FF);
		return ;
	}
	if(num<0)
	{
		//			HLCD_vidSendChar('-');
		//			num=num*-1;
	}
	while (num)
	{
		str[i]=num%10;
		num/=10;
		i++;
	}

	for(j=i-1;j>=0;j--)
	{
		for(k=0;k<10;k++)
		{
			if(str[j]==k)
			{
				HTFT_VidWriteChar ( numbers[k]     , s  , 96 , 0x07FF);
				s=s-15;
			}
		}
	}

}
void HTFT_vidPrintSpeedNormal(s32 num)
{
	u8 x=114;
	u8 y=122;
	u8 i=0,k;
	u8 s=112;
	u16 str[10],str1[10];
	s8 j=0;
	u8 z=16;
	TFT_VidFillColor(BLACK);
	HTFT_VidWriteChar ( S     , x , y+22    , RED     );
	HTFT_VidWriteChar ( P     , x-14 , y+22 , RED     );
	HTFT_VidWriteChar ( E     , x-28 , y+22 , RED     );
	HTFT_VidWriteChar ( E     , x-42 , y+22 , RED     );
	HTFT_VidWriteChar ( D     , x-56 , y+22 , RED     );

	//HTFT_VidWriteChar ( S     , x-z ,    40 , YELLOW     );
	//HTFT_VidWriteChar ( S     , x-14-z , 40 , YELLOW     );
	//HTFT_VidWriteChar ( I     , x-28-z , 40 , YELLOW     );
	//HTFT_VidWriteChar ( T     , x-42-z , 40 , YELLOW     );
	//HTFT_VidWriteChar ( C     , x-56-z , 40 , YELLOW     );
	//HTFT_VidWriteChar ( S     , x-70-z , 40 , YELLOW     );
	//HTFT_VidWriteChar ( numbers[0]     , x  , 40 , 0x07FF);


	if(num==0)
	{
		HTFT_VidWriteChar ( numbers[0]     , 114  , 122 , 0x07FF);
	}
	while (num)
	{
		str[i]=num%10;
		num/=10;
		i++;
	}

	for(j=i-1;j>=0;j--)
	{
		for(k=0;k<10;k++)
		{
			if(str[j]==k)
			{
				HTFT_VidWriteChar ( numbers[k]     , s  , y , 0x07FF);
				s=s-15;
			}
		}
	}
}
void HTFT_vidPrintInit()
{
	u8 x=114;
	u8 y=122;
	//TFT_VidFillColor(BLACK);
	static u8 c=0;
		if(c==0){
		TFT_VidFillColor(BLACK);
		}
		HTFT_voidDrawRect (0, 128,122,144,BLACK);
		HTFT_voidDrawRect (0, 128,68, 90,BLACK);
	HTFT_VidWriteChar ( N     , x , y+22    , RED     );
	HTFT_VidWriteChar ( zero     , x-14 , y+22 , RED     );
	HTFT_VidWriteChar ( R     , x-28 , y+22 , RED     );
	HTFT_VidWriteChar ( M     , x-42 , y+22 , RED     );
	HTFT_VidWriteChar ( A     , x-56 , y+22 , RED     );
	HTFT_VidWriteChar ( L     , x-56 , y+22 , RED     );

	HTFT_VidWriteChar ( one     , 112  , y , 0x07FF);

	HTFT_VidWriteChar ( A     , x ,    90 , YELLOW     );
	HTFT_VidWriteChar ( D     , x-14 , 90 , YELLOW     );
	HTFT_VidWriteChar ( A     , x-28 , 90 , YELLOW     );
	HTFT_VidWriteChar ( P     , x-42 , 90 , YELLOW     );
	HTFT_VidWriteChar ( T     , x-56 , 90 , YELLOW     );
	HTFT_VidWriteChar ( I     , x-70 , 90 , YELLOW     );
	HTFT_VidWriteChar ( V     , x-84 , 90 , YELLOW     );
	HTFT_VidWriteChar ( E     , x-98 , 90 , YELLOW     );

	HTFT_VidWriteChar ( two     , 112  , 68 , 0x07FF);
}

void HTFT_vidAuthInit(void)
{
	u8 x=114 - 40;
	u8 y=122 - 60;
	//TFT_VidFillColor(BLACK);
	static u8 c=0;
		if(c==0){
		TFT_VidFillColor(BLACK);
		}
		HTFT_voidDrawRect (0, 128,122,144,BLACK);
		HTFT_voidDrawRect (0, 128,68, 90,BLACK);
	HTFT_VidWriteChar ( C    , x , y+22    , GREEN     );
	HTFT_VidWriteChar ( L     , x-14 , y+22 , GREEN     );
	HTFT_VidWriteChar ( zero     , x-28 , y+22 , GREEN     );
	HTFT_VidWriteChar ( S     , x-42 , y+22 , GREEN     );
	HTFT_VidWriteChar ( E     , x-56 , y+22 , GREEN   );
	HTFT_VidWriteChar ( D     , x-70 , y+22 , GREEN   );


}
void HTFT_vidPrintSpeed()
{
	u8 x=114;
	u8 y=122;
	TFT_VidFillColor(BLACK);
	HTFT_VidWriteChar ( S     , x , y+22    , RED     );
	HTFT_VidWriteChar ( P     , x-14 , y+22 , RED     );
	HTFT_VidWriteChar ( E     , x-28 , y+22 , RED     );
	HTFT_VidWriteChar ( E     , x-42 , y+22 , RED     );
	HTFT_VidWriteChar ( D     , x-56 , y+22 , RED     );

//	HTFT_VidWriteChar ( one     , 112  , y , 0x07FF);
}
void HTFT_vidPrintDistance()
{
	u8 x=114;
	u8 y=122;
//	TFT_VidFillColor(BLACK);
	/*
	HTFT_VidWriteChar ( S     , x , y+22    , RED     );
	HTFT_VidWriteChar ( P     , x-14 , y+22 , RED     );
	HTFT_VidWriteChar ( E     , x-28 , y+22 , RED     );
	HTFT_VidWriteChar ( E     , x-42 , y+22 , RED     );
	HTFT_VidWriteChar ( D     , x-56 , y+22 , RED     );
*/
	HTFT_VidWriteChar ( D     , x ,    90 , YELLOW     );
	HTFT_VidWriteChar ( I     , x-14 , 90 , YELLOW     );
	HTFT_VidWriteChar ( S     , x-28 , 90 , YELLOW     );
	HTFT_VidWriteChar ( T     , x-42 , 90 , YELLOW     );
	HTFT_VidWriteChar ( A     , x-56 , 90 , YELLOW     );
	HTFT_VidWriteChar ( N     , x-70 , 90 , YELLOW     );
	HTFT_VidWriteChar ( C     , x-84 , 90 , YELLOW     );
	HTFT_VidWriteChar ( E     , x-98 , 90 , YELLOW     );

//	HTFT_VidWriteChar ( one     , 112  , y , 0x07FF);
}
void HTFT_vidSendNum1DigSpeed(s32 num)
{
	u8 x=112;
//	TFT_VidFillColor(BLACK);
	u8 i=0,k;
	static u8 s=112;
	u16 str[20];
	s8 j=0;
	if(num==0)
	{
		HTFT_VidWriteChar ( numbers[0]     , s  , 122 , 0x07FF);
		s=s-15;
	}
	while (num)
	{
		str[i]=num%10;
		num/=10;
		i++;
	}

	for(j=i-1;j>=0;j--)
	{
		for(k=0;k<10;k++)
		{
			if(str[j]==k)
			{
				HTFT_VidWriteChar ( numbers[k]     , s  , 122 , 0x07FF);
				s=s-15;
			}
		}
	}

}
void HTFT_vidSendNum1DigDista(s32 num)
{
	u8 x=112;
//	TFT_VidFillColor(BLACK);
	u8 i=0,k;
	static u8 s=112;
	u16 str[20];
	s8 j=0;
	if(num==0)
	{
		HTFT_VidWriteChar ( numbers[0]     , 112  , 68 , 0x07FF);
		s=s-15;
	}
	while (num)
	{
		str[i]=num%10;
		num/=10;
		i++;
	}

	for(j=i-1;j>=0;j--)
	{
		for(k=0;k<10;k++)
		{
			if(str[j]==k)
			{
				HTFT_VidWriteChar ( numbers[k]     , s  , 68 , 0x07FF);
				s=s-15;
			}
		}
	}

}
