/* name=grblhal_driver_skeleton/board_stc32g.h
   Concrete pin map draft for STC32G144K246 (assumed LQFP100).
   IMPORTANT: Verify each line marked [REQUIRE VERIFY] against the datasheet pin-mux table for the chosen package.
*/
#ifndef BOARD_STC32G_H
#define BOARD_STC32G_H

#include <stdint.h>
#include <stdbool.h>

#define BOARD_NAME "STC32G144K246_LQFP100"
#define BOARD_VOLTAGE_MV 3300

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2
#define AXIS_A 3
#define AXIS_B 4
#define NUM_AXES 5

// --- Timer assignments (logical mapping: Timer0..Timer4 used for STEP generation)
// NOTE: Ensure those timers support PWM/OC output mapping to the chosen STEP pins.
#define AXIS_X_TIMER   0  // Timer0 -> X STEP
#define AXIS_Y_TIMER   1  // Timer1 -> Y STEP
#define AXIS_Z_TIMER   2  // Timer2 -> Z STEP
#define AXIS_A_TIMER   3  // Timer3 -> A STEP (optional)
#define AXIS_B_TIMER   4  // Timer4 -> B STEP (optional)

// --- STEP / DIR / EN pins (selected from PWM-capable pins per pin-mux table)
// X/Y/Z/A chosen from PWMA group (P2.x, P6.x etc) to use hardware PWM/OC outputs.
#define X_STEP_PIN   P2_0   // PWMA candidate (PWMA group includes P2.0..P2.3) [REQUIRE VERIFY: Timer0 -> P2.0 mapping]
#define X_DIR_PIN    P0_0
#define X_EN_PIN     P0_1

#define Y_STEP_PIN   P2_1   // PWMA candidate [REQUIRE VERIFY: Timer1 -> P2.1 mapping]
#define Y_DIR_PIN    P0_2
#define Y_EN_PIN     P0_3

#define Z_STEP_PIN   P2_2   // PWMA candidate [REQUIRE VERIFY: Timer2 -> P2.2 mapping]
#define Z_DIR_PIN    P0_4
#define Z_EN_PIN     P0_5

#define A_STEP_PIN   P2_3   // PWMA candidate [REQUIRE VERIFY: Timer3 -> P2.3 mapping]
#define A_DIR_PIN    P0_6
#define A_EN_PIN     P0_7

#define B_STEP_PIN   P6_0   // PWMA alternative (P6.0..P6.3 also listed) [REQUIRE VERIFY: Timer4 -> P6.0 mapping]
#define B_DIR_PIN    P1_0
#define B_EN_PIN     P1_1

// --- Spindle ---
#define SPINDLE_PWM_PIN   P8_0   // choose PWMC group pin for spindle PWM [REQUIRE VERIFY: PWM channel availability]
#define SPINDLE_PWM_TIMER 5      // Timer5 (use PWMC output mapping)
#define SPINDLE_DIR_PIN   P8_1
#define SPINDLE_EN_PIN    P8_2
#define SPINDLE_TACH_PIN  P6_4   // input capture candidate [REQUIRE VERIFY]

// --- Limits / probe / estop (general-purpose pins)
#define X_MIN_PIN  P4_4
#define X_MAX_PIN  P4_5
#define Y_MIN_PIN  P4_6
#define Y_MAX_PIN  P4_7
#define Z_MIN_PIN  P7_0
#define Z_MAX_PIN  P7_1
#define PROBE_PIN  P7_2
#define ESTOP_PIN  P7_3

// --- UARTs (selected from pin-mux alternatives) ---
// USART1: host (PC via CH340 or direct USB if using USB-CDC). Using P3.1 (Tx) / P3.0 (Rx) mapping
#define HOST_UART_NUM   1
#define HOST_UART_TX    P3_1   // TxD (USART1) [REQUIRE VERIFY if used as SWD/USB conflict]
#define HOST_UART_RX    P3_0   // RxD (USART1) [REQUIRE VERIFY]

// USART2: display TTL (choose P1.1 / P1.0)
#define DISP_UART_NUM   2
#define DISP_UART_TX    P1_1   // TxD2
#define DISP_UART_RX    P1_0   // RxD2

// USART3: optional MCU2 comms (use P8.6 / P8.7 as alternate TxD3 / RxD3)
#define MCU2_UART_NUM   3
#define MCU2_UART_TX    P8_6   // TxD3 alternative [REQUIRE VERIFY]
#define MCU2_UART_RX    P8_7   // RxD3 alternative [REQUIRE VERIFY]

// --- SPI for SD (use P3.2..P3.5 mapping block as SPI)
// According to table: P3.2 SCLK, P3.3 MISO, P3.4 MOSI, P3.5 SS (one common SPI mapping set)
#define SD_SPI_NUM    1
#define SD_SCK_PIN    P3_2   // SCLK (SPI)
#define SD_MOSI_PIN   P3_4   // MOSI (SPI) [note: MOSI/MISO may be swappable]
#define SD_MISO_PIN   P3_3   // MISO (SPI)
#define SD_CS_PIN     P3_5   // CS
#define SD_CD_PIN     P5_4   // card detect candidate (P5.4 appears in SPI alt list) [REQUIRE VERIFY]

// --- SWD pins ---
// Datasheet: SWD on P3.0/P3.1; but these also used above for USART1 and USB D+/D-.
// You must decide whether to reserve P3.0/P3.1 for SWD during development or for USB/USART in production.
#define SWD_SWDIO_PIN  P3_0   // [REQUIRE VERIFY / conflict with USB / USART1]
#define SWD_SWCLK_PIN  P3_1   // [REQUIRE VERIFY / conflict]

// --- USB D+/D- pins (per datasheet: P3.1 = D+, P3.0 = D-) ---
#define USB_DP_PIN P3_1   // D+  [REQUIRE VERIFY: if USB used, SWD may be unavailable]
#define USB_DM_PIN P3_0   // D-  [REQUIRE VERIFY]

// Notes:
// - Many pins have multiple alternate functions. Confirm final choices with the chip's pin multiplex table for LQFP100.
// - If you want SWD permanently available, you may assign HOST_UART to other pins (USART1 has other alternate pins).
// - If some chosen PWM pins cannot be driven by the timers we assigned, reassign timers to match pin-mux rules.

#endif // BOARD_STC32G_H
