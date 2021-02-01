#include "../General/general.h"
#include "../General/bool.h"
#include "../Prog_struct/Prog_struct.h"

/*Read in strings from file*/
void readin_prog(char* filename, Prog* p);
/*parse the grammar of Main*/
void Main(Prog *p);
/*parse the grammar of Instrctlist*/
void Instrctlist(Prog *p);
/*parse the grammar of Instruction*/
void Instruction(Prog *p);
/*parse the grammar of FD*/
void FD(Prog *p);
/*parse the grammar of LT*/
void LT(Prog *p);
/*parse the grammar of RT*/
void RT(Prog *p);
/*parse the grammar of DO*/
void DO(Prog *p);
/*parse the grammar of SET*/
void SET(Prog *p);
/*parse the grammar of POLISH*/
void Polish(Prog *p);
/*parse the grammar of OP*/
void Op(Prog *p);
/*parse the grammar of Varnum*/
void Varnum(Prog *p);
/*check if the word is a variable*/
bool isVar(char* s);
/*check if the word is a number*/
bool isNum(char* s);
/*check if the word is a number or a variable*/
bool isVarnum(char* s);
/*check if the word is a operator*/
bool isOp(char* s);
