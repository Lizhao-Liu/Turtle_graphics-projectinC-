CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c90
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS = -lm

testparser: Parser/parser.h Parser/parser.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h General/general.h General/general.c Parser/testparser.c Stack/stack.h Stack/stack.c
	$(CC) Parser/testparser.c Parser/parser.c Prog_struct/Prog_struct.c General/general.c Stack/stack.c -o testparser  $(PRODUCTION) $(LDLIBS)

testparser_s: Parser/parser.h Parser/parser.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h General/general.h General/general.c Parser/testparser.c Stack/stack.h Stack/stack.c
	$(CC) Parser/testparser.c Parser/parser.c Prog_struct/Prog_struct.c General/general.c Stack/stack.c -o testparser_s  $(SANITIZE) $(LDLIBS)

testparser_v: Parser/parser.h Parser/parser.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h General/general.h General/general.c Parser/testparser.c Stack/stack.h Stack/stack.c
	$(CC) Parser/testparser.c Parser/parser.c Prog_struct/Prog_struct.c General/general.c Stack/stack.c -o testparser_v  $(VALGRIND) $(LDLIBS)


interpret: Interpreter/interp.h Interpreter/interp.c Prog_struct/Prog_struct_interp.c Prog_struct/Prog_struct_interp.h General/general.h General/general.c Stack/stack.h Stack/stack.c sdl2/neillsdl2.h sdl2/neillsdl2.c
	$(CC) Interpreter/interp.c Prog_struct/Prog_struct_interp.c General/general.c Stack/stack.c sdl2/neillsdl2.c -o interpret $(PRODUCTION) $(LDLIBS)

clean:
	rm -f testparser_s testparser testparser_v
