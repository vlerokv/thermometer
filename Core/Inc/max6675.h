/*
 * max6675.h
 *
 *  Created on: Jul 24, 2025
 *      Author: misch
 */

#ifndef INC_MAX6675_H_
#define INC_MAX6675_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32g031xx.h"

bool max6675_is_thermocouple_connected(uint16_t raw_data);

uint16_t max6675_read_raw_data(SPI_TypeDef *spi_type, GPIO_TypeDef *gpio_type_cs, uint32_t cs_pin_mask);

float max6675_convert_to_temperature(uint16_t raw_data);

#endif /* INC_MAX6675_H_ */
