#include "../Stack/stack.h"
#include "../Hashing/hash.h"
#include "../Prog_struct/Prog_struct.h"
#include "../General/general.h"
#include "../General/bool.h"
#define TEST_TO_RUN 1


void test_stack();
void test_Prog_array();
void test_hash();
void test_tiny_func();


int main_test1(void);
int main_test_unit();
int main_test_tiny_func(void);
int main_program(int argc, char* argv[]);

/*int main(int argc, char *argv[])
{
     switch(TEST_TO_RUN){
       case 2:
         return main_test1();
       case 1:
         return main_test_unit();
       case 0:
         return main_program(argc, argv);
     }

}*/

/*int main_test_tiny_func(void)
{
  test_Prog_array();
  test_stack();*/
  /*test_tiny_func();*/
  /*for extension*/
  /*  test_hash();
  return 0;

}*/
int main()
{
  test_Prog_array();
  test_stack();
  test_hash();
  return 0;
}

void test_Prog_array()
{
  Prog* p;
  unsigned int i;

  printf("Prog_array unit test started...\n");

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

  printf("stack unit test started...\n");

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

void test_hash()
{
  library* a = library_init();
  unsigned n;

  printf("hashing unit test started...\n");

  insert_item("aaa", 33, a);
  insert_item("abc", 100, a);
  insert_item("zzsdfe", 9.99, a);
  insert_item("test1", 13, a);
  insert_item("ll", 0, a);
  insert_item("cba", 33, a);
  assert(get_value(a, "cba")-33 < 1e-5);
  assert((get_value(a, "cba")-get_value(a, "aaa"))<1e-5);
  assert(get_value(a, "ll")-0 < 1e-5);
  assert(get_value(a, "test1")-13 < 1e-5);
  assert(get_value(a, "abc") - 100 < 1e-5);
  insert_item("abc", 122, a);
  assert(get_value(a, "abc") - 122 < 1e-5);
  n = a->capacity;
  resize(a);
  assert(a->capacity = SCALE_FACTOR * n);
  assert(get_value(a, "zzsdfe")>9);
  assert(free_library(a));

  printf("hashing test Passed\n");
}
