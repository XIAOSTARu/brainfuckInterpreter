#pragma once

#include <stdio.h>
#include "typedef.h"

#define VERSION "1.0.0"

#define MAX_MEM 1048575
#define MIN_MEM 255

#define MAX_STACK 16384
#define MIN_STACK 1

#define Output(x) putchar(x)
#define   Input() getchar()

extern bool exists_srcfile;
extern size_t memorySize;
extern size_t stackSize;
extern size_t codeSize;

extern bool debug_printmem;
extern bool debug;
extern bool debug_print;

extern char* srcfile;