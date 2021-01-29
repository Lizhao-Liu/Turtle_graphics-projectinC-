#include "Prog_struct_interp.h"

Prog* prog_init(void)
{
  Prog* p = (Prog*) ncalloc(sizeof(Prog), 1);
  p->str = (char**) ncalloc(sizeof(char*), INITSIZE);
  p->var_pool = (var*) ncalloc(sizeof(var), VARMAXSIZE);
  p->capacity = INITSIZE;
  return p;
}

bool prog_add(Prog* p, char* s)
{
  if(p==NULL){
    on_error("Please allocate memory for the program first");
  }
  p->str[p->size]=(char*) ncalloc(sizeof(char), strlen(s)+1);
  strcpy(p->str[p->size++], s);

  if(p->size >= p->capacity){
    p->str = (char**)nrecalloc(p->str, sizeof(char*)*p->capacity,\
              sizeof(char*)*p->capacity*SCALEFACTOR);
    p->capacity = p->capacity * SCALEFACTOR;
  }
  return true;
}

bool prog_free(Prog* p)
{
  unsigned int i;
  if(p==NULL){
    return true;
  }
  for(i=0; i<p->size; i++){
    free(p->str[i]);
  }
  free(p->var_pool);
  free(p->str);
  free(p);
  return true;
}

var* add_var(var* var_pool, char name)
{
  int index = name - 'A';
  var_pool[index].name = name;
  return &var_pool[index];
}

void store_var(var* var_pool, var* v)
{
  int index = v->name - 'A';
  var_pool[index].value = v->value;
}

double load_var(var* var_pool, char name)
{
  int index = name - 'A';
  double d;
  if(var_pool[index].name==0){
    on_error("Cannot load the variable");
  }
  d = var_pool[index].value;
  return d;
}
