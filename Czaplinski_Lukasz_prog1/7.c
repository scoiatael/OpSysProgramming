#include "common.h"

void printEd_Wd()
{
  char* bufE = getenv("EDITOR");
  CERRS(bufE==NULL, "getenv failed");
  printf(" EDITOR=%s\n", bufE);
  char bufCWD[1024];
  CERRS(getcwd(bufCWD, 1024)==NULL, "getcwd failed");
  printf(" cwd=%s\n", bufCWD);
}

void funPEW(int sig)
{
  if(sig==SIGHUP)
    printEd_Wd();
  else
    printf("Error\n");
}

void print_env(int argc, char* argv[], char* envp[])
{
  printf("%s args and environment:\n", argv[0]);
  for(int i=1; i< argc; i++) {
    printf(" %s\n", argv[i]);
  }
  for(int i=0; envp[i] != NULL; i++) {
//    char* envv = getenv(envp[i]);
    printf(" %s \n", envp[i]);
/*    if(envv==NULL) {
      printf(" no match\n");
    } else {
      printf("%s\n", envv);
    }
    free(envv);*/
  }
  printEd_Wd();
}

void setEd_Wd(const char* Ed, const char* Wd)
{
  CERR(setenv("EDITOR",Ed,1), "setenv failed");
  CERR(chdir(Wd), "chdir failed");
}

//int main(int argc, char *argv[], char* envp[])
int main(void)
{
  struct sigaction act;
  memset(&act, 0, sizeof(act));
  act.sa_handler=&printEd_Wd;
  CERR(sigaction(SIGHUP,&act,NULL), "signal set failed");;
  //print_env(argc, argv, envp); 
  printEd_Wd();
  setEd_Wd("vim","/home");
  pid_t p;
  CERR(p=fork(), "fork failed");
  if(p==0){
    pause();
//    printEd_Wd();
  } else if(p>0){
    system("sleep 1"); 
    setEd_Wd("nano","/");
    printEd_Wd();
    kill(p,SIGHUP);
  }
  return 0;
}
