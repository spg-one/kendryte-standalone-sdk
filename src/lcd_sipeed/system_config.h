#ifndef _SYSTEM_CONFIG_H
#define _SYSTEM_CONFIG_H

/* clang-format off */
///////////////////////////////////////////////////////////////////////////////
#define PLL0_OUTPUT_FREQ            (800000000UL)
#define PLL1_OUTPUT_FREQ            (400000000UL)
#define PLL2_OUTPUT_FREQ            (45158400UL)
///////////////////////////////////////////////////////////////////////////////
#define LCD_W                       (400)
#define LCD_H                       (240)

#define CAM_W                       (320)
#define CAM_H                       (240)

///////////////////////////////////////////////////////////////////////////////
/* LCD */
#define LCD_RST_PIN                         (37)
#define LCD_DCX_PIN                         (38)
#define LCD_WRX_PIN                         (39)
#define LCD_SCK_PIN                         (36)

#define LCD_DCX_HS_NUM                      (5)
#define LCD_RST_HS_NUM                      (6)


///////////////////////////////////////////////////////////////////////////////
/* clang-format on */

#endif
