## Project Status

### Phase 1: Voltage Monitoring (Completed)

#### Objective
Measure and reconstruct individual cell voltages in a 3S Li-ion battery pack using the Arduino Uno ADC.

#### Implemented

- Voltage measurement of Cell 1 (A0)
- Voltage measurement of Cell 1 + Cell 2 tap (A1)
- Voltage measurement of full pack voltage (A2)
- Voltage divider networks using:
  - 30kΩ / 10kΩ
  - 56kΩ / 10kΩ
- Cell voltage reconstruction:
  - Cell1 = Tap1
  - Cell2 = Tap2 − Tap1
  - Cell3 = Tap3 − Tap2
- ADC oversampling for improved stability
- Real-time Serial Monitor output
- Validation using a multimeter
- Pack voltage measurement up to 12.6V

#### Example Output

```text
Cell1: 3.82V
Cell2: 3.80V
Cell3: 3.84V
Pack : 11.46V
Status: GOOD
```

#### Engineering Concepts Demonstrated

- Analog signal conditioning
- Voltage divider design
- ADC interfacing
- Differential measurement
- Embedded C/C++ firmware
- Measurement validation and calibration

#### Current Hardware

- Arduino Uno R3
- Breadboard
- 3 × 18650 Li-ion cells
- 30kΩ resistor
- 56kΩ resistor
- 10kΩ resistors
- Jumper wires
- Multimeter

#### Next Phase

Phase 2 will add:

- 16×2 I2C LCD
- NTC thermistor temperature sensing
- Fault detection logic
- Alarm indicators
- UART CSV logging
