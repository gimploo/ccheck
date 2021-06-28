#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>
#include <ctype.h>
#include "color.h"

#define panic(...) {\
    fprintf(stderr, DBG"%s:" __VA_ARGS__ , __func__);\
    exit(1);\
}

#define IMPL (\
        fprintf(stderr,"TODO : %s left to implement\n",__func__);\
        exit(0);\
)


#define ESC 0x1B
#define KB 1024
#define MAXSIZE (4 * KB)

#define u_int64_t u64
#define u_int32_t u32

#endif //COMMON_H
