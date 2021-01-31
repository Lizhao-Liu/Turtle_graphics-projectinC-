#define TEST
#include "test.h"
#include "../Parser/parser.h"

#define TESTFILES 4

void test_parser_tiny_func();
void test_parser_integ_program();

void test_parser()
{
  test_parser_tiny_func();
  test_parser_integ_program();
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

void test_parser_integ_program()
{
  char* filename[TESTFILES] = {"../data/basic.ttl", "../data/loop.ttl", "../data/variable.ttl", "../data/nested.ttl"};
  Prog* p;
  unsigned i;
  p = prog_init();
  for(i=0; i<TESTFILES; i++){
    readin_prog(filename[i], p);
    Main(p);
    prog_free(p);
    printf("file <%s> tested\n", filename[i]);
  }
}
