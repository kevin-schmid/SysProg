#include <unistd.h>
#include <stdio.h>

void main(void){
 for(int i = 0; i < 14; ++i)
  if(!fork())
   printf ("ab geht´s");
 return 1; //never reached
}
