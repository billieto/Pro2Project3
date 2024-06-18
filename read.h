#ifndef READ_H
#define READ_H

#include <stdio.h>
#include "main.h"

void read_header(char *filename);
void list(void);
void reverse(char *output);
void print_bytes(dword *var, dword size);
dword swap_32bit(dword val);
void check_file(FILE *wav);
void check_malloc(void *ptr);


#endif