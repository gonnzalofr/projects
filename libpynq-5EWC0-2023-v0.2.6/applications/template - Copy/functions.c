#include <libpynq.h>
#include <uart.h>
#include <stdio.h>
#include <stdint.h>
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

void scroll_store(display_t display, int position[])
{
  for(int i = 5; i < 236; i++)
  {
  
      if(position[i] != 120){
      displayDrawPixel(&display, i, position[i], RGB_BLACK);
      }
      position[i] = position[i + 1];
      displayDrawPixel(&display, i, position[i], RGB_WHITE);
    }

  /*for(int i = 5; i < 236; i++)
  {
    for(int j = 19; j < 221; j++)
    {
      if(j != 120){
        if(color[i + 1][j].red == 255)
        {
          color[i][j] = color[i + 1][j];
          color[i + 1][j].red = 0;
          color[i + 1][j].green = 0;
          color[i + 1][j].blue = 0;
        
          
          if(color[i][j].red == 255 && color[i][j].green == 255 && color[i][j].blue == 255)
          {
            displayDrawPixel(&display, i, j, RGB_WHITE);
            displayDrawPixel(&display, i + 1, j, RGB_BLACK);
          }
        }
        }
    }*/
      
      
  
  return;
}




