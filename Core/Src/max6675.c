 /*
 * max6675.c
 *
 *  Created on: Jul 24, 2025
 *      Author: misch
 */

#include "max6675.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_spi.h"

uint16_t max6675_read_raw_data(SPI_TypeDef *spi_type, GPIO_TypeDef *gpio_type_cs, uint32_t cs_pin_mask)
{
	uint8_t first_byte;
	uint8_t second_byte;
	uint16_t raw_data;

	LL_GPIO_ResetOutputPin(gpio_type_cs, cs_pin_mask);
	 LL_SPI_Enable(SPI1);



	// wait until there is smth to read
	while(!LL_SPI_IsActiveFlag_RXNE(spi_type));
	first_byte = LL_SPI_ReceiveData8(spi_type);


	while(!LL_SPI_IsActiveFlag_RXNE(spi_type));
	second_byte = LL_SPI_ReceiveData8(spi_type);

	LL_SPI_Disable(spi_type);

	LL_GPIO_SetOutputPin(gpio_type_cs, cs_pin_mask);

	raw_data = (first_byte << 8) | second_byte;

	return raw_data;
}

uint8_t max6675_check_thermocouple(uint16_t raw_data)
{
	uint8_t d2;

	d2 = (raw_data >> 2) & 0x01;

	return d2;
}

float max6675_convert_to_temperature(uint16_t raw_data)
{
	uint16_t raw_temp;
	float temperature_celsius;
	raw_temp = (raw_data >> 3) & 0x0FFF;

	temperature_celsius = raw_temp * 0.25;

	return temperature_celsius;

}

