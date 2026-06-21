#include <Arduino.h>

#include "bms_config.h"
#include "bms_adc.h"
#include "bms_voltage.h"
#include "bms_serial.h"

// =============================================================================
// Phase 1 BMS Main Sketch
// Responsibilities:
// - Initialize serial telemetry
// - Run periodic sampling using millis() scheduler
// - Delegate ADC read, voltage reconstruction, and reporting to modules
// =============================================================================

static unsigned long g_lastPrintMs = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  const unsigned long now = millis();

  if (now - g_lastPrintMs >= PRINT_INTERVAL_MS) {
    g_lastPrintMs = now;

    const uint16_t adc1 = adcReadOversampled(ADC_PIN_TAP1);
    const uint16_t adc2 = adcReadOversampled(ADC_PIN_TAP2);
    const uint16_t adc3 = adcReadOversampled(ADC_PIN_TAP3);

    const VoltageData voltages = reconstructVoltages(adc1, adc2, adc3);
    printVoltageReport(adc1, adc2, adc3, voltages);
  }
}
