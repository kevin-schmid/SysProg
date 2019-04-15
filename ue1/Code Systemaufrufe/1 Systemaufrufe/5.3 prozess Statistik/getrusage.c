#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

void main (void){
struct rusage usage;
getrusage (RUSAGE_SELF, &usage);

// Code ergänzen 
}




