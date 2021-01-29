#include "../General/general.h"
#include "../General/bool.h"


typedef struct variable{
  char name;
  double value;
}var;

typedef struct var_pool{
  var* v;
  unsigned int size;
  unsigned int capacity;
}var_pool;
