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
 * Routine at the daemon's exit
 */
void hsw_daemonexit();

/*
 * Handler for signal SIGINT
 * Allow the daemon to be stopped properly with Ctrl+C when running in foreground in a terminal
 */
void sigint_handler(int signal);

#endif

