#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>
#include "color.h"

#ifdef DEBUG
#define IMPL (\
        fprintf(stderr,"TODO : %s left to implement\n",__func__);\
        exit(0);\
)
#endif //DEBUG

#define KB 1024
#define MAXSIZE (4 * KB)
#define ESC 0x1B

#endif //COMMON_H
