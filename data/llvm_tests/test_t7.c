int glob;
int main(void)
{
  int locl;
  locl = 1;
  glob = -2;
  printf("%d\n", locl+glob);
  printf("%d\n", locl-glob);
  printf("%d\n", locl*glob);
  printf("%d\n", locl/glob);
  return 0;
}
