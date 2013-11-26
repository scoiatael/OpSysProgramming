#include "common.h"

int main(int argc, const char *argv[])
{
  if(argc == 1) {
    printf("Usage: ./2 <arg>, arg is either no-zombie or zombie\n");
    return EXIT_FAILURE;
  }
  if(strcmp(argv[1], "no-zombie") == 0) {
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler=SIG_IGN;
    CERR(sigaction(SIGCHLD,&act,NULL), "signal set failed");;
    //if(SIG_ERR == signal(SIGCHLD, SIG_IGN)) perror( "signal set failed");
  }
  int pid;
  CERR(pid = fork(), "fork failed");
  if(pid == 0) {
    return EXIT_SUCCESS;
  } else {
    char str[64];
    sprintf(str, "ps -O -p %d", pid);
    CERR(system(str), "'system' call failed");
  }
  return EXIT_SUCCESS;
}
