#include "../General/general.h"
#include "../General/bool.h"
#include "../Prog_struct/Prog_struct.h"
#include "../Stack/stack.h"
#include "../Hashing/hash.h"
#include "../sdl2/neillsdl2.h"

#define MILLISECONDDELAY 100
#define SCALE 2

typedef struct cur{
  int x1, y1;
  int x2, y2;
  double degree;
}cur;

typedef struct variable{
  char name;
  double value;
}var;

void readin_prog(char* filename, Prog* p);
void Main(Prog *p, cur* c, SDL_Simplewin *sw);
void Instrctlist(Prog *p, cur *c, SDL_Simplewin *sw);
void Instruction(Prog *p, cur *c, SDL_Simplewin *sw);
void FD(Prog *p, cur *c, SDL_Simplewin *sw);
void LT(Prog *p, cur *c);
void RT(Prog *p, cur *c);
void DO(Prog *p, cur *c, SDL_Simplewin *sw);
void SET(Prog *p);
void CALL(Prog *p, cur *c, SDL_Simplewin *sw);
void DEFINE(Prog *p);
void Polish(Prog *p, double* result, stack* s);
void Op(Prog *p);
double Varnum(Prog *p);
bool isVar(char* s);
bool isNum(char* s);
bool isVarnum(char* s);
bool isOp(char* s);
cur* create_cur(void);
