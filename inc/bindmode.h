#ifndef HSW_BINDMODE_H
#define HSW_BINDMODE_H

#define NBMODES 4
#define BMODE_OWI 0
#define BMODE_OWO 1
#define BMODE_FLI 2
#define BMODE_FLO 3

extern char* BMODE_STR[NBMODES];

typedef int (*bmode_devicechecker_t)(char*);
bmode_devicechecker_t BMODE_VALIDDEVICE[NBMODES];

int bmode_owi_validdevice(char* device);
int bmode_owo_validdevice(char* device);
int bmode_fli_validdevice(char* device);
int bmode_flo_validdevice(char* device);

#endif

