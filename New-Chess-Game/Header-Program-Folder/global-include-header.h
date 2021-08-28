
#ifndef GLOBAL_INCLUDE_HEADER_H
#define GLOBAL_INCLUDE_HEADER_H

#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <string.h>

#include <math.h>

#include <time.h>

#include <unistd.h>

#define CLEAR_LINE printf("\033[2K");
#define MOVE_UP(lines) printf("\033[%dA", lines);

#include "struct-definitions-header.h"

#include "common-functions-program.h"

#endif