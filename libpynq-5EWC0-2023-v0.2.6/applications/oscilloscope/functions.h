#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>
#define LUT_SIZE 360




void init_math_lut(int ratio);
void send(float output);
int displaying(uint8_t input, uint8_t input2, uint8_t output, display_t display);
void scroll(display_t display, int position[], int y, int y1);
void scroll1(display_t display, int position[], int y, int y1);
void sine(display_t display, float ratio, int degree, int position[]);
void cosine(display_t display, float ratio, int degree1, int position1[]);

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

extern float sin_lut[LUT_SIZE];
extern float cos_lut[LUT_SIZE];

#endif