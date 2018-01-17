#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"

command_s COMMANDS[NCOMMANDS] =
{   { "bind", hsw_cmd_bind, 3, "<protocol> <name> <mqtt topic>" },
    { "stop", hsw_cmd_stop, 0, "" } };

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

    if(exec->argc != argc - 2)
    {
        sprintf(outstr, "Incorrect format!\nCorrect format is: homesw %s %s",
                exec->label, exec->format);
        return;
    }

    exec->action(argc - 1, argv + 1, outstr);
}

