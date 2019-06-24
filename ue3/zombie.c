#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  pid_t kind1;
  while(1) {
    switch ( kind1 = fork() ) {
      case -1 :
        printf("Fehler bei fork()..........\n");  
		    exit(0);
      case  0 :   // Code von Kindprozess
        sleep(5);
        exit(1);
      default :   // Code von Elternprozess
        sleep(30);
        exit(2);
    }
  }
  return 0;
}
