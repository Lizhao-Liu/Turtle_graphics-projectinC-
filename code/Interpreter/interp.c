#include "interp.h"
#include <assert.h>

#define ACCEPTED_ARGS 2
#define MAXTOKENSIZE 10
#define deg2rad(angle) ((angle) * M_PI / 180.0)

cur* create_cur(void);
void get_coord(cur *c, double dist);
void update_coord(cur *c);
void calculate(stack* s, char c);

int main(int argc, char* argv[])
{
  char* filename;
  Prog* p;
  cur* c;

  if(argc!=ACCEPTED_ARGS){
    fprintf(stderr, "ERROR: Correct Usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  filename = ncalloc(sizeof(char), strlen(argv[1])+1);
  strcpy(filename, argv[1]);
  printf("%s\n", filename);
  p = prog_init();
  readin_prog(filename, p);
  free(filename);
  c = create_cur();


  Main(p, c);
  prog_free(p);
  free(c);
  return 0;
}

void readin_prog(char* filename, Prog* p)
{
  FILE* fp = nfopen(filename, "r");
  char temp[MAXTOKENSIZE];

  while(fscanf(fp, "%s", temp)==1){
    prog_add(p, temp);
  }
  fclose(fp);
}

void Main(Prog *p, cur* c)
{
  if(!strsame(p->str[p->cw],"{"))
  {
    on_error("No Begin Symbol?");
  }
  p->cw = p->cw + 1;
  Instrctlist(p, c);
}

void Instrctlist(Prog *p, cur *c)
{
  if(strsame(p->str[p->cw], "}")){
    return;
  }
  Instruction(p, c);
  p->cw = p->cw + 1;
  Instrctlist(p, c);
}

void Instruction(Prog *p, cur *c)
{
  if(strsame(p->str[p->cw], "FD")){
    FD(p, c);
    return;
  }
  if(strsame(p->str[p->cw], "LT")){
    LT(p, c);
    return;
  }
  if(strsame(p->str[p->cw], "RT")){
    RT(p, c);
    return;
  }
  if(strsame(p->str[p->cw], "DO")){
    DO(p, c);
    return;
  }
  if(strsame(p->str[p->cw], "SET")){
    SET(p);
    return;
  }
  on_error("Expecting an instruction?");
}

void FD(Prog *p, cur *c)
{

  p->cw = p->cw + 1;
  get_coord(c, Varnum(p));
  printf("%d %d --> %d %d\n\n", c->x1, c->y1, c->x2, c->y2);
  update_coord(c);
}

void LT(Prog *p, cur *c)
{
  p->cw = p->cw + 1;
  c->degree -= fmod(Varnum(p), 360);
}

void RT(Prog *p, cur *c)
{
  p->cw = p->cw + 1;
  c->degree += fmod(Varnum(p), 360);
}

void DO(Prog *p, cur *c)
{
  unsigned vpos, min, max, startplace;
  var* v;

  p->cw = p->cw + 1;
  if(!isVar(p->str[p->cw])){
    on_error("Expecting a variable?");
  }
  vpos = p->cw;

  p->cw = p->cw + 1;
  if(!strsame(p->str[p->cw], "FROM")){
    on_error("Incorrect Grammar: Expecting the word <FROM>?");
  }

  p->cw = p->cw + 1;
  min = Varnum(p);

  p->cw = p->cw + 1;
  if(!strsame(p->str[p->cw], "TO")){
    on_error("Incorrect Grammar: Expecting the word <TO>?");
  }

  p->cw = p->cw + 1;
  max = Varnum(p);

  p->cw = p->cw + 1;
  if(!strsame(p->str[p->cw], "{")){
    on_error("Incorrect Grammar: Expecting < { >?");
  }

  p->cw = p->cw + 1;
  startplace = p->cw;
  v = add_var(p->var_pool, p->str[vpos][0]);
  v->value = min;
  while(v->value <= max){
    p->cw = startplace;
    Instrctlist(p, c);
    v->value = v->value + 1;
  }
}

void SET(Prog *p)
{
  var* v;
  stack *s;
  p->cw = p->cw + 1;
  if(!isVar(p->str[p->cw])){
    on_error("Expecting a varaible?");
  }
  if(!strsame(p->str[p->cw+1], ":=")){
    on_error("Incorrect Grammar: Expecting <:=>?");
  }

  v = add_var(p->var_pool, p->str[p->cw][0]);
  p->cw = p->cw + 1;
  s = stack_init();
  Polish(p, &(v->value), s);
}

void Polish(Prog *p, double* result, stack* s)
{
  p->cw = p->cw + 1;
  if(strsame(p->str[p->cw], ";")){
    if(!stack_pop(s, result)){
      stack_free(s);
      on_error("Fail to get the result");
    }
    if(!stack_isempty(s)){
      stack_free(s);
      on_error("Stack still has items on it?");
    }
    stack_free(s);
    return;
  }
  if(isOp(p->str[p->cw])){
    calculate(s, p->str[p->cw][0]);
    Polish(p, result, s);
  }
  else if(isVarnum(p->str[p->cw])){
    stack_push(s, Varnum(p));
    Polish(p, result, s);
  }
  else{
    stack_free(s);
    on_error("Cannot read the polish expression");
  }
}

void Op(Prog *p)
{
  if(!isOp(p->str[p->cw])){
    on_error("Expecting an operator?");
  }
}

double Varnum(Prog *p)
{
  double d = 0;
  char* s = p->str[p->cw];
  if(isVar(s)){
    d = load_var(p->var_pool, s[0]);
  }
  else if(isNum(s)){
    sscanf(s, "%lf", &d);
  }
  else{
    on_error("Expecting a number or a varaible?");
  }
  return d;
}

bool isOp(char* s)
{
  if(strlen(s)==1){
    if(s[0]=='+' || s[0]=='-' || s[0]=='*' || s[0]=='/'){
      return true;
    }
  }
  return false;
}

bool isVarnum(char* s)
{
  if(isVar(s) || isNum(s)){
    return true;
  }
  return false;
}

bool isVar(char* s)
{
  if(strlen(s)==1 && s[0]>='A' && s[0]<='Z'){
    return true;
  }
  return false;
}

bool isNum(char* s)
{
  unsigned int i=0;
  unsigned int dp; /*the place of decimal point if existed*/
  unsigned int count = 0; /*the number decimal points*/
  if(s[i]=='-'){ /*check if it is a negative number*/
    i++;
  }
  for(; i<strlen(s); i++){
    if(s[i]<'0' || s[i]>'9'){
      if(s[i]=='.'){
        dp = i;
        count++;
      }
      else{
        return false;
      }
    }
  }
  /*except the condition that the decimal point is at the end or more than one decimal points exist*/
  if(dp == i || count > 1) {
    return false;
  }
  return true;
}

cur* create_cur(void)
{
  cur* c = (cur*)ncalloc(sizeof(cur), 1);
  c->x1 = WWIDTH/2;
  c->y1 = WHEIGHT/2;
  return c;
}

void get_coord(cur *c, double dist) /*dist here refers to the hypotenuse in the Right triangle*/
{
  c->x2 = (int)(c->x1 + sin(deg2rad(c->degree))*dist*SCALE);
  c->y2 = (int)(c->y1 + cos(deg2rad(c->degree))*dist*SCALE);
}

void update_coord(cur *c)
{
  c->x1 = c->x2;
  c->y1 = c->y2;
}


void calculate(stack* s, char c)
{
  double d1, d2, r=0;
  if(!(stack_pop(s, &d2) && stack_pop(s, &d1))){
    stack_free(s);
    on_error("Cannot read the polish expression");
  }
  switch(c){
    case '+':
      r = d1 + d2;
      break;
    case '-':
      r = d1 - d2;
      break;
    case '*':
      r = d1 * d2;
      break;
    case '/':
      r = d1 / d2;
      break;
    default:
      stack_free(s);
      on_error("Cannot read the polish expression");
  }
  stack_push(s, r);
  printf("result is %f\n", r);
}
