# Integrated reference schematic — LPC1768 5-axis controller (draft)

This repository file contains a reference schematic draft (textual) for a custom LPC1768-based controller supporting:

- LPC1768 main MCU (3.3V)
- 5-axis step/dir stepper control (X/Y/Z from LPC1768, A/B from secondary MCU)
- microSD (SPI) for offline G-code
- CH340 USB-UART bridge for firmware update (USB -> UART0)
- SWD (2x5) for debugging and recovery
- BOOT and RESET buttons for ISP entry
- TTL serial display connector (JST-4)
- Limits / probe / E-STOP inputs with anti-noise filtering
- Spindle control (PWM/DIR/ENABLE and TACH input)
- Coolant outputs (FLOOD, MIST) via MOSFET low-side switches
- Optional USB Type-C connector for power and/or data (configured for USB2.0)
- Secondary MCU (STM32F0) to generate STEP/DIR for axes A/B

This is a reference draft: symbols, footprints and exact net names should be adapted into your CAD tool (KiCad recommended). The file is intended to be human-editable and used as a starting point for actual schematic capture.

---

## Structure of the draft

Files in this repo:
- `INTEGRATED_SCHEMATIC.md` (this file) — textual schematic with nets, components and pin mappings.
- `BOM.csv` — starter BOM listing key parts and suggested footrpints.

---

## Design notes (summary)

1. Use LPC1768 as main controller. Map step/dir outputs for X/Y/Z to LPC1768 hardware timers as supported by grblHAL/LPC176x driver. Reserve UART0 for CH340 USB-UART (firmware update). Reserve UART1/2 for display / plugins as needed.
2. For 5-axis support use a secondary MCU (MCU2) that receives high-level axis commands from LPC1768 (via UART) and generates precise STEP/DIR/EN signals for axes A and B using internal timers. MCU2 can be STM32F0 series or similar Cortex-M0.
3. microSD uses SPI lines and a CS pin; card detect routed to LPC1768 for auto-mount.
4. CH340 powered from 3.3V rail (preferred) so no level shifting required to MCU UART. If using 5V CH340 variant, include level shifters.
5. USB Type-C connector can be wired as a USB2.0 port for data and VBUS. Use CC resistors (Rd) to indicate device sink and follow USB-C port design rules if expecting to be powered by host.
6. Always keep SWD 10-pin header for development and recovery.
7. Use TVS on USB, SD and external IO for ESD protection. Add series resistors on USB D+/D- (22R), SD lines (22R), and stepper signal series resistors (100R) for ringing suppression.

---

## NETLIST and Components (reference)

### Power rails
- VBUS_USB: USB VBUS 5V (from USB-A or Type-C) after ferrite/PTC
- VCC_3V3: 3.3V LDO output (LDO_IN from VBUS_USB or main supply)
- VCC_5V: optional 5V rail (if using external 5V devices)
- GND

### Connectors
- J_USB_MICRO (micro-B) or J_USB_C (USB Type-C, 5 pins for USB2.0 and CC pins exposed)
  - Pins: VBUS_USB, USB_DP, USB_DN, GND, SHIELD, (CC1, CC2 for Type-C)
- J_SWD_10 (2x5 standard debug header)
  - Pins: VTREF (3.3V), SWDIO, GND, SWCLK, nRESET, TRACES per standard
- J_SD (microSD socket)
  - Pins: VCC, GND, MOSI (SD_MOSI), MISO (SD_MISO), SCK (SD_SCK), CS (SD_CS), CD (Card Detect)
- J_DISP (JST-4)
  - Pins: VCC, GND, DISP_RX (MCU TX), DISP_TX (MCU RX)
- J_AXIS_X/Y/Z/A/B (each 4-pin screw): STEP, DIR, EN, GND
- J_SPINDLE (6-pin): PWM, DIR, ENABLE, TACH, GND, V_AUX
- J_COOLANT (2x screw): FLOOD_OUT, MIST_OUT, GND
- J_LIMITS (group of 3-pin headers per sensor): SIG, GND, +V
- J_ESTOP (2-pin): E-STOP NC loop

