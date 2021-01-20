/*
 * MAX31865_Definitions.h
 *
 *  Created on: Jan 11, 2021
 *      Author: Mason
 */

#ifndef INC_MAX31865_DEFINITIONS_H_
#define INC_MAX31865_DEFINITIONS_H_

#define REF_RESISTOR 		428

#define MAX_SPI_TX_BUFFER_SIZE 30
#define MAX_SPI_RX_BUFFER_SIZE 30

#define CONFIGURATION_REG 	0x00
#define RTD_MSB_REG 		0x01
#define RTD_LSB_REG 		0x02

typedef enum
{
	OFF,
	ON = 0b10000000
}Bias;

typedef enum
{
	NORMALLY_OFF,
	AUTO = 0b1000000
}Conversion;

typedef enum
{
	TWO_OR_FOUR_WIRE,
	THREE_WIRE = 0b10000
}Wire;

typedef enum
{
	SIXTY_HZ,
	FIFTY_HZ = 0b1
}Filter;

typedef enum
{
	CELSIUS,
	FAHRENHEIT
}Temp_Units;

#endif /* INC_MAX31865_DEFINITIONS_H_ */
