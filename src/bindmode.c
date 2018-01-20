#include "bind.h"

char* BMODE_STR[NBMODES] =
{   "OWI",
    "OWO" ,
    "FLI",
    "FLO" };

bmode_devicechecker_t BMODE_VALIDDEVICE[NBMODES] =
{   bmode_owi_validdevice,
    bmode_owo_validdevice,
    bmode_fli_validdevice,
    bmode_flo_validdevice };

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


