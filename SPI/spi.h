/*
 * @Description: SPI 接口
 * @Author: land sea
 * @Date: 2019-11-18 20:43:34
 * @LastEditTime: 2019-11-18 20:57:02
 * @LastEditors: Please set LastEditors
 */
#ifndef _FRAME_SPI_H_
#define _FRAME_SPI_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void Drv_SpiInit(void);
extern void Drv_SpiTransData(uint8_t *pTxData, uint16_t size);
extern void Drv_SpiRecvData(uint8_t *pRxData, uint16_t size);
extern void Drv_SpiSpeedChanged(uint8_t speed);

#ifdef __cplusplus
}
#endif

#endif
