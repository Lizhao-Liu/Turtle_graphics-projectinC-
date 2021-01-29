#include "../General/general.h"
#include "../General/bool.h"

typedef struct node{
  double d;
  struct node* next;
}node;

typedef struct stack{
  node* start;
  unsigned int size;
}stack;

stack* stack_init(void);
void stack_push(stack* s, double d);
bool stack_pop(stack* s, double* d);
bool stack_peek(stack*s,  double* d);
bool stack_isempty(stack* s);
bool stack_free(stack* s);
