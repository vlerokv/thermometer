/*
 * max6675.h
 *
 *  Created on: Jul 24, 2025
 *      Author: misch
 */



#ifndef INC_MAX6675_H_
#define INC_MAX6675_H_

uint8_t max6675_check_thermocouple(uint16_t raw_data);

uint16_t max6675_read_raw_data(SPI_TypeDef *spi_type, GPIO_TypeDef *gpio_type_cs, uint32 cs_pin_mask);

int max6675_convert_to_temperature();

#endif /* INC_MAX6675_H_ */
