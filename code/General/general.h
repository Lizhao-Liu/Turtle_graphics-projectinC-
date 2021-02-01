#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#define EXIT_FAILURE 1

void* ncalloc(int n, size_t size);
void* nrecalloc(void* p, int oldsz, int newsz);
void* nfopen(char* fname, char* mode);
void on_error(const char* s);
