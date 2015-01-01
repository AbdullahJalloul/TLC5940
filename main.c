#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "tlc5940.h"

int main(void) {
  TLC5940_Init();

#if (TLC5940_INCLUDE_DC_FUNCS)
  TLC5940_SetAllDC(63);
  TLC5940_ClockInDC();
#endif

  TLC5940_SetAllGS(4095);
  TLC5940_ClockInGS();

  // Enable Global Interrupts
  sei();

  //TCNT0 = 0;

  for (;;) {
    for (channel_t i = 0; i < numChannels; ++i) {
      while(TLC5940_GetGSUpdateFlag()); // wait until we can modify gsData
      TLC5940_SetAllGS(0);
      TLC5940_SetGS(i, 4095);
      TLC5940_SetGSUpdateFlag();
      //_delay_ms(50);
    }
    for (channel_t i = numChannels - 1; i > 0; --i) {
      while(TLC5940_GetGSUpdateFlag()); // wait until we can modify gsData
      TLC5940_SetAllGS(0);
      TLC5940_SetGS(i, 4095);
      TLC5940_SetGSUpdateFlag();
      //_delay_ms(50);
    }
  }

  return 0;
}
