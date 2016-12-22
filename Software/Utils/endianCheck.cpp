#include <stdio.h>
#include <string.h>

int main(){
  int i;
  unsigned int ce=1;
  size_t cs=sizeof(ce);
  unsigned char *et = new unsigned char[cs];
  memcpy(et, &ce, cs); // copy the first byte to et.
  printf("Object size: %i\n",cs);
  printf("Byte pattern:\n ");
  for (i=0;i<cs;i++) printf(" 0x%02x",et[i]);
  printf("\n");
  delete et;
  return 0;
}
