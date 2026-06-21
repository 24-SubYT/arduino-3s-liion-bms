#include "bms_voltage.h"
#include "bms_config.h"

// =============================================================================
// Convert ADC counts to reconstructed voltage at source node before divider.
// =============================================================================
float adcCountsToVoltage(uint16_t adcCounts, float ratio) {
  const float measured = (static_cast<float>(adcCounts) * ADC_REFERENCE_VOLTAGE) /
                         static_cast<float>(ADC_MAX_COUNT);
  return measured * ratio;
}

// =============================================================================
// Reconstruct 3S pack tap voltages and cell voltages from three ADC channels.
// Cell1 = Tap1
// Cell2 = Tap2 - Tap1
// Cell3 = Tap3 - Tap2
// Pack  = Tap3
// =============================================================================
VoltageData reconstructVoltages(uint16_t adc1, uint16_t adc2, uint16_t adc3) {
  VoltageData v{};

  v.tap1 = adcCountsToVoltage(adc1, TAP1_DIVIDER_RATIO);
  v.tap2 = adcCountsToVoltage(adc2, TAP2_DIVIDER_RATIO);
  v.tap3 = adcCountsToVoltage(adc3, TAP3_DIVIDER_RATIO);

  v.cell1 = v.tap1;
  v.cell2 = v.tap2 - v.tap1;
  v.cell3 = v.tap3 - v.tap2;
  v.pack  = v.tap3;

  return v;
}
