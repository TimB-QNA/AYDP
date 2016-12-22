// Print a few data sizes

#include <stdio.h>
#include <sys/time.h>

int main(){
  struct timeval tv;
  printf("Useful data sizes:\n");
  printf("  timeval              %i bytes\n",sizeof(tv));
  printf("    timeval.tv_secs    %i bytes\n",sizeof(tv.tv_sec));
  printf("    timeval.tv_usecs   %i bytes\n",sizeof(tv.tv_usec));
  return 0;
}
