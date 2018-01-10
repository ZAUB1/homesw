#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define HOMESW_DIR "/var/run/homesw/"

#define FIFO_PATH_CMD (HOMESW_DIR "cmd.fifo")
#define FIFO_PATH_OUT (HOMESW_DIR "out.fifo")

#define MAX_CMD_ARGC 10
#define MAX_CMD_ARGVLEN 100
#define MAX_OUT_LEN 1000

void homesw_parsecmd(int argc, char** argv, char* outstr)
{
    for(int i = 0; i < argc; i++)
    {
        puts(argv[i]);
    }
    outstr[0] = '\0';
}

void homesw_atexit()
{
    unlink(FIFO_PATH_CMD);
    unlink(FIFO_PATH_OUT);
}

void sigint_handler(int signal)
{
    exit(EXIT_FAILURE);
}

void homesw_daemon()
{
    if(mkdir(HOMESW_DIR, 0600) == -1 && errno != EEXIST)
    {
        perror(HOMESW_DIR);
        exit(EXIT_FAILURE);
    }

    if(mkfifo(FIFO_PATH_CMD, 0600) != 0 || mkfifo(FIFO_PATH_OUT, 0600) != 0)
    {
        perror("mkfifo");
        fprintf(stderr, "Maybe homesw is already running. If not, try to delete %s and %s",
                FIFO_PATH_CMD, FIFO_PATH_OUT);
        exit(EXIT_FAILURE);
    }

    atexit(homesw_atexit);
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

        if(rd == -1)
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
        homesw_parsecmd(cmd_argc, cmd_argv, outstr);

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

void homesw_sendcmd(int argc, char** argv)
{
    if(argc > MAX_CMD_ARGC)
    {
        fputs("Too many arguments", stderr);
        exit(EXIT_FAILURE);
    }

    char* sendargv = calloc(argc * MAX_CMD_ARGVLEN, sizeof(char));

    for(int iarg = 0; iarg < argc; iarg++)
    {
        if(strlen(argv[iarg]) < MAX_CMD_ARGVLEN)
        {
            strcpy(sendargv + iarg * MAX_CMD_ARGVLEN, argv[iarg]);
        }
        else
        {
            fprintf(stderr, "Argument %d too long !\n", iarg);
            exit(EXIT_FAILURE);
        }
    }

    int fd_cmd = open(FIFO_PATH_CMD, O_WRONLY);
    if(fd_cmd == -1)
    {
        perror(FIFO_PATH_CMD);
        fputs("Is homesw running ?", stderr);
        exit(EXIT_FAILURE);
    }

    write(fd_cmd, sendargv, argc * MAX_CMD_ARGVLEN * sizeof(char));
    close(fd_cmd);

    int fd_out = open(FIFO_PATH_OUT, O_RDONLY);
    if(fd_out == -1)
    {
        perror(FIFO_PATH_OUT);
        fputs("Is homesw running ?", stderr);
        exit(EXIT_FAILURE);
    }

    char* outstr = malloc(MAX_OUT_LEN * sizeof(char));
    read(fd_out, outstr, MAX_OUT_LEN);
    puts(outstr);

    free(outstr);
    close(fd_out);

    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv)
{
    if(argc == 2 && strcmp(argv[1], "start") == 0)
    {
        puts("Starting homesw daemon...");
        homesw_daemon();
    }
    else
    {
        homesw_sendcmd(argc, argv);
    }
}

