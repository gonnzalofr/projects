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



//rgb_conv(r,g,b); is whenever I want to use a random color
int main(void) 
{
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
  int degree1 = 0;
  int x = 6;
  int y;
  int y1;
  float ratio;
  int equations;
  char decision;
  char decision1;
  char str[30];
  int position[240];
  int position1[240];


  printf("Number of equations: ");
  scanf("%i", &equations);
  printf("Choose mode s/c: ");
  scanf(" %c", &decision);
  printf("Phase angle of first equation: ");
  scanf("%i", &degree);
  if(equations == 2){
    printf("Choose mode 2 s/c: ");
    scanf(" %c", &decision1);
    printf("Phase angle of second equation: ");
    scanf("%i", &degree1);
  }
  else if(equations > 2)
  {
    printf("Can't manage more than two equations.\n");
    return 0;
  }
  printf("Ratio: ");
  scanf("%f", &ratio);

  if(ratio < 1)
  {
    printf("The Ratio has to be equal or greater than 1");
    return 0;
  }
  else if(ratio > 10){
    printf("The Ratio has to be less or equal t0 10");
    return 0;
  }


  init_math_lut(ratio);

  if(equations == 1){
    switch (decision){
      case 's':
      strcpy(str, "Sine Wave");
      displayDrawString(&display, fx16G, 20, 20, (uint8_t*)str, RGB_WHITE);
        while(1) 
        {
          degree1 = degree1 % 360;
          if(x < 234){
            y = round(120 - ((101 - ratio) * sin_lut[degree1]));
            position[x] = y;
            displayDrawPixel(&display, x, y, RGB_WHITE);
            x++;
            degree1++;
          }
          else{
            if(degree1 > 360)
            {
              degree1 = degree1 % 360;
            }
            y = round(120 - ((101 - ratio) * sin_lut[degree1]));
            y1 = round(120 - ((101 - ratio) * sin_lut[(degree1 + 1) % 360]));
            scroll(display, position, y, y1);
            degree1++;
          }
        }
        break;
         
      case 'c':
      strcpy(str, "Cosine Wave");
      displayDrawString(&display, fx16G, 20, 20, (uint8_t*)str, RGB_WHITE);
        while(1) 
        {

          if(x < 234){
            y = round(120 - ((101 - ratio) * cos_lut[degree]));
            position[x] = y;
            displayDrawPixel(&display, x, y, RGB_WHITE);
            x++;
            degree++;
          }
          else{
            if(degree > 360)
            {
              degree = degree % 360;
            }
            y = round(120 - ((101 - ratio) * cos_lut[degree]));
            y1 = round(120 - ((101 - ratio) * cos_lut[(degree + 1) % 360]));
            scroll1(display, position, y, y1);
            degree++;
          }
        }

      return 0;
    }
  }
  else{
      strcpy(str, "Cosine & Sine waves");
      displayDrawString(&display, fx16G, 20, 20, (uint8_t*)str, RGB_WHITE);

        while(1) 
        {
          if(x < 236){
            y1 = round(120 - ((100 - (10 * ratio)) * cos_lut[degree1]));
            position1[x] = y1;
            displayDrawPixel(&display, x, y1, RGB_RED);
            y = round(120 - ((100 - (10 * ratio)) * sin_lut[degree]));
            position[x] = y;
            displayDrawPixel(&display, x, y, RGB_BLUE);
            x++;
            degree++;
            degree1++;
          }
          else{
            if(degree >= 360)
            {
              degree = degree % 360;
            }
            if(degree1 >= 360){
              degree1 = degree1 % 360;
            }
            sine(display, ratio, degree, position);
            cosine(display, ratio, degree1, position1);
            degree += 2;
            degree1 += 2;
          }
      }
  }        

  pynq_destroy();
  return EXIT_SUCCESS;
} 



