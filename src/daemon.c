#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "client.h"
#include "command.h"
#include "daemon.h"

void hsw_daemon()
{
    if(mkdir(HSW_DIR, 0600) == -1 && errno != EEXIST)
    {
        perror(HSW_DIR);
        exit(EXIT_FAILURE);
    }

    if(mkfifo(FIFO_PATH_CMD, 0600) != 0 || mkfifo(FIFO_PATH_OUT, 0600) != 0)
    {
        perror("mkfifo");
        fprintf(stderr, "Maybe homesw is already running. If not, try to delete %s and %s",
                FIFO_PATH_CMD, FIFO_PATH_OUT);
        exit(EXIT_FAILURE);
    }

    atexit(hsw_daemonexit);
    signal(SIGINT, sigint_handler);

    while(1)
    {
        int fd_cmd = open(FIFO_PATH_CMD, O_RDONLY);
        if(fd_cmd == -1)
        {
            perror(FIFO_PATH_CMD);
            exit(EXIT_FAILURE);
        }

        int rd = 1;
        int cmd_argc = 0;
        char** cmd_argv = malloc(MAX_CMD_ARGC * sizeof(char*));

        for(; rd > 0 && cmd_argc < MAX_CMD_ARGC; cmd_argc++)
        {
            cmd_argv[cmd_argc] = malloc(MAX_CMD_ARGVLEN * sizeof(char));
            rd = read(fd_cmd, cmd_argv[cmd_argc], MAX_CMD_ARGVLEN);
        }

        if(rd == 0)
        {
            free(cmd_argv[cmd_argc - 1]);
            cmd_argc--;
        }
        else if(rd == -1)
        {
            perror(FIFO_PATH_CMD);
            exit(EXIT_FAILURE);
        }

        close(fd_cmd);

        int fd_out = open(FIFO_PATH_OUT, O_WRONLY);
        if(fd_out == -1)
        {
            perror(FIFO_PATH_OUT);
            exit(EXIT_FAILURE);
        }

        char* outstr = malloc(MAX_OUT_LEN * sizeof(char));
        hsw_parsecmd(cmd_argc, cmd_argv, outstr);

        write(fd_out, outstr, strlen(outstr) + 1);
        close(fd_out);

        for(int iarg = 0; iarg < cmd_argc; iarg++)
        {
            free(cmd_argv[iarg]);
        }
        free(cmd_argv);
        free(outstr);
    }
}

void hsw_daemonexit()
{
    unlink(FIFO_PATH_CMD);
    unlink(FIFO_PATH_OUT);
}

void sigint_handler(int signal)
{
    exit(EXIT_FAILURE);
}

