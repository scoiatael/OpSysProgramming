#include "common.h"
int desc()
{
  printf("./6 <filename> { additional_args }\n");
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[], char *envp[])
{
  if(argc == 1) {
    return desc();
  }
  pid_t p;
  CERR(p=fork(),"fork failed"); 
  if(p==0) {
    execve(argv[1], &(argv[1]), envp);
  }
  else {
    printf("child id %d\n", p);
    int st;
    CERR(wait(&st), "wait failed");
    if(WIFSIGNALED(st)) {
      psignal(WTERMSIG(st), "child terminated by signal");
    }
  }
  return 0;
}
