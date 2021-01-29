#include <assert.h>
#include "../Stack/stack.h"
#include "parser.h"
#include <math.h>

void test_Prog_array();
void test_parser_tiny_func();
void test_stack();

int main(void)
{
  char* filename = "../data/basic.ttl";
  Prog* p = prog_init();

  readin_prog(filename, p);
  Main(p);
  assert(p->cw==p->size-1);
  printf("Passed OK\n");
  prog_free(p);

  filename = "../data/loop.ttl";
  p = prog_init();
  readin_prog(filename, p);
  Main(p);
  assert(p->cw==p->size-1);
  printf("Passed OK\n");
  prog_free(p);

  filename = "../data/nested.ttl";
  p = prog_init();
  readin_prog(filename, p);
  Main(p);
  assert(p->cw==p->size-1);
  printf("Passed OK\n");
  prog_free(p);

  filename = "../data/variable.ttl";
  p = prog_init();
  readin_prog(filename, p);
  Main(p);
  assert(p->cw==p->size-1);
  printf("Passed OK\n");
  prog_free(p);

  test_Prog_array();
  test_parser_tiny_func();
  test_stack();

  return 0;
}

/*int main_test_tiny_func(void)
{
  test_Prog_array();
  test_stack();
  test_parser_tiny_func();
  test_interp_tiny_func();

}*/

void test_Prog_array()
{
  Prog* p;
  unsigned int i;

  p = prog_init();
  assert(p->size==0);

  for(i=0; i<100; i++){
    assert(prog_add(p, "123"));
    assert(strcmp(p->str[i], "123")==0);
  }
  assert(p->size==100);
  assert(p->capacity==160);

  for(; i<1000; i++){
    assert(prog_add(p, "456"));
  }
  assert(p->size==1000);
  assert(p->capacity==1280);
  assert(strcmp(p->str[99], "456")!=0);
  assert(strcmp(p->str[99], "123")==0);
  assert(strcmp(p->str[999], "456")==0);

  assert(prog_free(p));
  assert(prog_free(NULL));
  printf("Prog_array test passed\n");
}

void test_stack()
{
  double d;
  double i;
  stack* s;

  assert(!stack_peek(NULL, &d));
  assert(!stack_pop(NULL, &d));

  s = stack_init();
  assert(!stack_peek(s, &d));
  assert(!stack_pop(s, &d));
  assert(stack_isempty(s));
  stack_push(s, 2.22);
  assert(stack_peek(s, &d));
  assert(d-2.22<1e-5);
  stack_push(s, 31);
  assert(stack_pop(s, &d));
  assert(d-31<1e-5);
  assert(!stack_isempty(s));
  assert(stack_pop(s, &d));
  assert(d-2.22<1e-5);
  assert(stack_isempty(s));

  for(i=0; i<1000; i++){
    stack_push(s, i);
  }
  for(i=999; i>=0; i--){
    assert(stack_pop(s, &d));
    assert(d-i<1e-5);
  }
  assert(stack_isempty(s));
  assert(!stack_peek(s, &d));
  assert(stack_free(s));
  printf("stack test Passed\n");
}

void test_parser_tiny_func()
{
  char* filename = "../data/basic.ttl";
  Prog* p;
  unsigned int i = 0;
  char* op[]={"+", "-", "*", "/"};

  /*test readin_prog function*/
  p = prog_init();
  readin_prog(filename, p);
  assert(strcmp(p->str[i++], "{")==0);
  assert(p->size==34);

  for(; i<p->size-1; i+=4){
    assert(strcmp(p->str[i], "FD")==0);
    assert(strcmp(p->str[i+1], "30")==0);
    assert(strcmp(p->str[i+2], "LT")==0);
    assert(strcmp(p->str[i+3], "45")==0);
  }
  assert(strcmp(p->str[p->size-1], "}")==0);
  assert(p->capacity==40);
  assert(prog_free(p));
  printf("readin_prog function test passed\n");

  /*test isOp function*/
  for(i=0; i<4; i++){
    assert(isOp(op[i]));
  }
  assert(!isOp("-/"));
  assert(!isOp("3+"));
  printf("isOp function test passed\n");

  /*test isVar function*/
  assert(isVar("O"));
  assert(isVar("Z"));
  assert(!isVar("a"));
  assert(!isVar("ABC"));
  assert(isVar("A"));
  assert(!isVar("Qs"));
  printf("isVar function test passed\n");

  /*test isNum function*/
  assert(isNum("2021"));
  assert(isNum("-111"));
  assert(isNum("0.0003"));
  assert(isNum("-999.99"));
  assert(!isNum("--22"));
  assert(!isNum("3.33.33"));
  assert(!isNum("0.93-2"));
  assert(isNum("0.00"));
  assert(isNum("30"));
  printf("isNum function test passed\n");

  /*test isVarnum function*/
  assert(isVarnum("222"));
  assert(isVarnum("E"));
  assert(!isVarnum("E23"));
  assert(!isVarnum("+"));
  printf("isVarnum function test passed\n");

}
