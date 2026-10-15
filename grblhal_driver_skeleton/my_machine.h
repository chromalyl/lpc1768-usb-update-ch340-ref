#ifndef __MY_MACHINE_H__
#define __MY_MACHINE_H__

// -----------------------------------------------------------------------------
// Example compile-time features for a custom LPC1768 controller.
// -----------------------------------------------------------------------------
// This header is a template for enabling features and board options in a
// grblHAL build. It intentionally mirrors commonly used grblHAL config macros.
// -----------------------------------------------------------------------------

#ifndef USB_SERIAL_CDC
#define USB_SERIAL_CDC           1
#endif

#ifndef SDCARD_ENABLE
#define SDCARD_ENABLE            1
#endif

#ifndef EEPROM_ENABLE
#define EEPROM_ENABLE            0
#endif

#ifndef LIMIT_MAX_ENABLE
#define LIMIT_MAX_ENABLE         0
#endif

#ifndef CONTROL_ENABLE
#define CONTROL_ENABLE           (CONTROL_HALT | CONTROL_FEED_HOLD | CONTROL_CYCLE_START)
#endif

#ifndef DISPLAY_ENABLE
#define DISPLAY_ENABLE           1
#endif

#ifndef SPINDLE_ENABLE
#define SPINDLE_ENABLE           1
#endif

#ifndef COOLANT_ENABLE
#define COOLANT_ENABLE           1
#endif

#ifndef PROBE_ENABLE
#define PROBE_ENABLE             1
#endif

#ifndef MPG_ENABLE
#define MPG_ENABLE               0
#endif

#ifndef TRINAMIC_ENABLE
#define TRINAMIC_ENABLE          0
#endif

#ifndef UART0_SERIAL_PORT
#define UART0_SERIAL_PORT       0
#endif

#ifndef UART1_SERIAL_PORT
#define UART1_SERIAL_PORT       1
#endif

#ifndef UART2_SERIAL_PORT
#define UART2_SERIAL_PORT       2
#endif

// -----------------------------------------------------------------------------
// Build flags for the current board
// -----------------------------------------------------------------------------
#define BOARD_CUSTOM_LPC1768     1
#define USE_SECONDARY_AXIS_MCU  1
#define SD_CARD_GCODE_STREAM     1
#define SERIAL_DISPLAY_ENABLE    1
#define CH340_USB_UART_ENABLE     1

// -----------------------------------------------------------------------------
// Optional spindle modes
// -----------------------------------------------------------------------------
// Use PWM spindle by default. Replace as required by the final hardware.
#define SPINDLE_PWM_MODE         1
#define SPINDLE_DIR_MODE         1

// -----------------------------------------------------------------------------
// Machine config summary
// -----------------------------------------------------------------------------
#define AXIS_X                  0
#define AXIS_Y                  1
#define AXIS_Z                  2
#define AXIS_A                  3
#define AXIS_B                  4

#define N_AXIS                  5
#define N_COOR                  5

#define MAX_AXIS_LIMITS         6

#endif /* __MY_MACHINE_H__ */
