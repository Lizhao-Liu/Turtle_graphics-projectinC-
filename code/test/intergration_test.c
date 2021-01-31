
int test_parser(void)
{
  char* filename = "../data/basic.ttl";
  Prog* p = prog_init();

  readin_prog(filename, p);
  Main(p);
  assert(p->cw==p->size-1);
  printf("Passed OK\n");
  prog_free(p);

  filename = "../data/loop.ttl";
  p = prog_init();
  readin_prog(filename, p);
  Main(p);
  assert(p->cw==p->size-1);
  printf("Passed OK\n");
  prog_free(p);

  filename = "../data/nested.ttl";
  p = prog_init();
  readin_prog(filename, p);
  Main(p);
  assert(p->cw==p->size-1);
  printf("Passed OK\n");
  prog_free(p);

  filename = "../data/variable.ttl";
  p = prog_init();
  readin_prog(filename, p);
  Main(p);
  assert(p->cw==p->size-1);
  printf("Passed OK\n");
  prog_free(p);

  return 0;
}
