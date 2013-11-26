#include "common.h"

int main()
{
  pid_t pid = getpid();
  pid_t ppid = getppid();
  pid_t sid; 
  CERR(sid = getsid((pid_t)0), "getsid failed");
  pid_t pgrp = getpgrp();
  printf("PID=%d PPID=%d\nSID=%d PGRP=%d\n--\n",pid,ppid,sid,pgrp);
  CERR(system("ps f -O sess,pgrp,ppid"), "'system' call failed");
  return 0;
}
