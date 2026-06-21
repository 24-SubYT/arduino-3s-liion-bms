#pragma once

#include <Arduino.h>
#include "bms_voltage.h"

// =============================================================================
// Serial Reporting Module
// Handles formatted telemetry output and simple safety status diagnostics.
// =============================================================================

void printVoltageReport(uint16_t adc1, uint16_t adc2, uint16_t adc3, const VoltageData& data);
