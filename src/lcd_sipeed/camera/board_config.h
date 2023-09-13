#ifndef _BOARD_CONFIG_
#define _BOARD_CONFIG_

#include <stdio.h>

#define 	BOARD_V1_2_LE				0
#define 	BOARD_V1_3					1
// choose your board version
#define 	BOARD_VERSION				BOARD_V1_3

// pin definitions
/* CAMERA */
#if (BOARD_VERSION == BOARD_V1_2_LE)
#define		DVP_PWDN_PIN				45
#define		DVP_RST_PIN					43
#elif (BOARD_VERSION == BOARD_V1_3)
#define		DVP_SCCB_SDA_PIN_2			40
#define		DVP_PWDN_PIN				44
#endif
#define		DVP_VSYNC_PIN				43
#define		DVP_HREF_PIN				45
#define		DVP_PCLK_PIN				47
#define		DVP_XCLK_PIN				46
#define		DVP_SCCB_SCLK_PIN			41
#define		DVP_SCCB_SDA_PIN			40	


#endif
