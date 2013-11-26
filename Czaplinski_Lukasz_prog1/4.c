#include "common.h"
#define SCERR(X) CERR(system(X),"'system' call failed ");

int badArgs()
{
  printf("Usage: <command> arg where arg is either no-limit or limited\n");
  return EXIT_FAILURE;
}

int main(int argc, const char *argv[])
{
  if(argc == 1) {
    return badArgs();
  }
  int gdarg=0;
  if(strcmp(argv[1],"limited")==0)
  {
    gdarg++;
    struct rlimit limit;
    memset(&limit, 0, sizeof(limit));
    limit.rlim_cur=50;
    limit.rlim_max=50;
    CERR(setrlimit(RLIMIT_NPROC, &limit), "setrlimit failed");
  }
  if(strcmp(argv[1],"no-limit")==0)
  {
    gdarg++;
  }
  if(gdarg==0)
  {
    return badArgs();
  }
  //użyj id tego procesu:
  if( setpgid(0, 0) == -1)
    perror("setpgid failed ");
  pid_t pid = getpid();
  pid_t pgid = getpgid(0);
  printf("PGID=%d\n", pgid);
  int parent = 1;
  printf("forking..\n");
  int i;
  for(i = 0; (i<100) && (parent > 0); i++) {
    putchar('=');
    fflush(stdout);
    parent = fork();
  }
  if(parent == 0) {
    pause();
    return EXIT_SUCCESS;
  }
  printf(" done.\n");
  char cmd[64];
  sprintf(cmd,"ps f -o pgrp,pid,command --ppid %d", pgid);
  SCERR(cmd);
  if(parent == -1) {
    char desc[64];
    sprintf(desc, "Fork failed (created %d processes) ", i);
    perror(desc);
  } else {
    SCERR("sleep 5");
  }
  killpg(pid,SIGINT);
  return EXIT_SUCCESS;
}
