#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void trap();

void main(void){
    int* a = NULL;
    signal(SIGSEGV, &trap);
    *a = 5;
}

void trap() {
    printf("bla");
    exit(1);
}