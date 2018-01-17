#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "client.h"
#include "daemon.h"

int hsw_sendcmd(int argc, char** argv, char* outstr)
{
    if(argc >= MAX_CMD_ARGC)
    {
        fputs("Too many arguments", stderr);
        return -1;
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
            return -1;
        }
    }

    int fd_cmd = open(FIFO_PATH_CMD, O_WRONLY);
    if(fd_cmd == -1)
    {
        perror(FIFO_PATH_CMD);
        fputs("Is homesw running ?", stderr);
        return -1;
    }

    write(fd_cmd, sendargv, argc * MAX_CMD_ARGVLEN * sizeof(char));
    close(fd_cmd);

    int fd_out = open(FIFO_PATH_OUT, O_RDONLY);
    if(fd_out == -1)
    {
        perror(FIFO_PATH_OUT);
        fputs("Is homesw running ?", stderr);
        return -1;
    }

    read(fd_out, outstr, MAX_OUT_LEN);
    close(fd_out);

    return 0;
}
