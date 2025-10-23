#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>


typedef struct{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} screens;

void send(float output);
int displaying(uint8_t input, uint8_t input2, uint8_t output, display_t display);
void scroll(display_t display, int position[]);
void scroll1(display_t display, int position[]);
void sine(display_t display, float ratio, int degree, int position[]);
void cosine(display_t display, float ratio, int degree1, int position1[]);
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#endif