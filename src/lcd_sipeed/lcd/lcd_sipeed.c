#include "lcd_sipeed.h"

#include <string.h>

#include "gpiohs.h"
#include "sleep.h"

#include "system_config.h"
#include "fpioa.h"
#include "sleep.h"
#include "sysctl.h"

#include "timer.h"
#include "utils.h"


extern void gpiohs_irq_disable(size_t pin);
extern void spi_send_data_normal(spi_device_num_t spi_num,
                                 spi_chip_select_t chip_select,
                                 const uint8_t *tx_buff, size_t tx_len);
///////////////////////////////////////////////////////////////////////////////
static int32_t PageCount = 0;
static uint8_t *img_ptr = NULL; //TODO: check prt type???
static volatile uint8_t dis_flag = 0;
static void lcd_sipeed_send_dat(uint8_t *DataBuf, uint32_t Length);


static void lcd_test(void)
{
	uint8_t* lcd_addr = (img_ptr);
	uint16_t unit_x = LCD_W/16;
	for(int i=0; i< LCD_H; i++)
	{
		if(1){
			for(int j=0; j<LCD_W; j++)
			{	
				if(j<unit_x*5){	//R
					lcd_addr[(i*LCD_W+j)*2 + 1] = (1<<(j/unit_x))<<3;
					lcd_addr[(i*LCD_W+j)*2 + 0] = 0;
				} else if(j<unit_x*(5+6)) {	//G
					lcd_addr[(i*LCD_W+j)*2 + 1] = ((1<<((j-unit_x*5)/unit_x))>>3);
					lcd_addr[(i*LCD_W+j)*2 + 0] = ((1<<((j-unit_x*5)/unit_x))<<5);
				} else {	//B
					lcd_addr[(i*LCD_W+j)*2 + 1] = 0;
					lcd_addr[(i*LCD_W+j)*2 + 0] = 1<<((j-unit_x*(5+6))/unit_x);
				}
			}
		}	
	}
	while(1){};
	return;
}

static void lcd_sipeed_send_cmd(uint8_t CMDData)
{
    gpiohs_set_pin(LCD_DCX_HS_NUM, GPIO_PV_HIGH);

    spi_init(LCD_SIPEED_SPI_DEV, SPI_WORK_MODE_0, SPI_FF_OCTAL, 8, 0);
    spi_init_non_standard(LCD_SIPEED_SPI_DEV, 8 /*instrction length*/, 0 /*address length*/, 0 /*wait cycles*/,
                          SPI_AITM_AS_FRAME_FORMAT /*spi address trans mode*/);
    spi_send_data_normal(LCD_SIPEED_SPI_DEV, LCD_SIPEED_SPI_SS, (uint8_t *)(&CMDData), 1);
}

static void sipeed_spi_send_data_dma(uint8_t spi_num, uint8_t chip_select,uint8_t dma_chn, const uint8_t *data_buf, size_t buf_len)
{
    volatile spi_t *spi_handle = spi[spi_num];
	set_bit(&spi_handle->ctrlr0, 3 << 8, SPI_TMOD_TRANS << 8);
	spi_handle->ser = 0x00;
	spi_handle->ssienr = 0x00;
    spi_handle->dmacr = 0x2; /*enable dma transmit*/
    spi_handle->ssienr = 0x01;
    sysctl_dma_select((dmac_channel_number_t)dma_chn, SYSCTL_DMA_SELECT_SSI0_TX_REQ + spi_num * 2);
    dmac_set_single_mode((dmac_channel_number_t)dma_chn, data_buf, (void *)(&spi_handle->dr[0]), DMAC_ADDR_INCREMENT, DMAC_ADDR_NOCHANGE,
                         DMAC_MSIZE_4, DMAC_TRANS_WIDTH_32, buf_len / 4);
    spi_handle->ser = 1U << chip_select;
}

static void lcd_sipeed_send_dat(uint8_t *DataBuf, uint32_t Length)
{
    sipeed_spi_send_data_dma(LCD_SIPEED_SPI_DEV, LCD_SIPEED_SPI_SS, DMAC_CHANNEL2, (DataBuf), Length);
}

