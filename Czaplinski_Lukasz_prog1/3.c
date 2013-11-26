#include "common.h"

int id()
{
  uid_t uid = getuid();
  struct passwd* pwuid = getpwuid(uid);    
  gid_t gid = getgid();
  int grpNr=0;
  gid_t* groups = malloc(32*sizeof(gid));;
  int r = getgrouplist(pwuid->pw_name,pwuid->pw_gid, groups, &grpNr);
  if(r==-1) {
    free(groups);
    groups = malloc((grpNr+1) * sizeof(gid_t));
    r = getgrouplist(pwuid->pw_name,pwuid->pw_gid, groups, &grpNr);
  }
  struct group* grp = getgrgid(gid);
  printf("user=%s(%d) grp=%s(%d)\ngroups= ", pwuid->pw_name, uid, grp->gr_name, gid);
  for(int i=0; i< grpNr;i++) {
    grp = getgrgid(groups[i]);
    printf("%s(%d) ", grp->gr_name, grp->gr_gid);
  }
  putchar('\n');
  free(groups);
  return 0;
}

int main()
{
//  for(int i=0; i<100000; i++) id();
  return id();
}
