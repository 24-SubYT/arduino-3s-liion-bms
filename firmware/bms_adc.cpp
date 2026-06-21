#include "bms_adc.h"
#include "bms_config.h"

// =============================================================================
// Perform N-sample oversampling and return averaged ADC count.
// This reduces random conversion noise while keeping integer ADC semantics.
// =============================================================================
uint16_t adcReadOversampled(uint8_t pin) {
  uint32_t accumulator = 0;

  for (uint8_t i = 0; i < ADC_OVERSAMPLE_COUNT; ++i) {
    accumulator += static_cast<uint16_t>(analogRead(pin));
  }

  return static_cast<uint16_t>(accumulator / ADC_OVERSAMPLE_COUNT);
}
