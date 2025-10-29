#include <libpynq.h>
#include <uart.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "functions.h"

#define DISPLAY_HEIGHT 240
#define DISPLAY_WIDTH 240
float sin_lut[LUT_SIZE];
float cos_lut[LUT_SIZE];


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

void scroll(display_t display, int position[], int y, int y1)
{
  int temp;
  int start_y;
  int end_y;
  /*for(int i = 6; i < 236; i++)
  {
    if(position[i] != 120){
      displayDrawPixel(&display, i, position[i], RGB_BLACK);
    }
  }*/
  for(int i = 6; i < 236; i++)
  {
    start_y = position[i];
    end_y = position[i + 1];

    if(start_y > end_y)
    {
      temp = start_y;
      start_y = end_y;
      end_y = temp;
    }
  
    for(int j = start_y; j <= end_y + 1; j++)
    {
      if(j != 120){
      displayDrawPixel(&display, i, j, RGB_BLACK);
      }
    }
 }

  memmove(&position[6], &position[8], 230 * sizeof(int));
  position[234] = y;
  position[235] = y1;

  /*for(int i = 6; i < 236; i++)
  {
    if(position[i] != 120){
      displayDrawPixel(&display, i, position[i], RGB_BLUE);  
    }
  }
  return;*/

  for(int i = 6; i < 235; i++)
  {
    start_y = position[i];
    end_y = position[i + 1];
    if(start_y > end_y)
    {
      temp = start_y;
      start_y = end_y; 
      end_y = temp;
    }
    for(int j = start_y; j < end_y; j++)
    {
      if(j != 120)
      {
        displayDrawPixel(&display, i, j, RGB_BLUE);
      }
    }
  }
}

void scroll1(display_t display, int position1[], int y, int y1)
{
  int temp;
  int start_y;
  int end_y;
  /*for(int i = 6; i < 236; i++)
  {
    if(position1[i] != 120){
      displayDrawPixel(&display, i, position1[i], RGB_BLACK);
    }
  }*/
//removes old pixels
  for(int i = 6; i < 236; i++)
  {
    start_y = position1[i];
    end_y = position1[i + 1];

    if(start_y > end_y)
    {
      temp = start_y;
      start_y = end_y;
      end_y = temp;
    }
  
    for(int j = start_y; j <= end_y + 1; j++)
    {
      if(j != 120){
      displayDrawPixel(&display, i, j, RGB_BLACK);
      }
    }
 }
  memmove(&position1[6], &position1[8], 230 * sizeof(int));
  position1[234] = y;
  position1[235] = y1;

  /*for(int i = 6; i < 236; i++)
  {
    if(position1[i] != 120){
    displayDrawPixel(&display, i, position1[i], RGB_RED);  
    }
  }*/

  for(int i = 6; i < 235; i++)
  {
    start_y = position1[i];
    end_y = position1[i + 1];
    if(start_y > end_y)
    {
      temp = start_y;
      start_y = end_y; 
      end_y = temp;
    }
    for(int j = start_y; j < end_y; j++)
    {
      if(j != 120)
      {
        displayDrawPixel(&display, i, j, RGB_RED);
      }
    }
  }
  return;
}

void sine(display_t display, float ratio, int degree, int position[])
{
  int y;
  int y1;
  y = round(120 - ((100 - (5 * ratio)) * sin_lut[degree]));
  y1 = round(120 - ((100 - (5 * ratio)) * sin_lut[degree + 1]));
  scroll(display, position, y, y1);
}

void cosine(display_t display, float ratio, int degree1, int position1[])
{
  int y;
  int y1;
  y = round(120 - ((100 - (5 * ratio)) * cos_lut[degree1]));
  y1 = round(120 - ((100 - (5 * ratio)) * cos_lut[degree1 + 1]));
  scroll1(display, position1, y, y1);
}

void init_math_lut(int ratio){
  float rad;
  for(int i = 0; i < LUT_SIZE; i++){
    rad = ratio * (i * M_PI / 180.0f);
    sin_lut[i] = sinf(rad);
    cos_lut[i] = cosf(rad);
  }
}


  