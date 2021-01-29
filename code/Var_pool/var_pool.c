#include "var_pool.h"

var* create_var(void)
{
  var* v = (var*) ncalloc(sizeof(var), 1);
  return v;
}
