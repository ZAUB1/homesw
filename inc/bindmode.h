#ifndef HSW_BINDMODE_H
#define HSW_BINDMODE_H

#include "bind.h"

/*
 * Represents a 'protocol' of a link between a device and a MQTT topic
 *
 * str          Name
 * valid_device Function that tells if a device name is valid
 * print_bind   Function used to print the bind concerned
 */
typedef struct bmode_s
{
    char* str;
    int (*valid_device)(char*);
    char* (*print_bind)(char*, bind_s*);
} bmode_s;

#define NBMODES 4
#define BMODE_OWI 0
#define BMODE_OWO 1
#define BMODE_FLI 2
#define BMODE_FLO 3

// Specifiactions of every bind mode
extern bmode_s BMODE[NBMODES];

// Return 1 if the device is valid and 0 if not
int bmode_owi_validdevice(char* device);
int bmode_owo_validdevice(char* device);
int bmode_fli_validdevice(char* device);
int bmode_flo_validdevice(char* device);

/*
 * Print a bind to a string
 *
 * outstr	Where the bind will be printed
 * bind     Bind to print_bind
 *
 * Return where to print other data, typically outstr + bytes written
 */
char* bmode_printbind_sensor(char* outstr, bind_s* bind);
char* bmode_printbind_actuator(char* outstr, bind_s* bind);

#endif

