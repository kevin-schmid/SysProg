#include <sys/types.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>


void main(void){
    unsigned int ID1, ID2;
    ID1 = syscall("hans");
    ID2 = getpid();

    printf("%d %d", ID1, ID2);
}
