#include "../General/general.h"
#include "../General/bool.h"
#include "../Prog_struct/Prog_struct.h"
#include "../Stack/stack.h"
#include "../sdl2/neillsdl2.h"

#define SCALE 2
#define MILLISECONDDELAY 100
#define VARMAXSIZE 26 /*[A-Z]*/

typedef struct variable{
  char name;
  double value;
}var;

typedef struct cur{
  int x1, y1;
  int x2, y2;
  double degree;
}cur;

void readin_prog(char* filename, Prog* p);
void Main(Prog *p, cur* c, SDL_Simplewin *sw);
void Instrctlist(Prog *p, cur *c, SDL_Simplewin *sw);
void Instruction(Prog *p, cur *c, SDL_Simplewin *sw);
void FD(Prog *p, cur *c, SDL_Simplewin *sw);
void LT(Prog *p, cur *c);
void RT(Prog *p, cur *c);
void DO(Prog *p, cur *c, SDL_Simplewin *sw);
void SET(Prog *p);
void Polish(Prog *p, double* result, stack* s);
void Op(Prog *p);
double Varnum(Prog *p);
bool isVar(char* s);
bool isNum(char* s);
bool isVarnum(char* s);
bool isOp(char* s);
var* add_var(var* library, char name);
double load_var(var* library, char name);
cur* create_cur(void);
void get_coord(cur *c, double dist);
void update_coord(cur *c);
void calculate(stack* s, char c);
