#include "../General/general.h"
#include "../General/bool.h"
#include "../Prog_struct/Prog_struct_interp.h"
#include "../Stack/stack.h"
#include <math.h>

/*#include "../sdl2/neillsdl2.h"*/
#define strsame(A,B) (strcmp(A,B)==0)
#define SCALE 10
#define WWIDTH 0
#define WHEIGHT 0


typedef struct cur{
  int x1, y1;
  int x2, y2;
  double degree;
}cur;



void readin_prog(char* filename, Prog* p);
void Main(Prog *p, cur* c);
void Instrctlist(Prog *p, cur *c);
void Instruction(Prog *p, cur *c);
void FD(Prog *p, cur *c);
void LT(Prog *p, cur *c);
void RT(Prog *p, cur *c);
void DO(Prog *p, cur *c);
void SET(Prog *p);
void Polish(Prog *p, double* result, stack* s);
void Op(Prog *p);
double Varnum(Prog *p);
bool isVar(char* s);
bool isNum(char* s);
bool isVarnum(char* s);
bool isOp(char* s);
