#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf env;

void sigfunc(int sig){
  if(sig==SIGABRT)
    printf("Demonstration von SIGABRT ausgeloest mit abort()\n");
  longjmp(env, 1);
}

int main(){
  signal(SIGABRT,sigfunc);
  if(setjmp(env) == 0) {
    abort();
  }
}
