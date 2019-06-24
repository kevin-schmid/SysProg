#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void main(void){
   pid_t pid1;
   while(1) {
      switch(pid1 = fork()) {
         case -1: printf("fehler\n"); exit(0);
         case 0: sleep(2);
            printf("Kind fertig\n");
            exit(1);
         default: printf("sleep\n");
            wait(NULL);
            sleep(30);
            printf("eltern fertig\n");
            exit(2);
      }
   }
   return 0;
}
