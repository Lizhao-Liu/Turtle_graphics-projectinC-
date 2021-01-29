#include "../General/general.h"
#include "../General/bool.h"

#define MAXTOKENSIZE 10
#define SCALEFACTOR 2
#define INITSIZE 20
#define VARMAXSIZE 26

typedef struct variable{
  char name;
  double value;
}var;

typedef struct program{
  char** str;
  unsigned int cw; /*current word*/
  unsigned int size;
  unsigned int capacity;
  var* var_pool;
}Prog;

Prog* prog_init(void);
bool prog_add(Prog* p, char* s);
bool prog_free(Prog* p);
var* add_var(var* var_pool, char name);
void store_var(var* var_pool, var* v);
double load_var(var* var_pool, char name);
