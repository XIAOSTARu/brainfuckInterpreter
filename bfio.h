#pragma once

#include <stdio.h>
#include <stddef.h>

#define OUTPUT_BUFFER_MAX 1024

#define PRINT_FUNC(x) printf("%s", x)
#define INPUT_FUNC() getchar()

extern char output_buffer[OUTPUT_BUFFER_MAX];

void bfOutput(char c);
char bfInput();
void bfPrint();
void bfClean();
