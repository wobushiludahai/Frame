/*
 * @Description: STM32 SPI
 * @Author: land sea
 * @Date: 2019-11-18 20:43:34
 * @LastEditTime: 2019-11-23 16:23:07
 * @LastEditors: Please set LastEditors
 */
#include "spi.h"

#ifdef STM32_SPI_EN
SPI_HandleTypeDef SPI_InitStruct;

/**
 * @description: SPI初始化
 * @param {type} 
 * @return: 
 */
void Drv_SpiInit(void)
{
    SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN);    //SPI2使能

    SPI_InitStruct.Instance = SPI2;
    SPI_InitStruct.Init.Mode = SPI_MODE_MASTER;//SPI模式：主机模式
    SPI_InitStruct.Init.Direction = SPI_DIRECTION_2LINES;//两线全双工
    SPI_InitStruct.Init.DataSize = SPI_DATASIZE_8BIT;//数据宽度：8位
    SPI_InitStruct.Init.CLKPolarity = SPI_POLARITY_LOW; //串行同步字时钟控制为低速时钟
    SPI_InitStruct.Init.CLKPhase = SPI_PHASE_1EDGE;      //CPOL=0;CPHA=0模式
    SPI_InitStruct.Init.NSS = SPI_NSS_SOFT;//NSSD由软件管理
    SPI_InitStruct.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;//波特率分频，8分频
    SPI_InitStruct.Init.FirstBit = SPI_FIRSTBIT_MSB;//数据从MSB开始
    SPI_InitStruct.Init.TIMode = SPI_TIMODE_DISABLE;//SPI Motorola mode
    SPI_InitStruct.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;//CRC校验不使能
    SPI_InitStruct.Init.CRCPolynomial = 7;//CRC值计算的多项式
    SPI_InitStruct.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
    SPI_InitStruct.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;

    if (HAL_SPI_Init(&SPI_InitStruct) != HAL_OK)
    {
        while(1);
    }
    __HAL_SPI_ENABLE(&SPI_InitStruct);
}

/**
 * @description: SPI主设备发出函数
 * @param {type} 
 * @return: 
 */
void SpiTransData(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    if((pData == NULL)||(Size == 0))
    {
        return;
    }
    
    __HAL_LOCK(hspi);
    
    hspi->TxXferCount = Size;
    
    hspi->TxISR       = NULL;
    hspi->RxISR       = NULL;

    SET_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);

    if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
      __HAL_SPI_ENABLE(hspi);
    }

    while (hspi->TxXferCount > 0U)
    {
        if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE))
        {
            *((__IO uint8_t *)&hspi->Instance->DR) = (*pData++);
            hspi->TxXferCount--;
        }
    }

    __HAL_UNLOCK(hspi);
}

/**
 * @description: SPI主设备接收函数
 * @param {type} 
 * @return: 
 */
void Drv_SpiRecvData(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    if((pData == NULL)||(Size <= 0))
    {
        return;
    }

    if ((hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES))
    {
        Drv_SpiSendAndRecv(hspi, pData, pData, Size, Timeout);
        return;
    }
    __HAL_LOCK(hspi);

    hspi->RxXferCount = Size;

    hspi->RxISR       = NULL;
    hspi->TxISR       = NULL;

    SET_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);

    if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
        __HAL_SPI_ENABLE(hspi);
    }

    while (hspi->RxXferCount > 0U)
    {
        if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE))
        {
            (* (uint8_t *)pData) = *(__IO uint8_t *)&hspi->Instance->DR;
            pData += sizeof(uint8_t);
            hspi->RxXferCount--;
        }
    }
}

/**
 * @description: 根据ST库函数改写  bug无超时判定
 * @param {type} 
 * @return: 
 */
HAL_StatusTypeDef Drv_SpiSendAndRecv(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size,
                                          uint32_t Timeout)
{
    uint32_t txallowed = 1U;

    __HAL_LOCK(hspi);

    hspi->RxXferCount = Size;
    hspi->TxXferCount = Size;

    hspi->RxISR       = NULL;
    hspi->TxISR       = NULL;

    SET_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);

    if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
      __HAL_SPI_ENABLE(hspi);
    }

    while ((hspi->TxXferCount > 0U) || (hspi->RxXferCount > 0U))
    {
        if (txallowed && (hspi->TxXferCount > 0U) && (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE)))
        {
            *(__IO uint8_t *)&hspi->Instance->DR = (*pTxData++);
            hspi->TxXferCount--;
            txallowed = 0U;
        }
    
        if ((hspi->RxXferCount > 0U) && (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE)))
        {
          
            (*(uint8_t *)pRxData++) = *(__IO uint8_t *)&hspi->Instance->DR;
            hspi->RxXferCount--;
            txallowed = 1U;
        }
    }
    __HAL_UNLOCK(hspi);
}



#endif /*STM32_SPI_EN*/
