#ifndef HSW_BIND_H
#define HSW_BIND_H

#include "bindmode.h"
#include "command.h"

typedef struct bind_s
{
    struct bind_s* next;
    int mode;
    char device[MAX_CMD_ARGVLEN];
    char topic[MAX_CMD_ARGVLEN];
} bind_s;

extern bind_s* BINDS[NBMODES];

char* bind_print(char* outstr, bind_s* bind);

#endif

