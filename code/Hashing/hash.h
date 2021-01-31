#include "../General/general.h"
#include "../General/bool.h"
#define INITPOOLSIZE 17
#define WARNINGLINE 0.7
#define SCALE_FACTOR 2
/*indicating that the table is almost full and needed to be resized*/

typedef unsigned int hash_index;

typedef struct item{
  char* name;
  double value;
}item;

typedef struct library{
  item* v;
  unsigned int size;
  unsigned int capacity;
}library;

library* library_init();
item* insert_item(char* name, double value, library* a);
double get_value(library* a, char* name);
void resize(library* a);
bool free_library(library* a);
hash_index hashcode(const void* key, unsigned int capacity);
