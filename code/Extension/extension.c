#include "extension.h"

#define ACCEPTED_ARGS 2
#define MAXTOKENSIZE 20
#define MILLISECONDDELAY 100
#define strsame(A,B) (strcmp(A,B)==0)
#define deg2rad(angle) ((angle) * M_PI / 180.0)

cur* create_cur(void);
void get_coord(cur *c, double dist);
void update_coord(cur *c);
void calculate(stack* s, char c);
void draw(cur* c, SDL_Simplewin *sw);
void read_color(char *s, SDL_Simplewin *sw);
bool islegal(char c);
unsigned nextstep(Prog *p);
void CALL(Prog *p, cur *c, SDL_Simplewin *sw);
void DEFINE(Prog *p);

int main(int argc, char* argv[])
{
  char* filename;
  Prog* p;
  cur* c;
  SDL_Simplewin sw;

  if(argc!=ACCEPTED_ARGS){
    fprintf(stderr, "ERROR: Correct Usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  filename = ncalloc(sizeof(char), strlen(argv[1])+1);
  strcpy(filename, argv[1]);
  p = prog_init();
  p->library=library_init();
  readin_prog(filename, p);
  free(filename);

  /*Neill_SDL_Init(&sw);*/

  c = create_cur();
  Main(p, c, &sw);
  /*SDL_Quit();
  atexit(SDL_Quit);*/
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

void Main(Prog *p, cur* c, SDL_Simplewin *sw)
{
  if(!strsame(p->str[p->cw],"{"))
  {
    on_error("No Begin Symbol?");
  }
  p->cw = p->cw + 1;
  Instrctlist(p, c, sw);
}

void Instrctlist(Prog *p, cur *c, SDL_Simplewin *sw)
{
  if(strsame(p->str[p->cw], "}")){
    return;
  }
  Instruction(p, c, sw);
  p->cw = p->cw + 1;
  Instrctlist(p, c, sw);
  on_error("Expecting an ending <}>");
}

void Instruction(Prog *p, cur *c, SDL_Simplewin *sw)
{
  if(strsame(p->str[p->cw], "FD")){
    FD(p, c, sw);
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
    DO(p, c, sw);
    return;
  }
  if(strsame(p->str[p->cw], "SET")){
    SET(p);
    return;
  }
  if(strsame(p->str[p->cw], "DEFINE")){
    DEFINE(p);
    return;
  }
  if(strsame(p->str[p->cw], "CALL")){
    CALL(p, c, sw);
    return;
  }
  printf("%s\n", p->str[p->cw]);
  printf("Expecting an instruction?");
}

void CALL(Prog *p, cur *c, SDL_Simplewin *sw)
{
  unsigned pointer, len, next;
  p->cw = p->cw + 1;
  len = strlen(p->str[p->cw]);
  if(len > 2 && p->str[p->cw][0]=='[' \
             && p->str[p->cw][len-1] ==']'){
    pointer = (unsigned int)get_value(p->library, p->str[p->cw]);
    next = p->cw;
    p->cw = pointer;
    Instrctlist(p, c, sw);
    p->cw = next;
  }
  else{
    on_error("Cannot read the CALL instruction");
  }

}

void DEFINE(Prog *p)
{
  int len;
  unsigned int pointer;
  p->cw = p->cw + 1;
  len = strlen(p->str[p->cw]);
  if(len > 2 && p->str[p->cw][0]=='[' \
             && p->str[p->cw][len-1] ==']'\
             && strsame(p->str[p->cw+1], "{")){
    pointer = p->cw + 2;
    insert_item(p->str[p->cw], pointer, p->library);
    p->cw =p->cw + 1;
    p->cw = nextstep(p);
  }
  else{
    on_error("Cannot read the DEFINE instruction");
  }
}

unsigned nextstep(Prog *p)
{
  stack* s = stack_init();
  double temp = 1;
  do{
    if(p->cw == p->size){
      on_error("Cannot find the closing <}> in DEFINE");
    }
    if(strsame(p->str[p->cw], "{")){
      stack_push(s, temp);
    }
    if(strsame(p->str[p->cw], "}")){
      stack_pop(s, &temp);
    }
    p->cw = p->cw + 1;
  }while(!stack_isempty(s));
  stack_free(s);
  return p->cw - 1;
}


void FD(Prog *p, cur *c, SDL_Simplewin *sw)
{
  p->cw = p->cw + 1;
  get_coord(c, Varnum(p));
  /*if(strsame(p->str[p->cw+1], "COLOR")){
    p->cw = p->cw + 2;
    read_color(p->str[p->cw], sw);
  }
  else{
    Neill_SDL_SetDrawColour(sw, 255, 255, 255);
  }
  draw(c, sw);*/
  printf("%d %d --> %d %d\n\n", c->x1+WWIDTH/2, c->y1+WHEIGHT/2, c->x2+WWIDTH/2, c->y2+WHEIGHT/2);
  update_coord(c);
}

void read_color(char *s, SDL_Simplewin *sw)
{
  if(strlen(s)!=1){
    on_error("Expecting a colour choice? e.g. <G>");
  }
  switch(s[0]){
    case 'Y':
      Neill_SDL_SetDrawColour(sw, 255, 255, 0);
      break;
    case 'R':
      Neill_SDL_SetDrawColour(sw, 255, 0, 0);
      break;
    case 'G':
      Neill_SDL_SetDrawColour(sw, 0, 128, 0);
      break;
    case 'W':
      Neill_SDL_SetDrawColour(sw, 255, 255, 255);
      break;
    case 'B':
      Neill_SDL_SetDrawColour(sw, 0, 0, 255);
      break;
    case 'C':
      Neill_SDL_SetDrawColour(sw, 0, 255, 255);
      break;
    case 'P':
      Neill_SDL_SetDrawColour(sw, 255, 0, 255);
    case 'K':
      Neill_SDL_SetDrawColour(sw, 0, 0, 0);
      break;
    default:
      on_error("Cannot read your colour choice? try e.g. <G> for green");
  }
}

void draw(cur* c, SDL_Simplewin *sw)
{
  SDL_RenderDrawLine(sw->renderer, c->x1+WWIDTH/2, c->y1+WHEIGHT/2,\
                                   c->x2+WWIDTH/2, c->y2+WHEIGHT/2);
  Neill_SDL_UpdateScreen(sw);
  SDL_Delay(MILLISECONDDELAY);
  Neill_SDL_Events(sw);
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

void DO(Prog *p, cur *c, SDL_Simplewin *sw)
{
  unsigned vpos, min, max, startplace;
  item* v;

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
  v = insert_item(p->str[vpos], min, p->library);
  while(v->value <= max){
    p->cw = startplace;
    Instrctlist(p, c, sw);
    v->value = v->value + 1;
  }
}

void SET(Prog *p)
{
  double value;
  stack *s;
  unsigned int vpos;
  p->cw = p->cw + 1;
  if(!isVar(p->str[p->cw])){
    on_error("Expecting a varaible?");
  }
  if(!strsame(p->str[p->cw+1], ":=")){
    on_error("Incorrect Grammar: Expecting <:=>?");
  }
  vpos = p->cw;
  p->cw = p->cw + 1;
  s = stack_init();
  Polish(p, &(value), s);
  insert_item(p->str[vpos], value, p->library);
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
  if(isNum(s)){
    sscanf(s, "%lf", &d);
  }
  else if(isVar(s)){
    d = get_value(p->library, s);
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
  unsigned int len = strlen(s);
  unsigned int i;

  for(i=0; i<len; i++){
    if(!islegal(s[i])){
      return false;
    }
  }
  return true;
}

bool islegal(char c)
{
  if(c>='A' && c<='Z'){
    return true;
  }
  if(c>='a' && c<='z'){
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
  return c;
}

void get_coord(cur *c, double dist) /*dist here refers to the hypotenuse in the Right triangle*/
{
  c->x2 = (int)(c->x1 + (sin(deg2rad(c->degree))*dist*SCALE));
  c->y2 = (int)(c->y1 - (cos(deg2rad(c->degree))*dist*SCALE));
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
}
