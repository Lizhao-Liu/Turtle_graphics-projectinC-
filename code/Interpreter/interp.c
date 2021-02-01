#include "interp.h"

#define TEST 1 /*if there is a test being done*/
#define SDL 1 /*if draw the output in sdl*/
#define ACCEPTED_ARGS 2
#define MAXTOKENSIZE 20
#define strsame(A,B) (strcmp(A,B)==0)
#define deg2rad(angle) ((angle) * M_PI / 180.0)/*change the angle degree to radian degree*/


int main_program(int argc, char* argv[]);
int main_test();
void draw(cur* c, SDL_Simplewin *sw);


int main(int argc, char* argv[]){
  /*if TEST is set as one, use the main_test function to do the test*/
  if(TEST==1){
    return main_test();
  }
  /*if TEST is set as zero, use the main_program function to parse the files inputted*/
  else{
    return main_program(argc, argv);
  }
}

int main_program(int argc, char* argv[])
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
  /*allocate the memory for the variable [A-Z], the maxsize is 26*/
  p->library = (var*) ncalloc(sizeof(var), VARMAXSIZE);
  readin_prog(filename, p);
  free(filename);
  #if SDL
  Neill_SDL_Init(&sw);
  #endif
  /*create a cursor*/
  c = create_cur();
  Main(p, c, &sw);

  #if SDL
  SDL_Quit();
  atexit(SDL_Quit);
  #endif
  free(p->library);
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
  if(!strsame(p->str[p->cw],"{")){
    prog_free(p);
    free(c);
    on_error("No Begin Symbol?");
  }
  p->cw = p->cw + 1;
  Instrctlist(p, c, sw);
}

void Instrctlist(Prog *p, cur *c, SDL_Simplewin *sw)
{
  /*if the current word pointer has reached the end of the file but still didn't find the ending "}"*/
  if(p->cw >= p->size){
    prog_free(p);
    free(c);
    on_error("No ending Symbol?");
  }
  if(strsame(p->str[p->cw], "}")){
    return;
  }
  Instruction(p, c, sw);
  p->cw = p->cw + 1;
  Instrctlist(p, c, sw);
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
  prog_free(p);
  free(c);
  on_error("Expecting an instruction?");
}

void FD(Prog *p, cur *c, SDL_Simplewin *sw)
{

  p->cw = p->cw + 1;
  /*get the coordinate value of the current cursor place*/
  get_coord(c, Varnum(p));
  #if SDL
  draw(c, sw);
  #endif
  /*
  printf("%d %d --> %d %d\n\n", c->x1+WWIDTH/2, c->y1+WHEIGHT/2, \
                                c->x2+WWIDTH/2, c->y2+WHEIGHT/2);*/
  update_coord(c);
}

void draw(cur* c, SDL_Simplewin *sw)
{
  Neill_SDL_SetDrawColour(sw, 255, 255, 255);
  SDL_RenderDrawLine(sw->renderer, c->x1+WWIDTH/2, c->y1+WHEIGHT/2,\
                                   c->x2+WWIDTH/2, c->y2+WHEIGHT/2);
  Neill_SDL_UpdateScreen(sw);
  SDL_Delay(MILLISECONDDELAY);
  Neill_SDL_Events(sw);
}

void LT(Prog *p, cur *c)
{
  p->cw = p->cw + 1;
  /*calculate the angle of turn*/
  c->degree -= fmod(Varnum(p), 360);
}

void RT(Prog *p, cur *c)
{
  p->cw = p->cw + 1;
  /*calculate the angle of turn*/
  c->degree += fmod(Varnum(p), 360);
}

void DO(Prog *p, cur *c, SDL_Simplewin *sw)
{
  unsigned vpos, min, max, startplace;
  var* v;

  p->cw = p->cw + 1;
  if(!isVar(p->str[p->cw])){
    prog_free(p);
    free(c);
    on_error("Expecting a variable?");
  }
  vpos = p->cw; /*the place of the variable*/

  p->cw = p->cw + 1;
  if(!strsame(p->str[p->cw], "FROM")){
    prog_free(p);
    free(c);
    on_error("Incorrect Grammar: Expecting the word <FROM> in DO?");
  }

  p->cw = p->cw + 1;
  min = Varnum(p); /*the starting/min value of the variable*/

  p->cw = p->cw + 1;
  if(!strsame(p->str[p->cw], "TO")){
    prog_free(p);
    free(c);
    on_error("Incorrect Grammar: Expecting the word <TO> in DO?");
  }

  p->cw = p->cw + 1;
  max = Varnum(p);/*the max value of the variable*/

  p->cw = p->cw + 1;
  if(!strsame(p->str[p->cw], "{")){
    on_error("Incorrect Grammar: Expecting < { > in DO?");
  }

  p->cw = p->cw + 1;
  startplace = p->cw; /*refers to the starting instruction in the loop*/
  v = add_var(p->library, p->str[vpos][0]); /*add the variable to the variable pool*/
  v->value = min; /*store the variable value*/
  while(v->value <= max){
    p->cw = startplace; /*starting at the first instruction in the loop every time*/
    Instrctlist(p, c, sw);
    v->value = v->value + 1;
  }
}

void SET(Prog *p)
{
  var* v;
  stack *s;
  p->cw = p->cw + 1;
  if(!isVar(p->str[p->cw])){
    prog_free(p);
    on_error("Expecting a varaible? in SET");
  }
  if(!strsame(p->str[p->cw+1], ":=")){
    prog_free(p);
    on_error("Incorrect Grammar: Expecting <:=> in SET?");
  }

  v = add_var(p->library, p->str[p->cw][0]);
  p->cw = p->cw + 1;
  s = stack_init();
  Polish(p, &(v->value), s);/*store the value of the variable after calculating the polish expression*/
}

void Polish(Prog *p, double* result, stack* s)
{
  p->cw = p->cw + 1;
  if(strsame(p->str[p->cw], ";")){
    if(!stack_pop(s, result)){
      stack_free(s);
      prog_free(p);
      on_error("Fail to calculate the result in SET");
    }
    if(!stack_isempty(s)){
      stack_free(s);
      prog_free(p);
      on_error("Fail to calculate the result in SET");
    }
    stack_free(s);
    return;
  }
  /*if there is an operator, do the calculation*/
  if(isOp(p->str[p->cw])){
    calculate(s, p->str[p->cw][0]);
    Polish(p, result, s);
  }
  /*if there is a variable or number, push it to the stack*/
  else if(isVarnum(p->str[p->cw])){
    stack_push(s, Varnum(p));
    Polish(p, result, s);
  }
  else{
    stack_free(s);
    prog_free(p);
    on_error("Cannot read the polish expression");
  }
}

void Op(Prog *p)
{
  if(!isOp(p->str[p->cw])){
    prog_free(p);
    on_error("Expecting an operator?");
  }
}

double Varnum(Prog *p)
{
  double d = 0;
  char* s = p->str[p->cw];
  if(isVar(s)){
    d = load_var(p->library, s[0]);
  }
  else if(isNum(s)){
    sscanf(s, "%lf", &d);
  }
  else{
    prog_free(p);
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
  unsigned int dp = 0; /*the place of decimal point if existed*/
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

var* add_var(var* library, char name)
{
  /*stored in alphabetical sequence, so as to reach O(1) complexity*/
  int index = name - 'A';
  library[index].name = name;
  return &library[index];
}


double load_var(var* library, char name)
{
  int index = name - 'A';
  double d;
  if(library[index].name==0){
    on_error("Cannot load the variable");
  }
  d = library[index].value;
  return d;
}
