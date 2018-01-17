#ifndef HSW_CLIENT_H
#define HSW_CLIENT_H

#define MAX_CMD_ARGC 16
#define MAX_CMD_ARGVLEN 128
#define MAX_OUT_LEN 2048

/*
 * Send a command to the daemon and print the answer to stdout
 *
 * argc     The number of arguments in the command, at most MAX_CMD_ARGC.
 *
 * argv     The command itself, should contains the argc number of arguments. Each argument should
 *          be null terminated and shorter than MAX_CMD_ARGVLEN (including the final null byte).
 *
 * outstr   Buffer of size MAX_OUT_LEN that will contains the daemon's answer.
 *
 * Returns 0 if the command has been send and if the daemon answered, and -1 otherwise
 */
int hsw_sendcmd(int argc, char** argv, char* outstr);

#endif

