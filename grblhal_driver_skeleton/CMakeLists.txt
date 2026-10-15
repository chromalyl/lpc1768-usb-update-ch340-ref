cmake_minimum_required(VERSION 3.16)

project(grblhal_lpc1768_driver_skeleton C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(grblhal_driver_skeleton STATIC
    driver_glue.c
)

target_include_directories(grblhal_driver_skeleton
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# -----------------------------------------------------------------------------
# Integration notes for the real grblHAL project:
#   - Add this directory or its sources into the grblHAL/LPC176x target.
#   - Map the board.h and my_machine.h definitions to the actual board.
#   - Ensure the selected LPC1768 timers and UART peripherals match your PCB.
# -----------------------------------------------------------------------------
