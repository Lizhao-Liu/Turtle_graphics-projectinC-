#include "../Exten/extension.h"
#define TESTFILES 4

int main_test()
{
  char* filename[TESTFILES] = {"../data/exten_call.ttl", "../data/exten_color.ttl", \
                              "../data/exten_define.ttl", "../data/exten_variable.ttl"};
  Prog* p;
  cur* c;
  SDL_Simplewin sw;
  unsigned i;

  for(i=0; i<TESTFILES; i++){
    printf("file <%s> test started..\n", filename[i]);
    p = prog_init();
    p->library=library_init();
    readin_prog(filename[i], p);
    Neill_SDL_Init(&sw);
    c = create_cur();
    Main(p, c, &sw);
    SDL_Quit();
    atexit(SDL_Quit);
    free_library(p->library);
    prog_free(p);
    free(c);
    printf("file <%s> passed\n", filename[i]);
  }
  return 0;
}
