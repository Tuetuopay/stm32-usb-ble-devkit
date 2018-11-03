/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#ifndef BOARD_H
#define BOARD_H

/*
 * Setup for STM32 F205 USB+BLE devkit
 */

/*
 * Board identifier.
 */
#define BOARD_STM32_USB_BLE_DEVKIT
#define BOARD_NAME                  "STM32 USB+BLE Devkit"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                8000000U
#endif

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   330U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F205xx

/*
 * IO pins assignments.
 */
#define GPIOA_PIN0                  0U
#define GPIOA_PIN1                  1U
#define GPIOA_PIN2                  2U
#define GPIOA_SPI_CS                3U
#define GPIOA_SPI_IRQ               4U
#define GPIOA_SPI_SCK               5U
#define GPIOA_SPI_MISO              6U
#define GPIOA_SPI_MOSI              7U
#define GPIOA_PIN8                  8U
#define GPIOA_USB_FS_VBUS           9U
#define GPIOA_USB_FS_ID             10U
#define GPIOA_USB_FS_DM             11U
#define GPIOA_USB_FS_DP             12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_PIN15                 15U

#define GPIOB_DBG_P0                0U
#define GPIOB_DBG_P1                1U
#define GPIOB_DBG_P2                2U
#define GPIOB_SWO                   3U
#define GPIOB_DBG_TP0               4U
#define GPIOB_DBG_TP1               5U
#define GPIOB_TX                    6U
#define GPIOB_RX                    7U
#define GPIOB_DBG_TP2               8U
#define GPIOB_DBG_TP3               9U
#define GPIOB_DBG_P3                10U
#define GPIOB_PIN11                 11U
#define GPIOB_USB_HS_ID             12U
#define GPIOB_USB_HS_VBUS           13U
#define GPIOB_USB_HS_DM             14U
#define GPIOB_USB_HS_DP             15U

#define GPIOC_PIN0                  0U
#define GPIOC_PIN1                  1U
#define GPIOC_PIN2                  2U
#define GPIOC_PIN3                  3U
#define GPIOC_PIN4                  4U
#define GPIOC_PIN5                  5U
#define GPIOC_LED0                  6U
#define GPIOC_LED1                  7U
#define GPIOC_LED2                  8U
#define GPIOC_LED3                  9U
#define GPIOC_STM2NRF               10U
#define GPIOC_NRF2STM               11U
#define GPIOC_PIN12                 12U
#define GPIOC_PIN13                 13U
#define GPIOC_PIN14                 14U
#define GPIOC_PIN15                 15U

#define GPIOD_PIN0                  0U
#define GPIOD_PIN1                  1U
#define GPIOD_PIN2                  2U
#define GPIOD_PIN3                  3U
#define GPIOD_PIN4                  4U
#define GPIOD_PIN5                  5U
#define GPIOD_PIN6                  6U
#define GPIOD_PIN7                  7U
#define GPIOD_PIN8                  8U
#define GPIOD_PIN9                  9U
#define GPIOD_PIN10                 10U
#define GPIOD_PIN11                 11U
#define GPIOD_PIN12                 12U
#define GPIOD_PIN13                 13U
#define GPIOD_PIN14                 14U
#define GPIOD_PIN15                 15U

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U

/*
 * IO lines assignments.
 */
#define LINE_SPI_CS                 PAL_LINE(GPIOA, 3U)
#define LINE_SPI_IRQ                PAL_LINE(GPIOA, 4U)
#define LINE_SPI_SCK                PAL_LINE(GPIOA, 5U)
#define LINE_SPI_MISO               PAL_LINE(GPIOA, 6U)
#define LINE_SPI_MOSI               PAL_LINE(GPIOA, 7U)
#define LINE_USB_FS_VBUS            PAL_LINE(GPIOA, 9U)
#define LINE_USB_FS_ID              PAL_LINE(GPIOA, 10U)
#define LINE_USB_FS_DM              PAL_LINE(GPIOA, 11U)
#define LINE_USB_FS_DP              PAL_LINE(GPIOA, 12U)
#define LINE_SWDIO                  PAL_LINE(GPIOA, 13U)
#define LINE_SWCLK                  PAL_LINE(GPIOA, 14U)

#define LINE_DBG_P0                 PAL_LINE(GPIOB, 0U)
#define LINE_DBG_P1                 PAL_LINE(GPIOB, 1U)
#define LINE_DBG_P2                 PAL_LINE(GPIOB, 2U)
#define LINE_SWO                    PAL_LINE(GPIOB, 3U)
#define LINE_DBG_TP0                PAL_LINE(GPIOB, 4U)
#define LINE_DBG_TP1                PAL_LINE(GPIOB, 5U)
#define LINE_TX                     PAL_LINE(GPIOB, 6U)
#define LINE_RX                     PAL_LINE(GPIOB, 7U)
#define LINE_DBG_TP2                PAL_LINE(GPIOB, 8U)
#define LINE_DBG_TP3                PAL_LINE(GPIOB, 9U)
#define LINE_DBG_P3                 PAL_LINE(GPIOB, 10U)
#define LINE_USB_HS_ID              PAL_LINE(GPIOB, 12U)
#define LINE_USB_HS_VBUS            PAL_LINE(GPIOB, 13U)
#define LINE_USB_HS_DM              PAL_LINE(GPIOB, 14U)
#define LINE_USB_HS_DP              PAL_LINE(GPIOB, 15U)

