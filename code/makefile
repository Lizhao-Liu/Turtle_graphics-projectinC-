CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c90
SDLCFLAGS=`sdl2-config --cflags`
SDLLIBS=`sdl2-config --libs`
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS = -lm

testparser: test/testparser.c test/test.h Parser/parser.h Parser/parser.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h General/general.h General/general.c
	$(CC) test/testparser.c Parser/parser.c Prog_struct/Prog_struct.c General/general.c -o testparser  $(PRODUCTION) $(LDLIBS)

testparser_s: Parser/parser.h Parser/parser.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h General/general.h General/general.c Parser/testparser.c Stack/stack.h Stack/stack.c
	$(CC) Parser/testparser.c Parser/parser.c Prog_struct/Prog_struct.c General/general.c Stack/stack.c -o testparser_s  $(SANITIZE) $(LDLIBS)

testparser_v: Parser/parser.h Parser/parser.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h General/general.h General/general.c Parser/testparser.c Stack/stack.h Stack/stack.c
	$(CC) Parser/testparser.c Parser/parser.c Prog_struct/Prog_struct.c General/general.c Stack/stack.c -o testparser_v  $(VALGRIND) $(LDLIBS)


interpret: Interpreter/interp.h Interpreter/interp.c Prog_struct/Prog_struct_interp.c Prog_struct/Prog_struct_interp.h General/general.h General/general.c Stack/stack.h Stack/stack.c sdl2/neillsdl2.h sdl2/neillsdl2.c
	$(CC) Interpreter/interp.c Prog_struct/Prog_struct_interp.c General/general.c Stack/stack.c sdl2/neillsdl2.c -o interpret $(PRODUCTION) $(LDLIBS) $(SDLCFLAGS) $(SDLLIBS)

extension: Extension/extension.h Extension/extension.c Prog_struct/Prog_struct_interp.c Prog_struct/Prog_struct_interp.h Hashing/hash.c Hashing/hash.h General/general.h General/general.c Stack/stack.h Stack/stack.c sdl2/neillsdl2.h sdl2/neillsdl2.c
	$(CC) Extension/extension.c Prog_struct/Prog_struct_interp.c General/general.c Stack/stack.c Hashing/hash.c sdl2/neillsdl2.c -o exten $(SANITIZE) $(LDLIBS) $(SDLCFLAGS) $(SDLLIBS)



unittest: test/unit_test.c Stack/stack.h Stack/stack.c Prog_struct/Prog_struct.h Prog_struct/Prog_struct.c Hashing/hash.h Hashing/hash.c General/general.h General/general.c Parser/parser.h Parser/parser.c
	$(CC) test/unit_test.c Stack/stack.c Prog_struct/Prog_struct.c Hashing/hash.c General/general.c Parser/parser.c -o unittest $(SANITIZE) $(LDLIBS) $(SDLCFLAGS) $(SDLLIBS)

clean:
	rm -f testparser_s testparser testparser_v
