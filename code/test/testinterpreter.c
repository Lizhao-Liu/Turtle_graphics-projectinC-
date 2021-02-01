#include "../Interpreter/interp.h"
#define SDL 1
#define TESTFILES 5

void test_interp_tiny_func();
void test_interp_integ_program();

int main_test()
{
  /*test newly-added tiny functions in interpret.c*/
  test_interp_tiny_func();
  /*test the whole program with example files*/
  test_interp_integ_program();
  return 0;
}

void test_interp_tiny_func()
{
  cur* c = create_cur();
  double d, check;
  stack* s;
  double result;
  var* v;

  /*test get_coord function*/
  printf("get_coord and update_coord functions test started...\n");
  c->degree = 90;
  d = 55;
  get_coord(c, d);
  check = d * SCALE;
  assert(c->x2-check < 1e-5);
  assert(c->y2-0 < 1e-5);
  c->degree = 180;
  get_coord(c, d);
  assert(c->x2-0 < 1e-5);
  assert(c->y2-check < 1e-5);
  c->degree = 120;
  d = 100;
  check = d * SCALE;
  get_coord(c, d);
  assert(c->y2-(check/2) < 1e-5);
  c->degree = -90;
  get_coord(c, d);
  assert(c->x2-(-check) < 1e-5);
  assert(c->y2-0 < 1e-5);

  /*test update_coord function*/
  update_coord(c);
  assert(c->x2 == c->x1);
  assert(c->y2 == c->y1);
  assert(c->x1-(-check) < 1e-5);
  assert(c->y1-0 < 1e-5);
  free(c);
  printf("get_coord and update_coord functions test passed.\n\n");

  /*test calculate function*/
  printf("calculate function test started...\n");
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
  printf("calculate function test passed.\n\n");


  /*test add_var and load_var functions*/
  printf("add_var and load_var functions test started...\n");

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
  printf("add_var and load_var functions test passed.\n\n");
}

void test_interp_integ_program()
{
  char* filename[TESTFILES] = {"../data/basic.ttl", "../data/loop.ttl", \
                              "../data/variable.ttl", "../data/nested.ttl",\
                              "../data/star.ttl"};
  Prog* p;
  cur* c;
  SDL_Simplewin sw;
  unsigned i;

  for(i=0; i<TESTFILES; i++){
    printf("file <%s> test started..\n", filename[i]);
    p = prog_init();
    p->library = (var*) ncalloc(sizeof(var), VARMAXSIZE);
    readin_prog(filename[i], p);
    #if SDL
    Neill_SDL_Init(&sw);
    #endif
    c = create_cur();
    Main(p, c, &sw);

    #if SDL
    SDL_Quit();
    atexit(SDL_Quit);
    #endif
    free(p->library);
    prog_free(p);
    free(c);
    printf("file <%s> passed\n", filename[i]);
  }
}