#define LINE_LED0                   PAL_LINE(GPIOC, 6U)
#define LINE_LED1                   PAL_LINE(GPIOC, 7U)
#define LINE_LED2                   PAL_LINE(GPIOC, 8U)
#define LINE_LED3                   PAL_LINE(GPIOC, 9U)
#define LINE_STM2NRF                PAL_LINE(GPIOC, 10U)
#define LINE_NRF2STM                PAL_LINE(GPIOC, 11U)

#define LINE_OSC_IN                 PAL_LINE(GPIOH, 0U)
#define LINE_OSC_OUT                PAL_LINE(GPIOH, 1U)

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA13 - SWDIO                     (alternate 0)
 * PA14 - SWCLK                     (alternate 0)
 *
 * All others input floating.
 * Output set to pushpull, high speed
 */
#define VAL_GPIOA_MODER             (PIN_MODE_ALTERNATE(GPIOA_SWDIO) | \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK))
#define VAL_GPIOA_OTYPER            0
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_SWDIO) | \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK))
#define VAL_GPIOA_PUPDR             0
#define VAL_GPIOA_ODR               0
#define VAL_GPIOA_AFRL              0
#define VAL_GPIOA_AFRH              0

/*
 * GPIOB setup:
 *
 * All input floating.
 * Output set to pushpull, high speed
 */
#define VAL_GPIOB_MODER             0
#define VAL_GPIOB_OTYPER            0
#define VAL_GPIOB_OSPEEDR           0
#define VAL_GPIOB_PUPDR             0
#define VAL_GPIOB_ODR               0
#define VAL_GPIOB_AFRL              0
#define VAL_GPIOB_AFRH              0

/*
 * GPIOC setup:
 *
 * All input floating.
 * Output set to pushpull, high speed
 */
#define VAL_GPIOC_MODER             0
#define VAL_GPIOC_OTYPER            0
#define VAL_GPIOC_OSPEEDR           0
#define VAL_GPIOC_PUPDR             0
#define VAL_GPIOC_ODR               0
#define VAL_GPIOC_AFRL              0
#define VAL_GPIOC_AFRH              0

/*
 * GPIOD setup:
 *
 * All input floating.
 * Output set to pushpull, high speed
 */
#define VAL_GPIOD_MODER             0
#define VAL_GPIOD_OTYPER            0
#define VAL_GPIOD_OSPEEDR           0
#define VAL_GPIOD_PUPDR             0
#define VAL_GPIOD_ODR               0
#define VAL_GPIOD_AFRL              0
#define VAL_GPIOD_AFRH              0

/*
 * GPIOE setup:
 *
 * All input floating.
 * Output set to pushpull, high speed
 */
#define VAL_GPIOE_MODER             0
#define VAL_GPIOE_OTYPER            0
#define VAL_GPIOE_OSPEEDR           0
#define VAL_GPIOE_PUPDR             0
#define VAL_GPIOE_ODR               0
#define VAL_GPIOE_AFRL              0
#define VAL_GPIOE_AFRH              0

/*
 * GPIOF setup:
 *
 * All input floating.
 * Output set to pushpull, high speed
 */
#define VAL_GPIOF_MODER             0
#define VAL_GPIOF_OTYPER            0
#define VAL_GPIOF_OSPEEDR           0
#define VAL_GPIOF_PUPDR             0
#define VAL_GPIOF_ODR               0
#define VAL_GPIOF_AFRL              0
#define VAL_GPIOF_AFRH              0

/*
 * GPIOG setup:
 *
 * All input floating.
 * Output set to pushpull, high speed
 */
#define VAL_GPIOG_MODER             0
#define VAL_GPIOG_OTYPER            0
#define VAL_GPIOG_OSPEEDR           0
#define VAL_GPIOG_PUPDR             0
#define VAL_GPIOG_ODR               0
#define VAL_GPIOG_AFRL              0
#define VAL_GPIOG_AFRH              0

/*
 * GPIOH setup:
 *
 * All input floating.
 * Output set to pushpull, high speed
 */
#define VAL_GPIOH_MODER             0
#define VAL_GPIOH_OTYPER            0
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_OSC_IN) | \
                                     PIN_OSPEED_HIGH(GPIOH_OSC_OUT))
#define VAL_GPIOH_PUPDR             0
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_OSC_IN) | \
                                     PIN_ODR_HIGH(GPIOH_OSC_OUT))
#define VAL_GPIOH_AFRL              0
#define VAL_GPIOH_AFRH              0

/*
 * GPIOI setup:
 *
 * All input floating.
 * Output set to pushpull, high speed
 */
#define VAL_GPIOI_MODER             0
#define VAL_GPIOI_OTYPER            0
#define VAL_GPIOI_OSPEEDR           0
#define VAL_GPIOI_PUPDR             0
#define VAL_GPIOI_ODR               0
#define VAL_GPIOI_AFRL              0
#define VAL_GPIOI_AFRH              0

/*
 * GPIOJ setup:
 *
 * All input floating.
 * Output set to pushpull, high speed
 */
#define VAL_GPIOJ_MODER             0
#define VAL_GPIOJ_OTYPER            0
#define VAL_GPIOJ_OSPEEDR           0
#define VAL_GPIOJ_PUPDR             0
#define VAL_GPIOJ_ODR               0
#define VAL_GPIOJ_AFRL              0
#define VAL_GPIOJ_AFRH              0

/*
 * GPIOK setup:
 *
 * All input floating.
 * Output set to pushpull, high speed
 */
#define VAL_GPIOK_MODER             0
#define VAL_GPIOK_OTYPER            0
#define VAL_GPIOK_OSPEEDR           0
#define VAL_GPIOK_PUPDR             0
#define VAL_GPIOK_ODR               0
#define VAL_GPIOK_AFRL              0
#define VAL_GPIOK_AFRH              0

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
