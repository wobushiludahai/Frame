/*
 * @Description: msp430 spi
 * @Author: land sea
 * @Date: 2019-11-18 20:43:34
 * @LastEditTime: 2019-11-23 16:23:45
 * @LastEditors: Please set LastEditors
 */

#include "spi.h"
#include "driverlib.h"      //MSP430底层包

#ifdef MSP430_SPI_EN
/**
 * @description: SPI初始化
 * @param {type} 
 * @return: 
 */
void Drv_SpiInit(void)
{
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN7, GPIO_SECONDARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN6, GPIO_SECONDARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN2, GPIO_SECONDARY_MODULE_FUNCTION);

    EUSCI_B_SPI_initMasterParam param = {0};
    param.selectClockSource = EUSCI_B_SPI_CLOCKSOURCE_SMCLK;
    param.clockSourceFrequency = CS_getSMCLK();

    param.desiredSpiClock = 1000000;
    param.msbFirst = EUSCI_B_SPI_MSB_FIRST;
    
    param.clockPhase = EUSCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;
    param.clockPolarity = EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW;

    param.spiMode = EUSCI_B_SPI_3PIN;
    EUSCI_B_SPI_initMaster(EUSCI_B0_BASE, &param);

    //Enable SPI module
    EUSCI_B_SPI_enable(EUSCI_B0_BASE);
}

/**
 * @description: SPI主设备发出函数
 * @param {type} 
 * @return: 
 */
void Drv_SpiTransData(UINT8 *pTxData, UINT16 size)
{
    if((pTxData == NULL)||(size == 0))
    {
        return;
    }

    UINT16 wsize = size;
    UINT8 *bydata = pTxData;

    while (wsize)
    {
        if (!(UCBUSY & UCB0STATW))
        {
            UCB0TXBUF = (*bydata++);
            wsize--;
        }
    }
}

/**
 * @description: SPI主双设备接收函数
 * @param {type} 
 * @return: 
 */
void Drv_SpiRecvData(UINT8 *pRxData, UINT16 size)
{
    if((pRxData == NULL)||(size <= 0))
    {
        return;
    }

    UINT16 wsize = size;
    UINT8 *bydata = pRxData, byTxFlag = TRUE;

    while (wsize)
    {
        if((byTxFlag)&&(!(UCBUSY & UCB0STATW)))
        {
            UCB0TXBUF = 0x00;
            byTxFlag = FALSE;
        }
        if (!(UCBUSY & UCB0STATW))
        {
            *bydata++ = UCB0RXBUF;
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
void Drv_SpiSendAndRecv(UINT8 *pTxData,UINT8 *pRxData, UINT16 size)
{
    if(((pTxData == NULL)&&(pRxData == NULL))||(0 == size)||((pRxData != NULL)&&(pTxData != NULL)))
    {
        return;         //如果发送和接收缓冲区均为空，则返回
    }

    UINT16 TempSize = size;
    UINT8 *ptempdata, byTxFlag = FALSE, byRxFlag = FALSE, byallowTx = FALSE;
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
        if (((byallowTx)||(byTxFlag))&&(!(UCBUSY & UCB0STATW)))
        {
            if(byTxFlag)
            {
                UCB0TXBUF = (*ptempdata++);
                TempSize--;
            }
            else
            {
                UCB0TXBUF = 0x00;
                byallowTx = FALSE;
            }
        }

        if ((byRxFlag)&&(!(UCBUSY & UCB0STATW)))
        {
            *ptempdata++ = UCB0RXBUF;
            if(--TempSize)
            {
                byallowTx = TRUE;
            }
        }
    }
}

/**
 * @description: SPI速率调整
 * @param {type} speed  SPI速率   单位为HZ
 * @return: 
 */
void Drv_SpiSpeedChanged(UINT8 speed)
{
    EUSCI_B_SPI_changeMasterClockParam param = {0};
    param.clockSourceFrequency = CS_getSMCLK();
    param.desiredSpiClock = speed;

    EUSCI_B_SPI_changeMasterClock(EUSCI_B0_BASE, &param);
}

#endif /*MSP430_SPI_EN*/
