#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "command.h"
#include "daemon.h"

void hsw_help()
{
    puts("");
    puts("homesw - let a 1-wire bus communicate with a MQTT broker");
    puts("");
    puts("Syntax: homesw <command> [aruments]");
    puts("");
    puts("Commands:");
    puts("");

    for(int icmd = 0; icmd < NCOMMANDS; icmd++)
    {
        printf("%s %s\n  %s\n\n", COMMANDS_UNSORTED[icmd].label, COMMANDS_UNSORTED[icmd].format,
                COMMANDS_UNSORTED[icmd].help);
    }
}

int main(int argc, char** argv)
{
    memcpy(COMMANDS, COMMANDS_UNSORTED, sizeof(COMMANDS));
    qsort(COMMANDS, NCOMMANDS, sizeof(command_s), compare_cmd);

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

