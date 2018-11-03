/*
    Copyright (C) 2015 Fabio Utzig

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

#ifndef _BOARD_H_
#define _BOARD_H_

/* Board identifier. */
#define BOARD_STM32_USB_BLE_DEVKIT
#define BOARD_NAME              "STM32+nRF51 USB+BLE Devkit"

/* Board oscillators-related settings. */
#define NRF51_XTAL_VALUE        16000000

/* GPIO pins. */
#define DBG_TP3        1
#define DBG_TP2        2
#define DBG_TP1        3
#define DBG_TP0        4
#define SPI_CS         5
#define SPI_IRQ        6
#define SPI_SCK        7
#define SPI_MISO       8
#define SPI_MOSI       9
#define UART_RX        11
#define UART_TX        12
#define DBG_P0         13
#define DBG_P1         14
#define DBG_P2         15
#define DBG_P3         16
#define LED0           22
#define LED1           23
#define LED2           24
#define LED3           25

/*
 * IO pins assignments.
 */
#define IOPORT1_DBG_TP3        1U
#define IOPORT1_DBG_TP2        2U
#define IOPORT1_DBG_TP1        3U
#define IOPORT1_DBG_TP0        4U
#define IOPORT1_SPI_CS         5U
#define IOPORT1_SPI_IRQ        6U
#define IOPORT1_SPI_SCK        7U
#define IOPORT1_SPI_MISO       8U
#define IOPORT1_SPI_MOSI       9U
#define IOPORT1_UART_RX        11U
#define IOPORT1_UART_TX        12U
#define IOPORT1_DBG_P0         13U
#define IOPORT1_DBG_P1         14U
#define IOPORT1_DBG_P2         15U
#define IOPORT1_DBG_P3         16U
#define IOPORT1_LED0           22U
#define IOPORT1_LED1           23U
#define IOPORT1_LED2           24U
#define IOPORT1_LED3           25U

/*
 * IO lines assignments.
 */
#define LINE_DBG_TP3        PAL_LINE(IOPORT1, 1U)
#define LINE_DBG_TP2        PAL_LINE(IOPORT1, 2U)
#define LINE_DBG_TP1        PAL_LINE(IOPORT1, 3U)
#define LINE_DBG_TP0        PAL_LINE(IOPORT1, 4U)
#define LINE_SPI_CS         PAL_LINE(IOPORT1, 5U)
#define LINE_SPI_IRQ        PAL_LINE(IOPORT1, 6U)
#define LINE_SPI_SCK        PAL_LINE(IOPORT1, 7U)
#define LINE_SPI_MISO       PAL_LINE(IOPORT1, 8U)
#define LINE_SPI_MOSI       PAL_LINE(IOPORT1, 9U)
#define LINE_UART_RX        PAL_LINE(IOPORT1, 11U)
#define LINE_UART_TX        PAL_LINE(IOPORT1, 12U)
#define LINE_DBG_P0         PAL_LINE(IOPORT1, 13U)
#define LINE_DBG_P1         PAL_LINE(IOPORT1, 14U)
#define LINE_DBG_P2         PAL_LINE(IOPORT1, 15U)
#define LINE_DBG_P3         PAL_LINE(IOPORT1, 16U)
#define LINE_LED0           PAL_LINE(IOPORT1, 22U)
#define LINE_LED1           PAL_LINE(IOPORT1, 23U)
#define LINE_LED2           PAL_LINE(IOPORT1, 24U)
#define LINE_LED3           PAL_LINE(IOPORT1, 25U)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
