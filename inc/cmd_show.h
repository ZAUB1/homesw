#ifndef HSW_CMD_SHOW_H
#define HSW_CMD_SHOW_H

#include "bind.h"

/*
 * Show some binds
 */
void hsw_cmd_show(int argc, char** argv, char* outstr);

char* showbinds(char* outstr, bind_s* binds, bmode_s* mode);

#endif

