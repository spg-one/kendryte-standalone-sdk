#ifndef __LCD_SPIEED_H
#define __LCD_SPIEED_H

#include <stdint.h>

#include "system_config.h"


#include "spi.h"

#define BLACK       0x0000
#define NAVY        0x000F
#define DARKGREEN   0x03E0
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define DARKGREY    0x7BEF
#define BLUE        0x001F
#define GREEN       0x07E0
#define CYAN        0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
#define ORANGE      0xFD20
#define GREENYELLOW 0xAFE5
#define PINK        0xF81F
#define USER_COLOR  0xAA55

/* clang-format off */
#define LCD_BL_ON                       (0x61)
#define LCD_BL_OFF                      (0x60)
#define LCD_DISOLAY_ON                  (0x30)
#define LCD_FRAME_START                 (0x41)

#define LCDDisMode_normal               (0x01)
#define LCDDisMode_TranBK               (0x00)
#define LCDDisMode_Reverse              (0x10)

#define LCD_SIPEED_SPI_DEV              (SPI_DEVICE_0)
#define LCD_SIPEED_SPI_SS               (SPI_CHIP_SELECT_3)
#define LCD_SIPEED_SPI_FREQ             (35000000)

//must choose one lcd if select sipeed lcd
#define CONFIG_LCD_TYPE_SIPEED_800480       (0)
#define CONFIG_LCD_TYPE_SIPEED_480272       (1)
#define CONFIG_LCD_TYPE_SIPEED_1024600      (0)


#if CONFIG_LCD_TYPE_SIPEED_800480
	#define LCD_W                                (402)
	#define LCD_H                                (240)
	#define DAT_W                                (240)
	#define DAT_H                                (240)
	#define LCD_OFT_X                            (0)
	#define LCD_OFT_Y                            (0)
#elif CONFIG_LCD_TYPE_SIPEED_480272
	#define LCD_W                                (482)
	#define LCD_H                                (272)
	#define DAT_W                                (240)
	#define DAT_H                                (240)
	#define LCD_OFT_X                            (0)
	#define LCD_OFT_Y                            (0)
#elif CONFIG_LCD_TYPE_SIPEED_1024600
	#define LCD_W                                (344)
	#define LCD_H                                (240)
	#define DAT_W                                (240)
	#define DAT_H                                (240)
	#define LCD_OFT_X                            (0)
	#define LCD_OFT_Y                            (0)
#endif

#if CONFIG_LCD_TYPE_SIPEED_800480
	#define LCD_XUP						(2)
	#define LCD_YUP						(2)
	#define LCD_VFP						(59)
	#define LCD_SIPEED_SPI_FREQ 		(75000000)
#elif CONFIG_LCD_TYPE_SIPEED_480272
	#define LCD_XUP						(1)
	#define LCD_YUP						(1)
	#define LCD_VFP						(8)
	#define LCD_SIPEED_SPI_FREQ  		(30000000)
#elif CONFIG_LCD_TYPE_SIPEED_1024600
	#define LCD_XUP						(3)
	#define LCD_YUP						(3)
	#define LCD_VFP						(72)
	#define LCD_SIPEED_SPI_FREQ  		(30000000)
#endif
#define LCD_SIPEED_FRAME_END_LINE   (LCD_H * LCD_YUP + LCD_VFP - 1)
/* clang-format on */



void lcd_sipeed_config(uint8_t* image);
uint32_t lcd_sipeed_busy(void);
uint8_t lcd_covert_cam_order(uint32_t *addr, uint32_t length);
void copy_image_cam_to_lcd(uint8_t *cam_img, uint8_t *lcd_img);

/* flush img_buf to lcd */
//void lcd_sipeed_display(uint8_t *img_buf, uint8_t block);

#endif /* __LCD_SPIEED_H */