#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "daemon.h"

command_s COMMANDS[NCOMMANDS];
command_s COMMANDS_UNSORTED[NCOMMANDS] =
{   /* Stands here only to be displayed in help message, the start command
       will not be interpreted by this way */
    { "start", hsw_daemon, 0, 0, "", 
      "Start homesw daemon and load the config file" },

    { "stop", hsw_cmd_stop, 0, 0, "",
      "Stop homesw daemon" },

    { "show", hsw_cmd_show, 0, 1, "[all|<id>]",
      "Show all the binds" },

    { "bind", hsw_cmd_bind, 3, 3, "<mode> <name> <mqtt topic>",
      "Bind a device to a MQTT topic" } };

int compare_cmd(const void* _a, const void* _b)
{
    command_s* a = (command_s*) _a;
    command_s* b = (command_s*) _b;
    return strcmp(a->label, b->label);
}

void hsw_parsecmd(int argc, char** argv, char* outstr)
{
    outstr[0] = '\0';

    if(argc < 2)
    {
        sprintf(outstr, "Not enough arguments");
        return;
    }

    command_s cmd;
    strcpy(cmd.label, argv[1]);

    command_s* exec = bsearch(&cmd, COMMANDS, NCOMMANDS, sizeof(command_s), compare_cmd);

    if(exec == NULL)
    {
        sprintf(outstr, "Unknown command %s", cmd.label);
        return;
    }

    if(exec->minargc > argc - 2 || exec->maxargc < argc - 2 )
    {
        sprintf(outstr, "Incorrect number of arguments!\nCorrect format is: homesw %s %s",
                exec->label, exec->format);
        return;
    }

    exec->action(argc - 1, argv + 1, outstr);
}

