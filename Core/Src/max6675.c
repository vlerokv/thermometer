/*
 * max6675.c
 *
 *  Created on: Jul 24, 2025
 *      Author: misch
 */

#include "max6675.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_spi.h"
#include "stm32g0xx_ll_bus.h"

uint16_t max6675_read_raw_data(SPI_TypeDef *spi_type, GPIO_TypeDef *gpio_type_cs, uint32_t cs_pin_mask) {
    //LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI1);
    LL_GPIO_ResetOutputPin(gpio_type_cs, cs_pin_mask);
    LL_SPI_Enable(spi_type);

    // wait until there is smth to read
    while (!LL_SPI_IsActiveFlag_RXNE(spi_type));
    uint8_t first_byte = LL_SPI_ReceiveData8(spi_type);

    while (!LL_SPI_IsActiveFlag_RXNE(spi_type));
    uint8_t second_byte = LL_SPI_ReceiveData8(spi_type);

    LL_SPI_Disable(spi_type);
    LL_GPIO_SetOutputPin(gpio_type_cs, cs_pin_mask);
    //LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI1);

    return (first_byte << 8) | second_byte;
}

bool max6675_is_thermocouple_connected(uint16_t raw_data) {
    return !(raw_data & (1 << 2));
}

float max6675_convert_to_temperature(uint16_t raw_data) {
    return ((raw_data >> 3) & 0x0FFF) * 0.25;
}

