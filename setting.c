#include "setting.h"

bool exists_srcfile = false;
size_t memorySize = 30000;
size_t stackSize  = 256;
size_t codeSize   = 0;

bool debug_printmem = false;
bool debug = false;
bool debug_print = false;

char* srcfile = nullptr;