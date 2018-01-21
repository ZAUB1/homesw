#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bind.h"
#include "chainlist.h"
#include "command.h"
#include "util.h"

void hsw_cmd_show(int argc, char** argv, char* outstr_)
{
    char* outstr = outstr_;

    if(argc == 2)
    {
        int mode = -1;
        for(int imode = 0; imode < NBMODES; imode++)
        {
            if(strcmp(argv[0], BMODE[imode].str) == 0)
            {
                mode = imode;
            }
        }

        if(mode == -1)
        {
            outstr += max(0, sprintf(outstr, "Invalid mode %s, available modes are:", argv[0]));

            for(int imode = 0; imode < NBMODES; imode++)
            {
                outstr += max(0, sprintf(outstr, " %s", BMODE[imode].str));
            }
            return;
        }

        int id;
        if(sscanf(argv[1], "%d", &id) != 1)
        {
            outstr += max(0, sprintf(outstr, "Invalid id %s", argv[1]));
            return;
        }

        bind_s* toshow = chainlist_get(BINDS[mode], id - 1);
        if(toshow == NULL)
        {
            outstr += max(0, sprintf(outstr, "Index %d not found", id));
            return;
        }

        outstr = toshow->mode->print_bind(outstr, toshow);
        return;
    }
    else if(argc == 1)
    {
        int mode = -1;
        for(int imode = 0; imode < NBMODES; imode++)
        {
            if(strcmp(argv[0], BMODE[imode].str) == 0)
            {
                mode = imode;
            }
        }

        if(mode == -1)
        {
            outstr += max(0, sprintf(outstr, "Invalid mode %s, available modes are:", argv[0]));

            for(int imode = 0; imode < NBMODES; imode++)
            {
                outstr += max(0, sprintf(outstr, " %s", BMODE[imode].str));
            }
            return;
        }

        outstr = showbinds(outstr, BINDS[mode], &BMODE[mode]);
        return;
    }
    else
    {
        for(int imode = 0; imode < NBMODES; imode++)
        {
            if(imode != 0)// && BINDS[imode] != NULL)
            {
                outstr += max(0, sprintf(outstr, "\n\n"));
            }

            outstr = showbinds(outstr, BINDS[imode], &BMODE[imode]);
        }
        return;
    }
}

char* showbinds(char* outstr_, bind_s* currbind, bmode_s* mode)
{
    char* outstr = outstr_;

    if(currbind == NULL)
    {
        outstr += max(0, sprintf(outstr, "No %s binds", mode->str));
        return outstr;
    }

    int currid = 1;

    while(currbind != NULL)
    {
        if(currid != 1)
        {
            outstr += max(0, sprintf(outstr, "\n"));
        }

        outstr += max(0, sprintf(outstr, "%-3d ", currid));
        outstr = currbind->mode->print_bind(outstr, currbind);
        currbind = currbind->next;
        currid++;
    }

    return outstr;
}

