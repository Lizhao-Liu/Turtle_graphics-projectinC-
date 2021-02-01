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

/*Read in strings from file*/
void readin_prog(char* filename, Prog* p);
/*Interpret  Main*/
void Main(Prog *p, cur* c, SDL_Simplewin *sw);
/*Interpret Instrctlist*/
void Instrctlist(Prog *p, cur *c, SDL_Simplewin *sw);
/*Interpret Instruction*/
void Instruction(Prog *p, cur *c, SDL_Simplewin *sw);
/*Interpret FD*/
void FD(Prog *p, cur *c, SDL_Simplewin *sw);
/*Interpret LT*/
void LT(Prog *p, cur *c);
/*Interpret RT*/
void RT(Prog *p, cur *c);
/*Interpret DO*/
void DO(Prog *p, cur *c, SDL_Simplewin *sw);
/*Interpret SET*/
void SET(Prog *p);
/*Interpret Polish and calculate the result of the polish expression*/
void Polish(Prog *p, double* result, stack* s);
/*interpret OP*/
void Op(Prog *p);
/*interpret VARNUM and return the corresponding value*/
double Varnum(Prog *p);
/*check if the word is a variable*/
bool isVar(char* s);
/*check if the word is a number*/
bool isNum(char* s);
/*check if the word is a number or a variable*/
bool isVarnum(char* s);
/*check if the word is a operator*/
bool isOp(char* s);
/*add a variable into the library*/
var* add_var(var* library, char name);
/*load the value a variable from the library*/
double load_var(var* library, char name);
/*create the cursor in order to draw the pattern*/
cur* create_cur(void);
/*get the values of the x and y coordinates in order to draw*/
void get_coord(cur *c, double dist);
/*update the values of the x and y coordinates*/
void update_coord(cur *c);
/*do the calculation using stack*/
void calculate(stack* s, char c);
