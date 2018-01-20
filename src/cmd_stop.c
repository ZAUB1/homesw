#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void hsw_cmd_stop(int argc, char** argv, char* outstr_)
{
    puts("Stopping homesw daemon...");
    exit(EXIT_SUCCESS);
}

