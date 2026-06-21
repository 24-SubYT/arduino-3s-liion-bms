#pragma once

#include <Arduino.h>

// =============================================================================
// ADC Acquisition Module
// Provides oversampled ADC reading independent from BMS application logic.
// =============================================================================

uint16_t adcReadOversampled(uint8_t pin);
