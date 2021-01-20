/*
 * MAX31865.h
 *
 *  Created on: Jan 11, 2021
 *      Author: Mason
 */

#ifndef INC_MAX31865_H_
#define INC_MAX31865_H_

#include "main.h"
#include "stdio.h"
#include "MAX31865_Definitions.h"

typedef struct
{
	SPI_HandleTypeDef				spi;
	uint8_t							configuration;
	Bias							v_bias;
	Conversion						conversion_mode;
	Wire							rtd_wire;
	Filter							noise_filter;
	Temp_Units						units;
    int16_t                         temperature;
    uint8_t                         txBuffer[MAX_SPI_TX_BUFFER_SIZE];
    uint8_t                         rxBuffer[MAX_SPI_RX_BUFFER_SIZE];
}MAX31865;

uint8_t MAX31864_Initialize(MAX31865 *MAX);
float MAX31864_ReadResistance(MAX31865 *MAX);
float MAX31864_ReadTemp(MAX31865 *MAX);
float MAX31864_ReadTempPoly(MAX31865 *MAX);
uint8_t MAX31864_WriteReg(MAX31865 *MAX, uint8_t wrAddr, uint8_t wrData);
uint8_t MAX31864_ReadReg(MAX31865 *MAX, uint8_t rAddr);
uint8_t MAX31864_ChipSelectHigh();
uint8_t MAX31864_ChipSelectLow();



#endif /* INC_MAX31865_H_ */
