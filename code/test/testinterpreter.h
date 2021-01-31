#include "../Interpreter/interp.h"

#define TEST_TO_RUN 2


void test_interp_tiny_func()
{
  /*test get_coord function*/
  cur* c = create_cur();
  double d;
  stack s;
  double result;
  var* v;

  c->degree = 90;
  d = 55;
  get_coord(c, d);
  assert(c->x2-55 < 1e-5);
  assert(c->y2-0 < 1e-5);
  c->degree = 180;
  get_coord(c, d);
  assert(c->x2-0 < 1e-5);
  assert(c->y2-55 < 1e-5);
  c->degree = 120;
  d = 100;
  get_coord(c, d);
  assert(c->y2-100/2 < 1e-5);
  c->degree = -90;
  get_coord(c, d);
  assert(c->x2-(-100) < 1e-5);
  assert(c->y2-0 < 1e-5);

  /*test update_coord function*/
  update_coord(c);
  assert(c->x2 = c->x1);
  assert(c->y2 = c->y1);
  assert(c->x1-(-100) < 1e-5);
  assert(c->y1-0 < 1e-5);

  free(c);

  /*test calculate function*/
  s = stack_init();
  stack_push(s, 6);
  stack_push(s, 2);
  calculate(s, '+');
  stack_peek(s, &result);
  assert(result - 8 <1e-5);
  stack_push(s, 4);
  calculate(s, '/');
  stack_peek(s, &result);
  assert(result - 2 <1e-5);
  stack_push(s, 9);
  calculate(s, '*');
  stack_peek(s, &result);
  assert(result - 18 <1e-5);
  stack_push(s, 18);
  calculate(s, '-');
  stack_pop(s, &result);
  assert(result - 0 <1e-5);
  assert(stack_isempty(s));
  assert(stack_free(s));

  v = (var*)ncalloc(sizeof(var), 5);
  add_var(v, 'A')->value = 1;
  add_var(v, 'B')->value = 2;
  add_var(v, 'C')->value = -3.2;
  add_var(v, 'D')->value = 999;
  add_var(v, 'E')->value = -0.44;
  assert(load_var(v, 'E')-(-0.44)<1e-5);
  assert(load_var(v, 'D')-999<1e-5);
  assert(load_var(v, 'C')-(-3.2)<1e-5);
  assert(load_var(v, 'B')-2<1e-5);
  assert(load_var(v, 'A')-1<1e-5);
  free(v);  

}
