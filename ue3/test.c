#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void main(void){
  if(fork()) {
    if(fork()) {
      printf("Parent A of all: %d\n", getpid());
    } else {
      if(fork()) {
        printf("Child B with id: %d and it's Parent id: %d\n", getpid(), getppid());
      } else {
        printf("Child D with id: %d and it's Parent id: %d\n", getpid(), getppid());
      }
    }
  } else {
    if(fork()) {
      printf("Child C with id: %d and it's Parent id: %d\n", getpid(), getppid());
    } else {
      printf("Child E with id: %d and it's Parent id: %d\n", getpid(), getppid());
    }
  }
  exit(EXIT_SUCCESS);
}
