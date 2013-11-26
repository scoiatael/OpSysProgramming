#include "common.h"
#include <sys/stat.h>
#include <fcntl.h>

void func(int sig)
{
  if(sig == SIGHUP) {
  } else {
    printf("something else\n");
  }
  return;
}

int main(void)
{
  struct sigaction act;
  memset(&act, 0, sizeof(act));
  act.sa_handler = &func;
  CERR(sigaction(SIGHUP,&act,NULL), "signal set failed");;
  pid_t p;
  int f;
  CERR(f = open("8example.txt", O_CREAT, S_IRWXU), "file open failed");
  CERR(p = fork(), "fork failed");
  if(p == 0) {
    while(1 > 0) {
      pause();
      off_t o;
      CERR(o = lseek(f,0,SEEK_CUR),"lseek failed");
      printf("Offset: %d\n", (int)o);
    }
  } else {
    printf("child id: %d\n", p);
    char buf[32];
    read(f, &buf, 20);
    buf[21]='\0';
    close(f);
    printf("read %s\n", buf);
    CERR(kill(p,SIGHUP),"kill (hup) failed");
    pause();
    CERR(kill(p,SIGKILL),"kill (kill) failed");
  }
  return 0;
}
