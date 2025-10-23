#include <libpynq.h>
#include <stdio.h>
#include <libpynq.h>
#include <uart.h>
#include <math.h>
#include "functions.h"
#include <string.h>

#define _USE_MATH_DEFINES
#define WINDOW_HEIGHT 240
#define WINDOW_WIDTH 240

int main(void) {
  pynq_init();
  
  display_t display;
  display_init(&display);
  adc_init();

  FontxFile fx16G[2];
  uint8_t buffer_fx16G[FontxGlyphBufSize];
  uint8_t fontWidth_fx16G, fontHeight_fx16G;
  InitFontx(fx16G, "../../fonts/ILGH16XB.FNT", "");
  GetFontx(fx16G, 0, buffer_fx16G, &fontWidth_fx16G, &fontHeight_fx16G);



  display_set_flip(&display, false, false);
  displayFillScreen(&display, RGB_BLACK);
  displayDrawLine(&display, 5, 0, 5, 239, RGB_WHITE);
  displayDrawLine(&display, 5, 120, 235, 120, RGB_WHITE);

  gpio_set_direction(IO_A0, GPIO_DIR_INPUT);

  gpio_set_level(IO_A0, GPIO_LEVEL_LOW);

  int y;
  int x = 0;
  
  while(1){
    y = round(120 - (100 * (adc_read_channel(ADC0) / 4095)));
    printf("%i\n", y);
    sleep_msec(20);
    x++;
  }


  pynq_destroy();
  return EXIT_SUCCESS;
}


