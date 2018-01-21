#ifndef HSW_BIND_H
#define HSW_BIND_H

typedef struct bind_s bind_s;

#include "bindmode.h"
#include "command.h"

struct bind_s
{
    bind_s* next;
    bmode_s* mode;
    char device[MAX_CMD_ARGVLEN];
    char topic[MAX_CMD_ARGVLEN];
};

extern bind_s* BINDS[NBMODES];

#endif

