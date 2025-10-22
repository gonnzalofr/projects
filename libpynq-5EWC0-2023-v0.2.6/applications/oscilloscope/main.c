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
  display_set_flip(&display, false, false);
  displayFillScreen(&display, RGB_BLACK);
  FontxFile fx16G[2];
  uint8_t buffer_fx16G[FontxGlyphBufSize];
  uint8_t fontWidth_fx16G, fontHeight_fx16G;

  InitFontx(fx16G, "../../fonts/ILGH16XB.FNT", "");
  GetFontx(fx16G, 0, buffer_fx16G, &fontWidth_fx16G, &fontHeight_fx16G);

  displayDrawLine(&display, 5, 0, 5, 239, RGB_WHITE);
  displayDrawLine(&display, 5, 120, 235, 120, RGB_WHITE);
  int degree = 0;
  double radians = 0;
  int x = 6;
  int y;
  char decision;
  char str[30];
  int position[240];
  screens color[240][240];
  memset(color, 0, sizeof(color));
  printf("Choose mode s/c/t/r: ");
  scanf(" %c", &decision);
  
  switch (decision){
    case 's':
    strcpy(str, "Sine Wave");
    displayDrawString(&display, fx16G, 20, 20, (uint8_t*)str, RGB_WHITE);
    while(1) //for(degree = 0; degree <= 236; degree++)
        {
        if(x < 234){
          radians = (degree * (M_PI / 180.0));
          y = round(120 - (100 * sin(radians)));
          position[x] = y;
          displayDrawPixel(&display, x, y, RGB_WHITE);
          x++;
          degree++;
        }
        else{
          radians = (degree * (M_PI / 180.0));
          y = round(120 - (100 * sin(radians)));
          displayDrawPixel(&display, 234, y, RGB_WHITE);
          position[234] = y;
          scroll_store(display, position);
          degree++;
        }
        
        }
    case 'c':
    strcpy(str, "Cosine Wave");
    displayDrawString(&display, fx16G, 20, 20, (uint8_t*)str, RGB_WHITE);
    while(1) //for(degree = 0; degree <= 236; degree++)
        {
        if(x < 234){
          radians = (degree * (M_PI / 180.0));
          y = round(120 - (100 * cos(radians)));
          position[x] = y;
          displayDrawPixel(&display, x, y, RGB_WHITE);
          x++;
          degree++;
        }
        else{
          radians = (degree * (M_PI / 180.0));
          y = round(120 - (100 * cos(radians)));
          position[234] = y;
          scroll_store(display, position);
          degree++;
        }
        
        }
        
      return 0;
    case 't':
      return 0;
    case 'r':
      return 0;
  }

  pynq_destroy();
  return EXIT_SUCCESS;
}


