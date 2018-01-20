#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bind.h"
#include "chainlist.h"
#include "util.h"

void hsw_cmd_bind(int argc, char** argv, char* outstr_)
{
    char* outstr = outstr_;

    int mode = -1;
    for(int imode = 0; imode < NBMODES; imode++)
    {
        if(strcmp(argv[0], BMODE_STR[imode])== 0)
        {
            mode = imode;
        }
    }

    if(mode == -1)
    {
        outstr += max(0, sprintf(outstr, "Invalid mode %s, available modes are:", argv[0]));

        for(int imode = 0; imode < NBMODES; imode++)
        {
            outstr += max(0, sprintf(outstr, " %s", BMODE_STR[imode]));
        }
        return;
    }

    if(!BMODE_VALIDDEVICE[mode](argv[1]))
    {
        outstr += max(0, sprintf(outstr, "Invalid device %s", argv[1]));
        return;
    }

    bind_s* newbind = chainlist_add((void**) &BINDS[mode], sizeof(bind_s));
    newbind->mode = mode;
    strcpy(newbind->device, argv[1]);
    strcpy(newbind->topic, argv[2]);

    outstr = bind_print(outstr, newbind);
}

