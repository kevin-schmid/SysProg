#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigfunc(int sig){
 if(sig != SIGFPE)
   return;
 else {
   printf("durch 0 tun wir nicht \n");
   abort();
 }
}

int main(){
 int wert1,wert2;

 signal(SIGFPE, sigfunc); // TODO: Floating Point Error konfigurieren
 signal(SIGINT, sigfunc); // TODO: STRG - C Signal ignorieren 

 printf("Programm zum Dividieren von Zahlen!\n");
 printf("Zahl eingeben : ");
 scanf("%d",&wert1);

 while(1){
   printf("geteilt durch > ");
   scanf("%d",&wert2);
   printf("Gesamt = %f\n",wert1/=wert2);
  }
}


