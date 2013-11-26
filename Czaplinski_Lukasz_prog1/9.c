#include "common.h"
pid_t p;

void func(int sig)
{
  if(p==0) {
    printf("child ");
  } else {
    printf("parent ");
  }
  struct sigaction act;
  memset(&act, 0, sizeof(act));
  switch(sig) {
    case SIGHUP:
      printf("got SIGHUP\n");
      break;
    case SIGINT:
      printf("got SIGINT\n");
      act.sa_handler = SIG_DFL;
      CERR(sigaction(SIGINT,&act,NULL), "signal set (int) failed");;
      break;
    case SIGTERM:
      printf("got SIGTERM\n");
      break;
  }
}

int main(void)
{
  struct sigaction act;
  memset(&act, 0, sizeof(act));
  act.sa_handler = &func;
  CERR(sigaction(SIGHUP,&act,NULL), "signal set (hup) failed");;
  CERR(sigaction(SIGTERM,&act,NULL), "signal set (term) failed");;
  CERR(sigaction(SIGINT,&act,NULL), "signal set (int) failed");;

  CERR(p = fork(), "fork failed");
  if(p==0)
  {
    while(1 > 0) {
      pause();
      printf("..woken up..\n");
    }
  } else {
    printf("child id %d\n", p);
    kill(p, SIGTERM);
    kill(p, SIGINT);
    pause();
    kill(p,SIGKILL);
  }
  return 0;
}