static void irq_RS_Sync(void);
static int timer_callback(void *ctx);
//excute in 50Hz lcd refresh irq
static void lcd_sipeed_display(uint8_t *img_buf, uint8_t block)
{
    img_ptr = img_buf;
    gpiohs_irq_disable(LCD_DCX_HS_NUM);
    PageCount = -1;

    spi_init(LCD_SIPEED_SPI_DEV, SPI_WORK_MODE_0, SPI_FF_OCTAL, 32, 0);
    lcd_sipeed_send_cmd(LCD_FRAME_START);

    spi_init(LCD_SIPEED_SPI_DEV, SPI_WORK_MODE_0, SPI_FF_OCTAL, 32, 1);
    spi_init_non_standard(LCD_SIPEED_SPI_DEV, 0, 32, 0, SPI_AITM_AS_FRAME_FORMAT);

    gpiohs_set_drive_mode(LCD_DCX_HS_NUM, GPIO_DM_INPUT);
    gpiohs_set_pin_edge(LCD_DCX_HS_NUM, GPIO_PE_RISING);
    gpiohs_set_irq(LCD_DCX_HS_NUM, 3, irq_RS_Sync);

    if(block)
    {
        while(PageCount < LCD_SIPEED_FRAME_END_LINE)
        {
            msleep(1);
        }; //等待的同时可以做其实事情	//50ms
    }
}

static void irq_RS_Sync(void)
{
	if(PageCount < LCD_H * LCD_YUP )
	{
		dis_flag = 1;
		if(PageCount >= 0)lcd_sipeed_send_dat(&img_ptr[PageCount / LCD_YUP * LCD_W * 2], LCD_W * 2);
	} else if(PageCount > LCD_SIPEED_FRAME_END_LINE-1 && dis_flag)
	{
//printk("L:%ld\r\n", sysctl_get_time_us()/1000);
		dis_flag = 0;
	} 
	PageCount++;
	return;
}

static volatile uint64_t int_tim = 0;
static int timer_callback(void *ctx)
{
    int_tim = sysctl_get_time_us();
	//printk("T:%d\r\n", (int)(int_tim/1000));
    dis_flag = 1;
    lcd_sipeed_display((img_ptr), 0);
}

uint8_t lcd_covert_cam_order(uint32_t *addr, uint32_t length)
{
    if(NULL == addr)
        return -1;

    uint32_t *pend = addr + length;
    uint16_t *pdata;
    uint16_t tmp;
    for(; addr < pend; addr++)
    {
        pdata = (uint16_t *)(addr);
        tmp = pdata[0];
        pdata[0] = pdata[1];
        pdata[1] = tmp;
    } //1.7ms
    return 0;
}

void copy_image_cam_to_lcd(uint8_t *cam_img, uint8_t *lcd_img)
{
    uint32_t x = 0, y = 0;
    for(y = 0; y < CAM_H; y++)
    {
        memcpy((lcd_img) + y * LCD_W * 2, cam_img + (y * CAM_W + x) * 2, CAM_W * 2);
    }
    return;
}

uint32_t lcd_sipeed_busy(void)
{
	return dis_flag;
}

void lcd_sipeed_config(uint8_t* image)
{
	img_ptr = image;
    fpioa_set_function(LCD_RST_PIN, FUNC_GPIOHS0 + LCD_RST_HS_NUM);
    fpioa_set_function(LCD_DCX_PIN, FUNC_GPIOHS0 + LCD_DCX_HS_NUM);
    fpioa_set_function(LCD_WRX_PIN, FUNC_SPI0_SS3);
    fpioa_set_function(LCD_SCK_PIN, FUNC_SPI0_SCLK);
	fpioa_set_io_driving(LCD_SCK_PIN, FPIOA_DRIVING_7);
	sysctl_set_spi0_dvp_data(1);
	
	
    gpiohs_set_drive_mode(LCD_DCX_HS_NUM, GPIO_DM_OUTPUT);
    gpiohs_set_pin(LCD_DCX_HS_NUM, GPIO_PV_HIGH);

    gpiohs_set_drive_mode(LCD_RST_HS_NUM, GPIO_DM_OUTPUT);
    gpiohs_set_pin(LCD_RST_HS_NUM, GPIO_PV_LOW);
    msleep(100);
    gpiohs_set_pin(LCD_RST_HS_NUM, GPIO_PV_HIGH);

    spi_init(LCD_SIPEED_SPI_DEV, SPI_WORK_MODE_0, SPI_FF_OCTAL, 32, 0);
    spi_set_clk_rate(LCD_SIPEED_SPI_DEV, LCD_SIPEED_SPI_FREQ);

    lcd_sipeed_send_cmd(LCD_BL_ON);
    lcd_sipeed_send_cmd(LCD_FRAME_START);
    lcd_sipeed_send_cmd(LCD_DISOLAY_ON);

    timer_init(1);
    timer_set_interval(1, 1, 30 * 1000 * 1000);          	//30ms刷屏一次
    timer_irq_register(1, 1, 0, 1, timer_callback, NULL); //4th pri
    timer_set_enable(1, 1, 1);
	
	lcd_test();
	return;
}

