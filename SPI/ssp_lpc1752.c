/*
 * @Description: LPC1752 SPI
 * @Author: land sea
 * @Date: 2019-11-18 20:43:34
 * @LastEditTime: 2019-11-23 16:44:57
 * @LastEditors: Please set LastEditors
 */
#include "spi.h"

#ifdef LPC17xx_SSP_EN
#define Frame_SPI      LPC_SSP0

/**
 * @description: 将SSP0初始化为主机模式
 * @param {type} 
 * @return: 
 */
void Drv_SpiInit(void)
{
	SSP_CFG_Type SSP_mode;
	/*
     *  配置SCk、SSEL、MOSI、MISO引脚功能
     */
     
	PINSEL_CFG_Type PIO_mode;
    PIO_mode.Pinmode    = PINSEL_PINMODE_PULLUP;    //0
    PIO_mode.OpenDrain  = PINSEL_PINMODE_NORMAL;    //0

    PIO_mode.Funcnum    = PINSEL_FUNC_2;            //2  
    PIO_mode.Portnum    = SCLK_PORT;                //p0.15
    PIO_mode.Pinnum     = SCLK_PIN;                 //clock for spi or ssp?
    PINSEL_ConfigPin( &PIO_mode);

    PIO_mode.Funcnum    = PINSEL_FUNC_2;            //2
    PIO_mode.Portnum    = MISO_PORT;                //p0.17
    PIO_mode.Pinnum     = MISO_PIN;                 // spi miso               AD, SDOA  serial output the data to CPU miso
    PINSEL_ConfigPin( &PIO_mode); 

    PIO_mode.Funcnum    = PINSEL_FUNC_2;            //2
    PIO_mode.Portnum    = MOSI_PORT;                //p0.18
    PIO_mode.Pinnum     = MOSI_PIN;                 // spi mosi                connect to ad  sdi 
    PINSEL_ConfigPin( &PIO_mode);                       

 	PIO_mode.Funcnum    = PINSEL_FUNC_0;            /* 软件方式控制SEL管脚  */
 	PIO_mode.Portnum    = ADFS_PORT;                //p2.7
 	PIO_mode.Pinnum     = ADFS_PIN;                 // connect to ad cs 
 	PINSEL_ConfigPin( &PIO_mode);
	GPIO_SetDir( ADFS_PORT, (1 << ADFS_PIN), GPIO_DIR_OUTPUT);		
	GPIO_SetValue( ADFS_PORT, (1 << ADFS_PIN));  	

    /*
     *  初始化SSP         //spi
     */
    SSP_ConfigStructInit( &SSP_mode);
	SSP_mode.Databit    = SSP_DATABIT_16;           //16位
    SSP_mode.CPOL       = SSP_CPOL_LO;
    SSP_mode.CPHA       = SSP_CPHA_SECOND;
    SSP_mode.ClockRate  = SSP_BPS;
    SSP_mode.Mode       = SSP_MASTER_MODE;
    SSP_mode.FrameFormat= SSP_FRAME_SPI;
    SSP_Init( AD7616_SPI, &SSP_mode);

    SSP_Cmd( AD7616_SPI, ENABLE);                           /* 使能SSP功能	*/
}

/**
 * @description: SPI主设备发出函数
 * @param {type} 
 * @return: 
 */
void Drv_SpiTransData(uint16_t *pTxData, uint16_t size)
{
    uint16_t wsize = size;
    uint16_t *wdata = pTxData;
    
    if((pTxData == NULL)||(size == 0))
    {
        return;
    }

    while (wsize)
    {
        {
            SSP_SendData(AD7616_SPI ,*wdata++);
            wsize--;
        }
        while(SSP_GetStatus( AD7616_SPI, SSP_STAT_BUSY)); /* 等待接收数据，等待FIFO数据发送完   */   
    }
}

/**
 * @description: SPI主双设备接收函数
 * @param {type} 
 * @return: 
 */
void Drv_SpiRecvData(uint16_t *pRxData, uint16_t size)
{
    uint16_t wsize = size;
    uint16_t *bydata = pRxData, byTxFlag = TRUE;
    
    if((pRxData == NULL)||(size <= 0))
    {
        return;
    }

    while (wsize)
    {
        if((byTxFlag))
        {
            SSP_SendData(AD7616_SPI ,0xFFFF);
            byTxFlag = FALSE;
        }
        while(SSP_GetStatus( AD7616_SPI, SSP_STAT_BUSY)); /* 等待接收数据，等待FIFO数据发送完   */   
        {
            *bydata++ = SSP_ReceiveData(AD7616_SPI);
            if(--wsize)
            {
                byTxFlag = TRUE;
            }
        }
    }
}    

/**
 * @description: SPI主设备接收和发送函数一体，但仅能接收或仅能发送
 * @param {type} 
 * @return: 
 */
void Drv_SpiSendAndRecv(uint16_t *pTxData,uint16_t *pRxData, uint16_t size)
{
    if(((pTxData == NULL)&&(pRxData == NULL))||(0 == size)||((pRxData != NULL)&&(pTxData != NULL)))
    {
        return;         //如果发送和接收缓冲区均为空，则返回
    }

    uint16_t TempSize = size;
    uint16_t *ptempdata, byTxFlag = FALSE, byRxFlag = FALSE, byallowTx = FALSE;
    if (pTxData != NULL)
    {
        byTxFlag = TRUE;
        ptempdata = pTxData;
    }
    else
    {
        byallowTx = TRUE;
        byRxFlag = TRUE;
        ptempdata = pRxData;
    }

    while(TempSize)
    {
        if (((byallowTx)||(byTxFlag)))
        {
            if(byTxFlag)
            {
                SSP_SendData(AD7616_SPI ,*ptempdata++);
                TempSize--;
            }
            else
            {
                SSP_SendData(AD7616_SPI ,0xFFFF);
                byallowTx = FALSE;
            }
        }
        while(SSP_GetStatus( AD7616_SPI, SSP_STAT_BUSY)); /* 等待接收数据，等待FIFO数据发送完   */   
        if ((byRxFlag))
        {
            *ptempdata++ = SSP_ReceiveData(AD7616_SPI);
            if(--TempSize)
            {
                byallowTx = TRUE;
            }
        }
    }
}

#endif /*LPC17xx_SSP_EN*/
