#ifndef HSW_BINDMODE_H
#define HSW_BINDMODE_H

#include "bind.h"

typedef struct bmode_s
{
    char* str;
    int (*valid_device)(char*);
    char* (*print_bind)(char*, bind_s*);
} bmode_s;

#define NBMODES 4
#define BMODE_OWI 0
#define BMODE_OWO 1
#define BMODE_FLI 2
#define BMODE_FLO 3

extern bmode_s BMODE[NBMODES];

int bmode_owi_validdevice(char* device);
int bmode_owo_validdevice(char* device);
int bmode_fli_validdevice(char* device);
int bmode_flo_validdevice(char* device);

char* bmode_printbind_sensor(char* outstr, bind_s* bind);
char* bmode_printbind_actuator(char* outstr, bind_s* bind);

#endif

