#ifndef __MC2_PROTOCOL_H__
#define __MC2_PROTOCOL_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Secondary MCU protocol (binary framed) for A/B axis step generator
// UART-based, little-endian payload, CRC16 at end

#define MC2_FRAME_START      0xAA
#define MC2_FRAME_VERSION    0x01
#define MC2_MAX_PAYLOAD      16

typedef enum {
    MC2_CMD_NOP = 0x00,
    MC2_CMD_HELLO = 0x01,

    MC2_CMD_ENABLE_AXIS = 0x10,
    MC2_CMD_DISABLE_AXIS = 0x11,
    MC2_CMD_SET_DIR = 0x12,
    MC2_CMD_SET_STEP_RATE = 0x13,
    MC2_CMD_START_PULSE = 0x14,
    MC2_CMD_STOP_PULSE = 0x15,
    MC2_CMD_SET_MICROSTEP = 0x16,

    MC2_CMD_GET_STATUS = 0x20,
    MC2_CMD_STATUS = 0x21,
    MC2_CMD_FAULT = 0x22,

    MC2_CMD_RESET = 0x30,
    MC2_CMD_ESTOP = 0x31
} mc2_cmd_t;

// Status flags
#define MC2_STATUS_FLAG_ENABLED   (1 << 0)
#define MC2_STATUS_FLAG_FAULT     (1 << 1)
#define MC2_STATUS_FLAG_HOMED     (1 << 2)

// Protocol frame (on-wire):
// [start=0xAA][ver][msg_type][axis][len][payload...][crc_lo][crc_hi]

// API
void mc2_init(uint8_t uart_num, uint32_t baud);

// High-level commands
bool mc2_enable_axis(uint8_t axis);
bool mc2_disable_axis(uint8_t axis);
bool mc2_set_direction(uint8_t axis, bool dir);
bool mc2_set_step_rate(uint8_t axis, uint32_t step_rate);
bool mc2_start_pulse(uint8_t axis);
bool mc2_stop_pulse(uint8_t axis);

// Polling: call regularly from main loop to process rx and timeouts
void mc2_process(void);

// Query last known status
bool mc2_get_status(uint8_t axis, uint8_t *status_flags, uint32_t *current_rate);

#ifdef __cplusplus
}
#endif

#endif // __MC2_PROTOCOL_H__
