# Turtle Graphics (build a parser/interpreter in c)

## Grammar
> basic grammar
```
  <MAIN> ::= "{" <INSTRCTLST>
  <INSTRCTLST> ::= <INSTRUCTION><INSTRCTLST> |
  "}"
  <INSTRUCTION> ::= <FD> | <LT> |
  <RT> | <DO> | <SET>
  <FD> ::= "FD" <VARNUM>
  <LT> ::= "LT" <VARNUM>
  <RT> ::= "RT" <VARNUM>
  <DO> ::= "DO" <VAR> "FROM" <VARNUM> "TO"
  <VARNUM> "{" <INSTRCTLST>
  <VAR> ::= [A−Z]
  <VARNUM> ::= number | <VAR>
  <SET> ::= "SET" <VAR> ":=" <POLISH>
  <POLISH> ::= <OP> <POLISH> | <VARNUM> <POLISH> | ";" <OP> ::= "+" | "−" | "*" | "/"
```

> extended grammar
```
  <MAIN> ::= "{" <INSTRCTLST>
  <INSTRCTLST> ::= <INSTRUCTION><INSTRCTLST> | "}"
  <INSTRUCTION> ::= <FD> | <LT> | <RT> | <DO> | <SET> | <DEFINE> | <CALL>
  <FD> ::= "FD" <VARNUM> | "FD"  <VARNUM> <COLOR>
  <LT> ::= "LT" <VARNUM>
  <RT> ::= "RT" <VARNUM>
  <DO> ::= "DO" <VAR> "FROM" <VARNUM> "TO" <VARNUM> "{" <INSTRCTLST>
  <DEFINE> ::= "DEFINE" <NEWINSTRUCTION> "{" <INSTRCTLST>
  <CALL>::= "CALL" <NEWINSTRUCTION>
  <NEWINSTRUCTION> ::= "[" [A-Z]+ "]"
  <VAR> ::= [A-Za-z]+
  <VARNUM> ::= number | <VAR>
  <COLOR>::= "COLOR" <COLORCHOICES>
  <COLORCHOICES> ::= "Y" | "R" | "G" | "W" | "B" |"C" | "K"
  <SET> ::= "SET" <VAR> ":=" <POLISH>
  <POLISH> ::= <OP> <POLISH> | <VARNUM> <POLISH> | ";"
  <OP> ::= "+" | "−" | "*" | "/"
```

## Code
- [parser](https://github.com/Lizhao-Liu/projects/tree/main/code/Parser)
- [interpreter](https://github.com/Lizhao-Liu/projects/tree/main/code/Interpreter)
- [extension](https://github.com/Lizhao-Liu/projects/tree/main/code/Exten)
- [testing](https://github.com/Lizhao-Liu/projects/tree/main/code/test)
> data structs
- [Hashing](https://github.com/Lizhao-Liu/projects/tree/main/code/Hashing)
- [Prog_struct](https://github.com/Lizhao-Liu/projects/tree/main/code/Prog_struct)
- [Stack](https://github.com/Lizhao-Liu/projects/tree/main/code/Stack)

## Example Result
![]
