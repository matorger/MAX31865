/*
 * MAX31865.c
 *
 *  Created on: Jan 11, 2021
 *      Author: Mason
 */

#include "MAX31865.h"

uint8_t MAX31864_Initialize(MAX31865 *MAX)
{
	MAX->configuration = 0;
    MAX->configuration |= MAX->v_bias;
    MAX->configuration |= MAX->conversion_mode;
    MAX->configuration |= MAX->rtd_wire;
    MAX->configuration |= MAX->noise_filter;

    MAX31864_WriteReg(MAX, CONFIGURATION_REG, MAX->configuration);
    return 0;
}

float MAX31864_ReadResistance(MAX31865 *MAX)
{
	unsigned int rtd = 0;
	float rtd_resistance = 0.0;
	uint8_t read_byte = 0;

	read_byte = MAX31864_ReadReg(MAX, RTD_MSB_REG);
	rtd = read_byte <<8;
	read_byte = MAX31864_ReadReg(MAX, RTD_LSB_REG);
	rtd |= read_byte;
	rtd_resistance = (rtd * REF_RESISTOR) / 32768.0;

    return rtd_resistance;
}

float MAX31864_ReadTemp(MAX31865 *MAX)
{
	float rtd_resistance = 0.0;
	float temp = 0.0;

	rtd_resistance = MAX31864_ReadResistance(MAX);
	temp = (2.5291 * rtd_resistance) - 252.95;

	if(MAX->units == FAHRENHEIT)
	{
		temp = (temp * 9 / 5) + 32;
	}

    return temp;
}

float MAX31864_ReadTempPoly(MAX31865 *MAX)
{
	float rtd_resistance = 0.0;
	float temp = 0.0;


	rtd_resistance = MAX31864_ReadResistance(MAX);

	float R = rtd_resistance - 100;
	float R2 = R * R;
	float R3 = R2 * R;
	float R4 = R3 * R;

	R *= 4.60488;
	R2 *= 1.783157E-3;
	R3 *= 5.946734E-7;
	R4 *= 5.170783E-9;

	temp = (R4+R3+R2+R+31.999282);

	//if(MAX->units == FAHRENHEIT)
	//{
	//	temp = (temp * 9 / 5) + 32;
	//}

    return temp;
}


uint8_t MAX31864_WriteReg(MAX31865 *MAX, uint8_t wrAddr, uint8_t wrData)
{
    MAX->txBuffer[0] = wrAddr | 0x80;
    MAX->txBuffer[1] = wrData;

    MAX31864_ChipSelectLow();
    HAL_SPI_Transmit(&MAX->spi, MAX->txBuffer, 2, 100);
    MAX31864_ChipSelectHigh();

    return 0;
}

uint8_t MAX31864_ReadReg(MAX31865 *MAX, uint8_t rAddr)
{
    MAX->txBuffer[0] = rAddr;

    MAX31864_ChipSelectLow();
    HAL_SPI_Receive(&MAX->spi, MAX->txBuffer, 2, 100);
    MAX31864_ChipSelectHigh();

    return MAX->txBuffer[1];
}

uint8_t MAX31864_ChipSelectHigh()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
	return 0;
}

uint8_t MAX31864_ChipSelectLow()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	return 0;
}
