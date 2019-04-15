#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigfunc(int sig){
 char c;

if(sig != SIGINT)
   return;
 else{
    printf("\nWollen sie das Programm beenden (j/n) : ");
    while((c=getchar()) == 'j')
    exit (0);
   }
}

void main(void){
int i;

signal(SIGINT, sigfunc);

 while(1){
   printf("Die Endlosschleife koennen sie mit STRG-C beenden");
   for(i=0;i<=48;i++)
       printf("\b");
   }
}
