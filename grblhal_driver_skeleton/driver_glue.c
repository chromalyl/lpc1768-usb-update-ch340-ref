#include "board.h"
#include "my_machine.h"

// -----------------------------------------------------------------------------
// driver_glue.c
// -----------------------------------------------------------------------------
// This file is a skeleton for board initialization glue code.
// The real project should integrate with the target grblHAL driver tree and the
// actual LPCOpen or HAL library implementation.
// -----------------------------------------------------------------------------

extern void hal_gpio_init(void);
extern void hal_uart_init(int port, unsigned int baud);
extern void hal_spi_init(int port, int cs_port, int cs_pin);
extern void hal_timer_init(void);
extern void hal_pwm_init(void);
extern void hal_irq_enable(void);

static void custom_gpio_setup(void)
{
    // TODO: configure X/Y/Z/A/B STEP/DIR/ENABLE pins as outputs.
    // TODO: configure limits/probe/estop inputs with pull-ups/pull-downs and filters.
    // TODO: configure spindle outputs (PWM, DIR, ENABLE) and coolant outputs.
    // TODO: configure UART pins for CH340 and for serial display.
    // TODO: configure SD card CS and card detect pins.
}

static void custom_timer_setup(void)
{
    // TODO: initialize hardware timer(s) used for step pulse generation.
    // TODO: attach timer interrupts to the axis stepper ISR.
    // TODO: set timer prescalers and compare values according to the target motion rate.
}

static void custom_uart_setup(void)
{
    // UART0: CH340 USB-UART firmware update / command console
    // UART1: TTL display
    // UART2: communication to secondary MCU for A/B axis generation
    hal_uart_init(0, 115200);
    hal_uart_init(1, 115200);
    hal_uart_init(2, 115200);
}

static void custom_spi_setup(void)
{
    // microSD uses SPI. Configure the correct LPC1768 SPI peripheral.
    hal_spi_init(0, SD_CS_PORT, SD_CS_PIN);
}

void driver_init(void)
{
    custom_gpio_setup();
    custom_timer_setup();
    custom_uart_setup();
    custom_spi_setup();
    hal_pwm_init();
    hal_irq_enable();
}

// -----------------------------------------------------------------------------
// Example board capabilities
// -----------------------------------------------------------------------------
// These are placeholders; the final firmware should expose the actual board
// capability flags and integrate with grblHAL when the driver is wired in.
// -----------------------------------------------------------------------------

unsigned int board_capability_mask(void)
{
    return 0x00000000U;
}

void board_reset(void)
{
    // TODO: reset external peripherals, disable spindle, disable coolant, set outputs low.
}

void board_enable_axis(uint8_t axis, bool enable)
{
    (void)axis;
    (void)enable;
    // TODO: map axis-level enable to GPIO.
}

void board_set_direction(uint8_t axis, bool clockwise)
{
    (void)axis;
    (void)clockwise;
    // TODO: set axis direction output.
}

void board_set_step(uint8_t axis, bool level)
{
    (void)axis;
    (void)level;
    // TODO: set the hardware step pin output.
}

void board_set_spindle_pwm(uint16_t duty)
{
    (void)duty;
    // TODO: configure PWM duty cycle for spindle.
}

void board_set_coolant_flood(bool on)
{
    (void)on;
    // TODO: drive flood output MOSFET.
}

void board_set_coolant_mist(bool on)
{
    (void)on;
    // TODO: drive mist output MOSFET.
}

bool board_limit_state(uint8_t axis)
{
    (void)axis;
    return false;
    // TODO: return actual limit/probe status.
}

// -----------------------------------------------------------------------------
// Optional secondary-MCU interface for A/B axis generation
// -----------------------------------------------------------------------------
// This can be implemented as UART command exchange or via a simple frame-based
// serial protocol. The actual protocol should be selected based on the chosen
// secondary MCU and the requested update strategy.
// -----------------------------------------------------------------------------

void mc2_axis_update(uint8_t axis, uint32_t step_rate, bool dir, bool enable)
{
    (void)axis;
    (void)step_rate;
    (void)dir;
    (void)enable;
    // TODO: send command to secondary MCU for A/B axis motion generation.
}
