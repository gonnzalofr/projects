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

void scroll(display_t display, struct screen color[][240]);
void display_pixels(display_t display, struct screen color [][240]);
//ubk pidjedep
struct screen{
  uint8_t red;
  uint8_t green;
  uint8_t blue;

};

int main(void) {
  pynq_init();

  display_t display;
  display_init(&display);
  display_set_flip(&display, true, true);
  displayFillScreen(&display, RGB_BLACK);
  FontxFile fx16G[2];
  uint8_t buffer_fx16G[FontxGlyphBufSize];
  uint8_t fontWidth_fx16G, fontHeight_fx16G;

  InitFontx(fx16G, "../../fonts/ILGH16XB.FNT", "");
  GetFontx(fx16G, 0, buffer_fx16G, &fontWidth_fx16G, &fontHeight_fx16G);


  displayDrawLine(&display, 5, 0, 5, 240, RGB_WHITE);
  displayDrawLine(&display, 5, 120, 235, 120, RGB_WHITE);
  char status[20];
  int degree;
  double radians = 0;
  int x = 6;
  int y;
  char decision;
  struct screen color[240][240];
  printf("Choose mode s/c/t/r: ");
  scanf(" %c", &decision);


  switch (decision){
    case 's':
      decision = "Sine wave";
      displayDrawString(&display, fx16G, 5, 5, (uint8_t*)decision, RGB_WHITE);
      for(degree = 0; degree <= 236; degree++)
      {
        radians = (degree * (M_PI / 180.0));
        y = 120 + round(100 * sin(radians));
        displayDrawPixel(&display, x, y, RGB_WHITE);
        color[x][y].red = 255;
        color[x][y].green = 255;
        color[x][y].blue = 255;
        x++;
      }
      while (1){
        degree = degree % 360;
        radians = (degree * (M_PI / 180)) % 360;
        y = 120 + round(100 * sin(radians));
        displayDrawPixel(&display, x, y, RGB_WHITE);
        color[x][y].red = 255;
        color[x][y].green = 255;
        color[x][y].blue = 255;
        degree++;
        scroll(display, color);
        display_pixels(display, color);
        sleep_msec(20);
      }
    return 0;
    case 'c':
    decision = "Cosine";
    displayDrawString(&display, fx16G, 5, 5, (uint8_t*)decision, RGB_WHITE);
    for(degree = 0; degree <= 236; degree++)
        {
          radians = (degree * (M_PI / 180.0));
          y = 120 + round(100 * cos(radians));
          displayDrawPixel(&display, x, y, RGB_WHITE);
          color[x][y].red = 255;
          color[x][y].green = 255;
          color[x][y].blue = 255;
          x++;
        }
        while (1){
          degree = degree % 360;
          radians = (degree * (M_PI / 180)) % 360;
          y = 120 + round(100 * cos(radians));
          displayDrawPixel(&display, x, y, RGB_WHITE);
          color[x][y].red = 255;
          color[x][y].green = 255;
          color[x][y].blue = 255;
          degree++;
          scroll(display, color);
          display_pixels(display, color);
          sleep_msec(20);
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


void scroll(display_t display, struct screen color[][240])
{
  for(int i = 6; i < 236; i++)
  {
    for(int j = 20; j < 221; j++)
    {
      color[i][j].red = color[i + 1][j].red;
      color[i][j].green = color[i + 1][j].green;
      color[i][j].blue = color[i + 1][j].blue;
    }
  }
  return;
}

void display_pixels(display_t display, struct screen color[][240])
{
  for(int i = 6; i < 236; i++)
  {
    for(int j = 20; j < 221; j++)
    {
      if(color[i][j].red == 255 && color[i][j].green == 255 && color[i][j].blue == 255)
      {
        displayDrawPixel(&display, i, j, RGB_WHITE);
      }
    }
  }
}
