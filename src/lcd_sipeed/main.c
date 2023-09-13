#include <stdio.h>

#include "dmac.h"
#include "dvp.h"
#include "fpioa.h"
#include "gpiohs.h"
#include "sleep.h"
#include "sysctl.h"

#include "lcd_sipeed.h"
#include "gc0328.h"

#include "system_config.h"

volatile uint8_t g_dvp_finish_flag = 0;

uint8_t cam_buf[CAM_W * CAM_H * 2] __attribute__((aligned(64)));
uint8_t lcd_buf[LCD_W * LCD_H * 2] __attribute__((aligned(64)));

void io_mux_init(void)
{
    /* Init DVP IO map and function settings */
    fpioa_set_function(42, FUNC_CMOS_RST);
    fpioa_set_function(44, FUNC_CMOS_PWDN);
    fpioa_set_function(46, FUNC_CMOS_XCLK);
    fpioa_set_function(43, FUNC_CMOS_VSYNC);
    fpioa_set_function(45, FUNC_CMOS_HREF);
    fpioa_set_function(47, FUNC_CMOS_PCLK);
    fpioa_set_function(41, FUNC_SCCB_SCLK);
    fpioa_set_function(40, FUNC_SCCB_SDA);


    sysctl_set_spi0_dvp_data(1);

    sysctl_set_power_mode(SYSCTL_POWER_BANK6, SYSCTL_POWER_V18);
    sysctl_set_power_mode(SYSCTL_POWER_BANK7, SYSCTL_POWER_V18);
    msleep(15);
}

static int on_irq_dvp(void *ctx)
{
    if(dvp_get_interrupt(DVP_STS_FRAME_FINISH))
    {
        dvp_clear_interrupt(DVP_STS_FRAME_FINISH);
        g_dvp_finish_flag = 1;
    } else
    {
        if(g_dvp_finish_flag == 0)
            dvp_start_convert();
        dvp_clear_interrupt(DVP_STS_FRAME_START);
    }
    return 0;
}

int main()
{
    uint64_t core = current_coreid();

    sysctl_pll_set_freq(SYSCTL_PLL0, PLL0_OUTPUT_FREQ);
    sysctl_pll_set_freq(SYSCTL_PLL1, PLL1_OUTPUT_FREQ);
    sysctl_pll_set_freq(SYSCTL_PLL2, PLL2_OUTPUT_FREQ);
    sysctl_clock_enable(SYSCTL_CLOCK_AI);

    // uarths_init();
    io_mux_init();
    plic_init();
    dmac_init();

    /* DVP init */
    printf("DVP init\r\n");
    dvp_init(8);
    dvp_set_xclk_rate(24000000);
    dvp_enable_burst();
    dvp_set_output_enable(0, 1); //enable to ai
    dvp_set_output_enable(1, 1); //disable to lcd
    dvp_set_image_format(DVP_CFG_RGB_FORMAT);
    dvp_set_image_size(CAM_W, CAM_H);
    gc0328_init();
    open_gc0328_0();

    dvp_set_display_addr((uint32_t)cam_buf);
    dvp_config_interrupt(DVP_CFG_START_INT_ENABLE | DVP_CFG_FINISH_INT_ENABLE, 0);
    dvp_disable_auto();

    /* DVP interrupt config */
    printf("DVP interrupt config\r\n");
    plic_set_priority(IRQN_DVP_INTERRUPT, 2);
    plic_irq_register(IRQN_DVP_INTERRUPT, on_irq_dvp, NULL);
    plic_irq_enable(IRQN_DVP_INTERRUPT);

    sysctl_enable_irq();

    g_dvp_finish_flag = 0;
    dvp_clear_interrupt(DVP_STS_FRAME_START | DVP_STS_FRAME_FINISH);
    dvp_config_interrupt(DVP_CFG_START_INT_ENABLE | DVP_CFG_FINISH_INT_ENABLE, 1);

	//LCD init
	lcd_sipeed_config(lcd_buf);
	
    uint32_t *g_lcd_gram = (uint32_t *)iomem_malloc(320 * 240 * 2);
    for(int i = 0; i < (320 * 240) / 2; i++)
    {
        g_lcd_gram[i] = 0;
    }

    for(int i = (320 * 240) / 2; i < 320 * 240; i++)
    {
        g_lcd_gram[i] = UINT32_MAX;
    }

    unsigned long t0, t1;

    // while(1)
    // {
    //     t0 = read_cycle();
    //     while(g_dvp_finish_flag == 0)
    //     {
    //     }; //15ms

    //     lcd_covert_cam_order((uint32_t *)cam_buf, CAM_W * CAM_H / 2);
	// 	while(lcd_sipeed_busy()){};
    //     copy_image_cam_to_lcd(cam_buf, lcd_buf);
    //     g_dvp_finish_flag = 0; 

    //     t1 = read_cycle();
    //     printf("%ld us!\r\n", ((t1 - t0) * 1000000 / PLL0_OUTPUT_FREQ * 2));
    // }

}
