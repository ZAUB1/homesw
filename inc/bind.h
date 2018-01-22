#ifndef HSW_BIND_H
#define HSW_BIND_H

// Required by bindmode.h
typedef struct bind_s bind_s;

#include "bindmode.h"
#include "command.h"

/*
 * A chainlist of links between a device and a MQTT topic
 *
 * next     Next element of the chainlist, NULL for final element
 * mode     'Protocol' of the link
 * device   Device concerned
 * topic    MQTT topic concerned
 */
struct bind_s
{
    bind_s* next;
    bmode_s* mode;
    char device[MAX_CMD_ARGVLEN];
    char topic[MAX_CMD_ARGVLEN];
};

// List of the binds for each bind modes
extern bind_s* BINDS[NBMODES];

#endif

