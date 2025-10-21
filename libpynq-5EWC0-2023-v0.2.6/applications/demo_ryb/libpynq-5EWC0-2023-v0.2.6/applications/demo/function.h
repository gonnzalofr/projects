#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>

int receive(uint8_t *msg, int *counter);
void send(float output);
int displaying(uint8_t input, uint8_t input2, uint8_t output, display_t display);

#endif