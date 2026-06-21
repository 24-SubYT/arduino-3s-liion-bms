#pragma once

#include <Arduino.h>

// =============================================================================
// Voltage Reconstruction Module
// Converts raw ADC counts into tap voltages and per-cell voltages for a 3S pack.
// =============================================================================

struct VoltageData {
  float tap1;
  float tap2;
  float tap3;
  float cell1;
  float cell2;
  float cell3;
  float pack;
};

float adcCountsToVoltage(uint16_t adcCounts, float ratio);
VoltageData reconstructVoltages(uint16_t adc1, uint16_t adc2, uint16_t adc3);
