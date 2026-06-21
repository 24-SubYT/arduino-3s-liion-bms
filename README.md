# Arduino 3S Li-ion BMS (ATmega328P)

Professional embedded systems repository for a **3-series (3S) Li-ion Battery Management System** implemented on **Arduino Uno (ATmega328P)**.

## Project overview

This project monitors a 3-cell Li-ion pack, computes individual cell voltages from stacked measurements, estimates temperature using an NTC sensor, and triggers alarms with hysteresis. It is structured for reproducible development and portfolio presentation in embedded systems internships.

## Repository structure

```text
arduino-3s-liion-bms/
├── docs/        # design notes, calculations, and architecture docs
├── firmware/    # Arduino firmware source and module layout
├── hardware/    # schematics, wiring, and hardware design notes
├── results/     # captured logs, validation tables, and test outputs
└── images/      # diagrams, photos, and UI screenshots
```

## Hardware architecture

Target controller: **Arduino Uno (ATmega328P, 10-bit ADC, 5 V reference)**.

Measured/controlled elements:
- 3-cell Li-ion stack (B1, B2, B3 nodes relative to pack negative)
- Resistive dividers to scale ADC input
- NTC thermistor divider for temperature channel
- LCD interface for local status
- Alarm output (buzzer/LED relay logic)
- UART serial logging for host-side capture

## Voltage divider design

Because stacked cell nodes exceed direct ADC limits, each tap is measured through a divider:

\[
V_\text{adc} = V_\text{node} \times \frac{R_\text{bottom}}{R_\text{top}+R_\text{bottom}}
\]

Node voltage is reconstructed in firmware by applying the inverse gain:

\[
V_\text{node} = V_\text{adc} \times \frac{R_\text{top}+R_\text{bottom}}{R_\text{bottom}}
\]

Design goals:
- Keep \(V_\text{adc} \leq 5\text{ V}\) across full pack range
- Use stable resistor values with tolerance awareness
- Balance measurement accuracy vs. divider current draw

## Cell voltage reconstruction

Measured nodes are cumulative in a stacked pack:
- \(V_{B1}\): Cell 1 top
- \(V_{B2}\): Cell 1 + Cell 2 top
- \(V_{B3}\): Cell 1 + Cell 2 + Cell 3 top

Individual cell estimates:
- \(V_{C1} = V_{B1}\)
- \(V_{C2} = V_{B2} - V_{B1}\)
- \(V_{C3} = V_{B3} - V_{B2}\)

This approach enables per-cell undervoltage/overvoltage logic using only single-ended ADC channels.

## NTC thermistor temperature sensing

Temperature is measured with an NTC divider:
1. Read ADC count
2. Convert ADC to divider voltage
3. Solve thermistor resistance
4. Convert resistance to temperature using Beta model or Steinhart-Hart coefficients

This supports pack thermal protection and alarm derating behavior.

## Alarm system with hysteresis

Alarms should avoid chatter around thresholds. Each fault uses:
- **Trip threshold** (fault enters active state)
- **Clear threshold** (fault exits active state with margin)

Typical monitored fault classes:
- Cell undervoltage / overvoltage
- Pack overtemperature
- Sensor plausibility faults

Hysteresis improves stability and user trust in field operation.

## LCD display

Local HMI displays key diagnostics:
- Cell voltages (C1/C2/C3)
- Pack voltage
- Temperature
- Active alarm/fault state

Display refresh is periodic and decoupled from ADC sampling cadence.

## UART CSV logging

Runtime telemetry is exported through UART in CSV format for plotting and validation:

```csv
timestamp_ms,vb1,vb2,vb3,vc1,vc2,vc3,temp_c,alarm
```

This supports offline analysis in spreadsheets, Python, or MATLAB.

## Future STM32 migration roadmap

Planned migration path from ATmega328P to STM32:
1. Preserve algorithm modules (voltage reconstruction, thermal conversion, alarm logic)
2. Replace HAL drivers (ADC, timers, UART, LCD) with STM32 HAL/LL equivalents
3. Move to higher-resolution ADC and DMA-backed sampling
4. Introduce RTOS scheduling for deterministic task partitioning
5. Add hardware protections and production-grade diagnostics

This roadmap keeps architecture portable while scaling toward industrial embedded practice.
