#include "stack.h"


stack* stack_init(void)
{
  stack* s = (stack*) ncalloc(sizeof(stack), 1);
  return s;
}

void stack_push(stack* s, double d)
{
  node* n = (node*) ncalloc(sizeof(node), 1);
  if(s){
    n->d = d;
    n->next = s->start;
    s->start = n;
    s->size++;
  }
}

bool stack_pop(stack* s, double* d)
{
  node* n;
  if(stack_isempty(s)){
     return false;
  }
  *d = s->start->d;
  n = s->start;
  s->start = n->next;
  free(n);
  s->size--;
  return true;
}


bool stack_peek(stack*s,  double* d)
{
  if(stack_isempty(s)){
     return false;
  }
  *d = s->start->d;
  return true;
}

bool stack_isempty(stack* s)
{
  if((s==NULL) || (s->start==NULL)){
    return true;
  }
  return false;
}

bool stack_free(stack* s)
{
   if(s){
      node* tmp;
      node* n = s->start;
      while(n!=NULL){
         tmp = n->next;
         free(n);
         n = tmp;
      }
      free(s);
   }
   return true;
}
