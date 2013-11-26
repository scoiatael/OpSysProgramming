#include "common.h"

pid_t pid=0;
void atexit_function()
{
  printf("pid %d: atexit function called.\n", pid);
}

int desc()
{
  printf("./5 { help | signal | exit {VAL{ | _exit {VAL} | pause | VAL }\n VAL specifies value returned by program with exit/_exit/return\n");
  return EXIT_FAILURE;
}

#define str_switch(X,Y,Z) if(strcmp(X,Y)==0) {Z}

int main(int argc, const char *argv[])
{
  pid = getpid();
  if(argc > 1) { str_switch(argv[1],"help", desc(); return EXIT_SUCCESS;); }
  CERRS(atexit(&atexit_function) != 0, "atexit failed"); 
  pid_t p;
  CERR(p=fork(),"fork failed");
  if(p > 0) {
    printf("ppid: %d, child id:%d\n", pid, p);
    pid = p;
  }
  if(argc>1) {
    str_switch(argv[1],"abort",abort(););
    str_switch(argv[1],"exit", 
        int ret = EXIT_SUCCESS;
        if (argc > 2) {
          ret = atoi(argv[2]);
         }
        exit(ret);
        );
    str_switch(argv[1],"_exit", 
        int ret = EXIT_SUCCESS;
        if (argc > 2) {
          ret = atoi(argv[2]);
         }
        _exit(ret);
        );
    str_switch(argv[1],"signal", pause(););
  }
  int ret = EXIT_SUCCESS;
  if(argc > 1) {
    ret = atoi(argv[1]);
  } 
  return ret;
}
