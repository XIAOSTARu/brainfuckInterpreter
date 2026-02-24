#pragma once

#include <stdio.h>
#include "typedef.h"
#include "bfio.h"

#define VERSION "1.0.2"

#ifndef NO_COLOR

#define CODE_PTR_START "\033[97;42m"
#define CODE_PTR_END "\b\033[0m "

#define MEM_PTR_START "|\033[47;31m"
#define MEM_PTR_END   "\033[0m|"

#else

#define CODE_PTR_START "{"
#define CODE_PTR_END "\b} "

#define MEM_PTR_START " ("
#define MEM_PTR_END   ") "

#endif

#define MAX_MEM 1048575
#define MIN_MEM 255

#define MAX_STACK 16384
#define MIN_STACK 1

#define Output(x) bfOutput(x)
#define   Input() bfInput()

extern bool exists_srcfile;
extern size_t memorySize;
extern size_t stackSize;
extern size_t codeSize;

extern bool auto_calc_codesize;
extern bool debug_printmem;
extern bool debug;
extern bool debug_print;
extern bool debug_print_outputbuffer;

extern char* srcfile;