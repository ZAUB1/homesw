#ifndef HSW_DAEMON_H
#define HSW_DAEMON_H

#define HSW_DIR "/var/run/homesw/"
#define FIFO_PATH_CMD (HSW_DIR "cmd.fifo")
#define FIFO_PATH_OUT (HSW_DIR "out.fifo")

/*
 * Daemon's loop waiting for command on the named pipe FIFO_PATH_CMD
 */
void hsw_daemon();

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

/*
 * Routine at the daemon's exit
 */
void hsw_daemonexit();

/*
 * Handler for signal SIGINT
 * Allow the daemon to be stopped properly with Ctrl+C when running in foreground in a terminal
 */
void sigint_handler(int signal);

#endif
