#include <libpynq.h>
#include <uart.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "functions.h"

#define DISPLAY_HEIGHT 240
#define DISPLAY_WIDTH 240


void send(float output)
{
uint8_t *data = (uint8_t*)&output;

for(int i = 0; i < (int)sizeof(float); i++)
    {
        uart_send(UART0, data[i]);
    }  
}

int displaying(uint8_t input, uint8_t input2, uint8_t output, display_t display)
{
  FontxFile fx16G[2];
  uint8_t buffer_fx16G[FontxGlyphBufSize];
  uint8_t fontWidth_fx16G, fontHeight_fx16G;

  InitFontx(fx16G, "../../fonts/ILGH16XB.FNT", "");
  GetFontx(fx16G, 0, buffer_fx16G, &fontWidth_fx16G, &fontHeight_fx16G);

  displayFillScreen(&display, RGB_WHITE);

    char inp[256];
    sprintf(inp, "Receiving 1: %u", input);
    displayDrawString(&display, fx16G, 10, 30, (uint8_t*)inp, RGB_BLACK);

    char inp2[256];
    sprintf(inp2, "Receiving 2: %u", input2);
    displayDrawString(&display, fx16G, 10, 60, (uint8_t*)inp2, RGB_BLACK);

    char out[256];
    sprintf(out, "Sending: %u", output);
    displayDrawString(&display, fx16G, 10, 90, (uint8_t*)out, RGB_BLACK);

  return 0;
} 

void scroll(display_t display, int position[])
{
  for(int i = 6; i < 236; i++)
  {
  
      if(position[i] != 120){
        displayDrawPixel(&display, i, position[i], RGB_BLACK);
      }
      if(position[i + 1] != 120){
      displayDrawPixel(&display, i, position[i + 1], RGB_BLUE);
      }
      position[i] = position[i + 1];

    }
  return;
}

void scroll1(display_t display, int position1[])
{
  for(int i = 6; i < 236; i++)
  { 
      if(position1[i] != 120)
      {
        displayDrawPixel(&display, i, position1[i], RGB_BLACK);
      }
  
      if(position1[i + 1] != 120){
      displayDrawPixel(&display, i, position1[i + 1], RGB_RED);
      }
      position1[i] = position1[i + 1];
    }
  return;
}

void sine(display_t display, float ratio, int degree, int position[])
{
  int y;
  float radians;
  radians = ratio * (degree * (M_PI / 180.0));
  y = round(120 - ((100 - (10 * ratio)) * sin(radians)));
  position[234] = y;
  scroll(display, position);
}

void cosine(display_t display, float ratio, int degree1, int position1[])
{
  int y;
  float radians1;
  radians1 = ratio * (degree1 * (M_PI / 180.0));
  y = round(120 - ((100 - (10 * ratio)) * cos(radians1)));
  position1[234] = y;
  scroll1(display, position1);
}



