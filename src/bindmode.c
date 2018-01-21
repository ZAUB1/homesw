#include <stdio.h>

#include "bind.h"
#include "util.h"

bmode_s BMODE[NBMODES] =
{   { "OWI", bmode_owi_validdevice, bmode_printbind_sensor },
    { "OWO", bmode_owo_validdevice, bmode_printbind_actuator },
    { "FLI", bmode_fli_validdevice, bmode_printbind_sensor },
    { "FLO", bmode_flo_validdevice, bmode_printbind_actuator } };

int bmode_owi_validdevice(char* device)
{
    return 1;
}

int bmode_owo_validdevice(char* device)
{
    return 1;
}

int bmode_fli_validdevice(char* device)
{
    return 1;
}

int bmode_flo_validdevice(char* device)
{
    return 1;
}

char* bmode_printbind_sensor(char* outstr, bind_s* bind)
{
    return outstr + max(0, sprintf(outstr,
            "%s  %s  ->  %s", bind->mode->str, bind->device, bind->topic));
}

char* bmode_printbind_actuator(char* outstr, bind_s* bind)
{
    return outstr + max(0, sprintf(outstr,
            "%s  %s  ->  %s", bind->mode->str, bind->topic, bind->device));
}

