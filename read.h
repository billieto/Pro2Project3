#ifndef READ_H
#define READ_H

#include <stdio.h>
#include "main.h"

void read_header(char *filename);
void write_header(char *filename);
void list(void);
void reverse(char *output);
void mono(char *output);
void crop(char *output, int start, int end);
void print_bytes(dword *var, dword size);
void check_file(FILE *wav);
void check_malloc(void *ptr);


#endif