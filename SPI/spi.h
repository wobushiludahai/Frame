/*
 * @Description: SPI 接口   注：不包含端口初始化
 * @Author: land sea
 * @Date: 2019-11-18 20:43:34
 * @LastEditTime: 2019-11-23 16:45:37
 * @LastEditors: Please set LastEditors
 */
#ifndef _FRAME_SPI_H_
#define _FRAME_SPI_H_

#include <stdint.h>
#include <stddef.h>

// #define MSP430_SPI_EN
// #define STM32_SPI_EN
// #define LPC17xx_SSP_EN

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MSP430_SPI_EN
#include "driverlib.h"      //MSP430底层包

extern void Drv_SpiInit(void);
extern void Drv_SpiTransData(uint8_t *pTxData, uint16_t size);
extern void Drv_SpiRecvData(uint8_t *pRxData, uint16_t size);
extern void Drv_SpiSendAndRecv(uint8_t *pTxData,uint8_t *pRxData, uint16_t size);
#endif /*MSP430_SPI_EN*/

#ifdef STM32_SPI_EN
#include "stm32l4xx_hal_spi.h"      //STM32 hal spi驱动
#include "stm32l4xx_hal_gpio.h"

extern void Drv_SpiInit(void);
extern void SpiTransData(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
extern void Drv_SpiRecvData(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
extern HAL_StatusTypeDef Drv_SpiSendAndRecv(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size,
                                          uint32_t Timeout);
#endif /*STM32_SPI_EN*/

#ifdef LPC17xx_SSP_EN
#include "lpc17xx.h"
#include "lpc17xx_ssp.h"

extern void Drv_SpiInit(void);
extern void Drv_SpiTransData(uint16_t *pTxData, uint16_t size);
extern void Drv_SpiRecvData(uint16_t *pRxData, uint16_t size);
extern void Drv_SpiSendAndRecv(uint16_t *pTxData,uint16_t *pRxData, uint16_t size);

#endif /*LPC17xx_SSP_EN*/

#ifdef __cplusplus
}
#endif

#endif