### Main MCU: LPC1768 (symbol U1)
- VCC_3V3 -> to all VDD pins
- GND -> to all VSS pins
- UART0 RX (P0.x) <- CH340 TXD
- UART0 TX (P0.x) -> CH340 RXD
- SPI: SPI_MOSI (P0.x), SPI_MISO (P0.x), SPI_SCK (P0.x) -> microSD
- SD_CS -> GPIO (choose free pin)
- SD_CD -> GPIO (card detect)
- Step/dir outputs
  - X_STEP -> P0.x (timing hardware output preferred)
  - X_DIR  -> P0.y
  - X_EN   -> P0.z
  - Y_STEP/Y_DIR/Y_EN similar
  - Z_STEP/Z_DIR/Z_EN similar
- SPI/Timer pins selection must follow LPC1768 datasheet and grblHAL LPC176x driver mapping
- SPINDLE PWM -> P[match timer], SPINDLE_DIR -> GPIO, SPINDLE_EN -> GPIO, SPINDLE_TACH -> timer capture input
- LIMITS / PROBE -> GPIO with RC filter and optional opto isolation

### Secondary MCU (MCU2): STM32F0 or similar (symbol U2)
- UART RX <- LPC1768 TX (protocol to accept A/B axis commands)
- UART TX -> LPC1768 RX (ack/status)
- A_STEP/A_DIR/A_EN -> stepper driver A headers
- B_STEP/B_DIR/B_EN -> stepper driver B headers
- Timer channels used for step pulse generation
- Optionally exposes debug header for firmware updates

### USB-UART Bridge: CH340 (symbol U3)
- VCC -> VCC_3V3 (preferred)
- GND -> GND
- D+/D- -> USB connector via 22Ω series resistors and TVS protection
- TXD -> CH340_TXD net to LPC_UART_RX
- RXD -> CH340_RXD net to LPC_UART_TX
- CH340 requires 12MHz crystal and caps per datasheet

### SD Card interface
- SD_MOSI, SD_MISO, SD_SCK -> SPI pins on LPC1768
- SD_CS -> dedicated GPIO
- CMD/D0 pull-ups 10k
- Series resistors 22Ω on data/clock lines
- ESD/TVS and decoupling caps near socket

### Spindle and Coolant
- Spindle control uses MOSFET or SSR driver and PWM input
- For VFD 0-10V control: PWM -> RC low-pass -> op-amp scaler to 0-10V (optional on adapter)
- TACH input -> timer capture input on LPC1768. Add small RC and clamp diode if needed
- Coolant outputs use N-MOSFET low side switches (Q1/Q2), gate resistor 100R and pulldown 100k

### Limits / Probe / E-STOP inputs
- Each input: series resistor 1k, pull-up 10k to 3.3V or 10k pull-down depending wiring
- RC filter: R=10k + C=100nF (for debouncing) or do software de-bounce
- E-STOP is a NC loop; hardware contactor/relay for immediate power cut plus MCU input for state reporting

### USB Type-C addition (optional)
- If adding Type-C connector and using it to supply power and/or data:
  - Wire CC1/CC2 via Rd resistors if board acts as sink (5.1k to GND to indicate sink)
  - Wire D+/D- to CH340 D+/D- (for USB2.0 compatibility)
  - Route VBUS via ferrite bead + PTC fuse to VBUS_PRE then to LDO_IN (if powering 3.3V from USB)
  - Protect CC pins and VBUS per USB-C design guides (use USB-C port controller if negotiating higher currents)

---

## BOM (starter)
A short starter BOM is in `BOM.csv`. It lists suggested part descriptions and footprints. Use it as starting point; values like MOSFET choice, LDO, TVS device must be selected based on current and mechanical constraints.

---

## Next steps I can do for you (pick any):
- Generate a KiCad schematic (.kicad_sch) and push to this repository (I can create the file skeleton and the textual symbols — you will need to assign footprints in KiCad and run ERC/DRC)
- Create a printable PDF page of the above schematic (I can create a PDF in the repo via a generated file that you can download)
- Produce a detailed pin mapping table for LPC1768 showing specific P0.x/P1.x pins for step/dir/timer usage aligned with grblHAL LPC176x driver
- Produce MCU2 firmware interface draft (UART protocol for A/B axis commands and example command set)

If you want I will now generate and push a KiCad-compatible schematic file and a PDF export to the repository so you can download them to your desktop. Confirm and I will proceed.