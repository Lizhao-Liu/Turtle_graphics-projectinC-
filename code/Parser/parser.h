#include "../General/general.h"
#include "../General/bool.h"
#include "../Prog_struct/Prog_struct.h"


void readin_prog(char* filename, Prog* p);
void Main(Prog *p);
void Instrctlist(Prog *p);
void Instruction(Prog *p);
void FD(Prog *p);
void LT(Prog *p);
void RT(Prog *p);
void DO(Prog *p);
void SET(Prog *p);
void Polish(Prog *p);
void Op(Prog *p);
void Varnum(Prog *p);
bool isVar(char* s);
bool isNum(char* s);
bool isVarnum(char* s);
bool isOp(char* s);
