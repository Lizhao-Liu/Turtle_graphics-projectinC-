CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c90
SDLCFLAGS=`sdl2-config --cflags`
SDLLIBS=`sdl2-config --libs`
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS = -lm

parse: Parser/parser.h Parser/parser.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h General/general.h General/general.c
	$(CC) Parser/parser.c Prog_struct/Prog_struct.c General/general.c -o parse  $(PRODUCTION) $(LDLIBS)
parse_s: Parser/parser.h Parser/parser.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h General/general.h General/general.c
	$(CC) Parser/parser.c Prog_struct/Prog_struct.c General/general.c  -o parse_s  $(SANITIZE) $(LDLIBS)
parse_v: Parser/parser.h Parser/parser.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h General/general.h General/general.c
	$(CC)  Parser/parser.c Prog_struct/Prog_struct.c General/general.c  -o parse_v  $(VALGRIND) $(LDLIBS)
testparser: test/testparser.c Parser/parser.h Parser/parser.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h General/general.h General/general.c
	$(CC) test/testparser.c Parser/parser.c Prog_struct/Prog_struct.c General/general.c -o testparser  $(PRODUCTION) $(LDLIBS)


interp: Interpreter/interp.h Interpreter/interp.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h General/general.h General/general.c Stack/stack.h Stack/stack.c sdl2/neillsdl2.h sdl2/neillsdl2.c
	$(CC) Interpreter/interp.c Prog_struct/Prog_struct.c General/general.c Stack/stack.c sdl2/neillsdl2.c -o interp $(PRODUCTION) $(LDLIBS) $(SDLCFLAGS) $(SDLLIBS)
interp_s: Interpreter/interp.h Interpreter/interp.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h General/general.h General/general.c Stack/stack.h Stack/stack.c sdl2/neillsdl2.h sdl2/neillsdl2.c
	$(CC) Interpreter/interp.c Prog_struct/Prog_struct.c General/general.c Stack/stack.c sdl2/neillsdl2.c -o interp_s $(SANITIZE) $(LDLIBS) $(SDLCFLAGS) $(SDLLIBS)
interp_v: Interpreter/interp.h Interpreter/interp.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h General/general.h General/general.c Stack/stack.h Stack/stack.c sdl2/neillsdl2.h sdl2/neillsdl2.c
	$(CC) Interpreter/interp.c Prog_struct/Prog_struct.c General/general.c Stack/stack.c sdl2/neillsdl2.c -o interp_v $(VALGRIND) $(LDLIBS) $(SDLCFLAGS) $(SDLLIBS)
testinterp: test/testinterpreter.c Interpreter/interp.h Interpreter/interp.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h General/general.h General/general.c Stack/stack.h Stack/stack.c sdl2/neillsdl2.h sdl2/neillsdl2.c
	$(CC) test/testinterpreter.c Interpreter/interp.c Prog_struct/Prog_struct.c General/general.c Stack/stack.c sdl2/neillsdl2.c -o testinterp $(PRODUCTION) $(LDLIBS) $(SDLCFLAGS) $(SDLLIBS)


extension: Exten/extension.h Exten/extension.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h Hashing/hash.c Hashing/hash.h General/general.h General/general.c Stack/stack.h Stack/stack.c sdl2/neillsdl2.h sdl2/neillsdl2.c
	$(CC) Exten/extension.c Prog_struct/Prog_struct.c General/general.c Stack/stack.c Hashing/hash.c sdl2/neillsdl2.c -o extension $(PRODUCTION) $(LDLIBS) $(SDLCFLAGS) $(SDLLIBS)
extension_s: Exten/extension.h Exten/extension.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h Hashing/hash.c Hashing/hash.h General/general.h General/general.c Stack/stack.h Stack/stack.c sdl2/neillsdl2.h sdl2/neillsdl2.c
	$(CC) Exten/extension.c Prog_struct/Prog_struct.c General/general.c Stack/stack.c Hashing/hash.c sdl2/neillsdl2.c -o extension_s $(SANITIZE) $(LDLIBS) $(SDLCFLAGS) $(SDLLIBS)
extension_v: Exten/extension.h Exten/extension.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h Hashing/hash.c Hashing/hash.h General/general.h General/general.c Stack/stack.h Stack/stack.c sdl2/neillsdl2.h sdl2/neillsdl2.c
	$(CC) Exten/extension.c Prog_struct/Prog_struct.c General/general.c Stack/stack.c Hashing/hash.c sdl2/neillsdl2.c -o extension_v $(VALGRIND) $(LDLIBS) $(SDLCFLAGS) $(SDLLIBS)
testextension: test/testextension.c Exten/extension.h Exten/extension.c Prog_struct/Prog_struct.c Prog_struct/Prog_struct.h Hashing/hash.c Hashing/hash.h General/general.h General/general.c Stack/stack.h Stack/stack.c sdl2/neillsdl2.h sdl2/neillsdl2.c
	$(CC) test/testextension.c Exten/extension.c Prog_struct/Prog_struct.c General/general.c Stack/stack.c Hashing/hash.c sdl2/neillsdl2.c -o testextension $(PRODUCTION) $(LDLIBS) $(SDLCFLAGS) $(SDLLIBS)


unittest: test/unit_test.c Stack/stack.h Stack/stack.c Prog_struct/Prog_struct.h Prog_struct/Prog_struct.c Hashing/hash.h Hashing/hash.c General/general.h General/general.c
	$(CC) test/unit_test.c Stack/stack.c Prog_struct/Prog_struct.c Hashing/hash.c General/general.c -o unittest $(SANITIZE) $(LDLIBS) $(SDLCFLAGS) $(SDLLIBS)

clean:
	rm -f parse parse_s parse_v testparser interp interp_s interp_v testinterp extension extension_s extension_v testextension unittest
