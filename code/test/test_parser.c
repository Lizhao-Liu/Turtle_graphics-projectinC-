#define TEST 1

#include "../Parser/parser.h"



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
