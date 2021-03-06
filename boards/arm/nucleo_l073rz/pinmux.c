/*
 * Copyright (c) 2018 Ilya Tagunov <tagunil@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for NUCLEO-L073RZ board */
static const struct pin_config pinconf[] = {
#if DT_HAS_NODE(DT_NODELABEL(usart1))
	{STM32_PIN_PB6, STM32L0_PINMUX_FUNC_PB6_USART1_TX},
	{STM32_PIN_PB7, STM32L0_PINMUX_FUNC_PB7_USART1_RX},
#endif
#if DT_HAS_NODE(DT_NODELABEL(usart2))
	{STM32_PIN_PA2, STM32L0_PINMUX_FUNC_PA2_USART2_TX},
	{STM32_PIN_PA3, STM32L0_PINMUX_FUNC_PA3_USART2_RX},
#endif
#if DT_HAS_NODE(DT_NODELABEL(i2c1))
	{STM32_PIN_PB8, STM32L0_PINMUX_FUNC_PB8_I2C1_SCL},
	{STM32_PIN_PB9, STM32L0_PINMUX_FUNC_PB9_I2C1_SDA},
#endif
#if DT_HAS_NODE(DT_NODELABEL(spi1))
	{STM32_PIN_PA5, STM32L0_PINMUX_FUNC_PA5_SPI1_SCK},
	{STM32_PIN_PA6, STM32L0_PINMUX_FUNC_PA6_SPI1_MISO},
	{STM32_PIN_PA7, STM32L0_PINMUX_FUNC_PA7_SPI1_MOSI},
#endif
#ifdef CONFIG_ADC_1
	{STM32_PIN_PA0, STM32L0_PINMUX_FUNC_PA0_ADC_IN0},
#endif /* CONFIG_ADC_1 */
#if DT_HAS_NODE(DT_NODELABEL(dac1))
	{STM32_PIN_PA4, STM32L0_PINMUX_FUNC_PA4_DAC_OUT1},
#endif /* dac1 */
};

static int pinmux_stm32_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
	 CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
