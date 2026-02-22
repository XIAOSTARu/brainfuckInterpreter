#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typedef.h"
#include "error.h"
#include "setting.h"

unsigned char* getCode(size_t* cp);

void interpret();