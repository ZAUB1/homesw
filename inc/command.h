#ifndef HSW_COMMAND_H
#define HSW_COMMAND_H

#include "client.h"

/*
 * Represents a command
 *
 * label    Name of the command
 * action   Function associated with the label
 */
typedef struct
{
    char* label;
    void (*action)(int, char**, char*);
    int argc;
    char* format;
} command_s;

#include "cmd_bind.h"
#include "cmd_stop.h"

#define NCOMMANDS 2
extern command_s COMMANDS[NCOMMANDS];

/*
 * Parse a command
 * Called by the daemon's loop hsw_daemon()
 *
 * argc     The number of arguments in the command, at most MAX_CMD_ARGC.
 *
 * argv     The command itself, should contains the argc number of arguments. Each argument should
 *          be null terminated and shorter than MAX_CMD_ARGVLEN (including the final null byte).
 *
 * outstr   Buffer of size MAX_OUT_LEN that will contains the daemon's answer.
 */
void hsw_parsecmd(int argc, char** argv, char* outstr);

#endif

