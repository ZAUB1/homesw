#include <stdio.h>

#include "bind.h"
#include "util.h"

bind_s* BINDS[NBMODES];

char* bind_print(char* outstr, bind_s* bind)
{
    return outstr + max(0, sprintf(outstr,
                "%s  %s  ->  %s", BMODE_STR[bind->mode], bind->device, bind->topic));
}

