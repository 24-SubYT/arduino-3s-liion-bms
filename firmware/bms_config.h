#pragma once

// =============================================================================
// BMS Configuration Constants
// Centralized configuration for ADC conversion, voltage scaling and reporting.
// =============================================================================

#include <Arduino.h>

// ADC conversion settings (Arduino Uno: 10-bit ADC)
constexpr float ADC_REFERENCE_VOLTAGE = 5.0f;   // [V]
constexpr uint16_t ADC_MAX_COUNT = 1023;        // 10-bit max
constexpr uint8_t ADC_OVERSAMPLE_COUNT = 16;    // 16x oversampling

// Voltage divider reconstruction ratios for each pack tap
// ratio = (Rtop + Rbottom) / Rbottom
constexpr float TAP1_DIVIDER_RATIO = 1.0f;
constexpr float TAP2_DIVIDER_RATIO = 2.0f;
constexpr float TAP3_DIVIDER_RATIO = 3.0f;

// Pack health threshold
constexpr float LOW_VOLTAGE_THRESHOLD = 9.0f;   // [V] 3S pack low voltage

// Reporting interval
constexpr unsigned long PRINT_INTERVAL_MS = 1000UL;

// ADC pin mapping for tap measurements
constexpr uint8_t ADC_PIN_TAP1 = A0;
constexpr uint8_t ADC_PIN_TAP2 = A1;
constexpr uint8_t ADC_PIN_TAP3 = A2;
