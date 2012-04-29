#ifndef _MAIN_H_
#define _MAIN_H_

#include "stdio.h"
#include "stdlib.h"
#include "curses.h"

void parse_file(char* file_name);
void dump_hex(char* buff, unsigned int row, unsigned int line_dump, int y);
void write_hex(char* buff, unsigned int row, char y, char x, char byte);

#endif
