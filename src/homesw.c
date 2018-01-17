#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "daemon.h"

int main(int argc, char** argv)
{
    if(argc == 1 || (argc == 2 && strcmp(argv[1], "start") == 0))
    {
        puts("Starting homesw daemon...");
        hsw_daemon();
    }
    else
    {
        char* outstr = malloc(MAX_OUT_LEN * sizeof(char));
        hsw_sendcmd(argc, argv, outstr);
        printf("%s", outstr);
        free(outstr);
    }
}

