#include "parser.h"
/*Test is set to one if there is a test being done*/
#define TEST 0
#define ACCEPTED_ARGS 2
#define MAXTOKENSIZE 10
#define strsame(A,B) (strcmp(A,B)==0)

int main_program(int argc, char* argv[]);
int main_test();


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
  if(argc!=ACCEPTED_ARGS){
    fprintf(stderr, "ERROR: Correct Usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  filename = ncalloc(sizeof(char), strlen(argv[1])+1);
  strcpy(filename, argv[1]);
  p = prog_init();
  readin_prog(filename, p);
  Main(p);
  free(filename);
  prog_free(p);
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

void Main(Prog *p)
{
  if(!strsame(p->str[p->cw],"{"))
  {
    prog_free(p);
    on_error("No Begin Symbol?");
  }
  p->cw = p->cw + 1;
  Instrctlist(p);
}

void Instrctlist(Prog *p)
{
  /*if the current word pointer has reached the end of the file but still didn't find the ending "}"*/
  if(p->cw >= p->size){
    prog_free(p);
    on_error("No ending Symbol?");
  }
  if(strsame(p->str[p->cw], "}")){
    return;
  }
  Instruction(p);
  p->cw = p->cw + 1;
  Instrctlist(p);
}

void Instruction(Prog *p)
{
  if(strsame(p->str[p->cw], "FD")){
    FD(p);
    return;
  }
  if(strsame(p->str[p->cw], "LT")){
    LT(p);
    return;
  }
  if(strsame(p->str[p->cw], "RT")){
    RT(p);
    return;
  }
  if(strsame(p->str[p->cw], "DO")){
    DO(p);
    return;
  }
  if(strsame(p->str[p->cw], "SET")){
    SET(p);
    return;
  }
  prog_free(p);
  on_error("Expecting an instruction?");
}

void FD(Prog *p)
{
  p->cw = p->cw + 1;
  Varnum(p);
}

void LT(Prog *p)
{
  p->cw = p->cw + 1;
  Varnum(p);
}

void RT(Prog *p)
{
  p->cw = p->cw + 1;
  Varnum(p);
}

void DO(Prog *p)
{
  p->cw = p->cw + 1;
  if(!isVar(p->str[p->cw])){
    prog_free(p);
    on_error("Expecting a variable?");
  }
  p->cw = p->cw + 1;
  if(!strsame(p->str[p->cw], "FROM")){
    prog_free(p);
    on_error("Incorrect Grammar: Expecting the word <FROM>?");
  }
  p->cw = p->cw + 1;
  Varnum(p);
  p->cw = p->cw + 1;
  if(!strsame(p->str[p->cw], "TO")){
    prog_free(p);
    on_error("Incorrect Grammar: Expecting the word <TO>?");
  }
  p->cw = p->cw + 1;
  Varnum(p);
  p->cw = p->cw + 1;
  if(!strsame(p->str[p->cw], "{")){
    prog_free(p);
    on_error("Incorrect Grammar: Expecting < { >?");
  }
  p->cw = p->cw + 1;
  Instrctlist(p);
}

void SET(Prog *p)
{
  p->cw = p->cw + 1;
  if(!isVar(p->str[p->cw])){
    prog_free(p);
    on_error("Expecting a varaible?");
  }
  p->cw = p->cw + 1;
  if(!strsame(p->str[p->cw], ":=")){
    prog_free(p);
    on_error("Incorrect Grammar: Expecting <:=>?");
  }
  Polish(p);
}

void Polish(Prog *p)
{
  p->cw = p->cw + 1;
  if(strsame(p->str[p->cw], ";")){
    return;
  }
  if(isOp(p->str[p->cw])){
    Polish(p);
  }
  if(isVarnum(p->str[p->cw])){
    Polish(p);
  }
}

void Op(Prog *p)
{
  if(!isOp(p->str[p->cw])){
    prog_free(p);
    on_error("Expecting an operator?");
  }
}

void Varnum(Prog *p)
{
  if(isVarnum(p->str[p->cw])){
    return;
  }
  prog_free(p);
  on_error("Expecting a number or a varaible?");
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
  /*except the condition that the decimal point is at the end \
  or more than one decimal points exist*/
  if(dp == i || count > 1) {
    return false;
  }
  return true;
}
