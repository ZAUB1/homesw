#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bind.h"
#include "command.h"
#include "util.h"

void hsw_cmd_show(int argc, char** argv, char* outstr_)
{
    char* outstr = outstr_;

    for(int imode = 0; imode < NBMODES; imode++)
    {
        if(imode != 0)
        {
            outstr += max(0, sprintf(outstr, "\n"));
        }

        if(BINDS[imode] == NULL)
        {
            if(imode != 0)
            {
                outstr += max(0, sprintf(outstr, "\n"));
            }

            outstr += max(0, sprintf(outstr, "No %s bind", BMODE[imode].str));
        }
        else
        {
            int currid = 1;
            bind_s* currbind = BINDS[imode];

            while(currbind != NULL)
            {
                if(!(imode == 0 && currid == 1))
                {
                    outstr += max(0, sprintf(outstr, "\n"));
                }

                outstr += max(0, sprintf(outstr, "%-3d ", currid));
                outstr = currbind->mode->print_bind(outstr, currbind);
                currbind = currbind->next;
                currid++;
            }
        }
    }
}

