/*
 * @Description: SPI 接口
 * @Author: land sea
 * @Date: 2019-11-18 20:43:34
 * @LastEditTime: 2019-11-19 08:42:47
 * @LastEditors: Please set LastEditors
 */
#ifndef _FRAME_SPI_H_
#define _FRAME_SPI_H_

#include <stdint.h>
#include <stddef.h>

// #define MSP430_SPI_EN
#define STM32_SPI_EN
// #define LPC17_SSP_EN

#ifdef __cplusplus
extern "C" {
#endif

extern void Drv_SpiInit(void);
extern void Drv_SpiTransData(uint8_t *pTxData, uint16_t size);
extern void Drv_SpiRecvData(uint8_t *pRxData, uint16_t size);
extern void Drv_SpiSendAndRecv(uint8_t *pTxData,uint8_t *pRxData, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif
