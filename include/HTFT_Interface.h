#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H



void HTFT_voidInitialize   (void);
void HTFT_vidAuthInit(void);
void HTFT_voidDisplayImage (const u16* Copy_Image);
void TFT_VidWriteChar( u8 * Cop_u8Char , u8 Xaxis , u8 Yaxis , u16 Copy_u8Color );
void TFT_VidFillColor ( u16 Copy_u16Color );
void HTFT_VidWriteChar( u16 * Cop_u8Char , u8 Xaxis , u8 Yaxis , u16 Copy_u8Color );
void HTFT_vidSendNumPoint(u32 num);
void HTFT_vidSendNum(s32 num);
void HTFT_vidSendNumDIST(s32 num);
void HTFT_voidDrawRect (u8 x1,u8 x2,u8 y1,u8 y2,u16 Copy_u16color);
//void HTFT_vidSendNumAll(s32 num,s32 num1);
void HTFT_vidPrintInit();
void HTFT_vidSendNumAdaptive(s32 num,s32 num1);
void HTFT_vidPrintSpeedNormal(s32 num);
void HTFT_vidSendNum1DigDista(s32 num);
void HTFT_vidSendNum1DigSpeed(s32 num);
void HTFT_vidPrintSpeed();
void HTFT_vidPrintDistance();
#define SWRESET 0x01 // software reset
#define SLPOUT 0x11 // sleep out
#define DISPOFF 0x28 // display off
#define DISPON 0x29 // display on
#define CASET 0x2A // column address set
#define RASET 0x2B // row address set
#define RAMWR 0x2C // RAM write
#define MADCTL 0x36 // axis control
#define COLMOD 0x3A // color mode
// 1.8" TFT display constants
#define XSIZE 128
#define YSIZE 160
#define XMAX XSIZE-1
#define YMAX YSIZE-1
// Color constants
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x0400
#define LIME 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#endif
