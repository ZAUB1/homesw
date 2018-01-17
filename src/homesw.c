#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "daemon.h"

void hsw_help()
{
}

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        hsw_help();
        return 0;
    }
    else if(argc == 2 && strcmp(argv[1], "start") == 0)
    {
        puts("Starting homesw daemon...");
        hsw_daemon();
        return 0;
    }
    else
    {
        char* outstr = malloc(MAX_OUT_LEN * sizeof(char));

        hsw_sendcmd(argc, argv, outstr);
        printf("%s\n", outstr);

        free(outstr);
        return 0;
    }
}

