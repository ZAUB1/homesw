#ifndef HSW_COMMAND_H
#define HSW_COMMAND_H

#include "client.h"

/*
 * Represents a command
 *
 * label    Name of the command
 * action   Function associated with the label
 */
typedef struct command_s
{
    char* label;
    void (*action)(int, char**, char*);
    int minargc;
    int maxargc;
    char* format;
    char* help;
} command_s;

/*
 * Compare two commands
 * Used for qsort() and bsearch() calls
 */
int compare_cmd(const void* _a, const void* _b);

#include "cmd_stop.h"
#include "cmd_show.h"
#include "cmd_bind.h"

#define NCOMMANDS 4

extern command_s COMMANDS[NCOMMANDS];
extern command_s COMMANDS_UNSORTED[NCOMMANDS];

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

