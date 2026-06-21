#include "bms_serial.h"
#include "bms_config.h"

namespace {

bool hasNegativeCell(const VoltageData& data) {
  return (data.cell1 < 0.0f) || (data.cell2 < 0.0f) || (data.cell3 < 0.0f);
}

bool hasOverPack(const VoltageData& data) {
  return data.pack > 13.0f;
}

}  // namespace

// =============================================================================
// Print one formatted telemetry frame for ADC counts, reconstructed voltages,
// and pack status classification.
// =============================================================================
void printVoltageReport(uint16_t adc1, uint16_t adc2, uint16_t adc3, const VoltageData& data) {
  Serial.println(F("---"));

  Serial.print(F("ADC1: "));
  Serial.print(adc1);
  Serial.print(F(" | ADC2: "));
  Serial.print(adc2);
  Serial.print(F(" | ADC3: "));
  Serial.println(adc3);

  Serial.print(F("Cell1: "));
  Serial.print(data.cell1, 2);
  Serial.println(F(" V"));

  Serial.print(F("Cell2: "));
  Serial.print(data.cell2, 2);
  Serial.println(F(" V"));

  Serial.print(F("Cell3: "));
  Serial.print(data.cell3, 2);
  Serial.println(F(" V"));

  Serial.print(F("Pack : "));
  Serial.print(data.pack, 2);
  Serial.println(F(" V"));

  if (data.pack < LOW_VOLTAGE_THRESHOLD) {
    Serial.println(F("STATUS: LOW VOLTAGE"));
  } else {
    Serial.println(F("STATUS: GOOD"));
  }

  if (hasNegativeCell(data)) {
    Serial.println(F("WARNING: NEGATIVE CELL VOLTAGE RECONSTRUCTED"));
  }

  if (hasOverPack(data)) {
    Serial.println(F("WARNING: PACK VOLTAGE ABOVE 13.00 V"));
  }

  Serial.println();
}
