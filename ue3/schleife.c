#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv){
    printf("--beginning of program\n");

    int counter = 0;
    pid_t pid = fork();

    if (pid > 0){
        // parent process
    }
    else if (pid == 0){
        // child process
    } else{
        printf("fork() failed!\n");
        return 1;
    }

    printf("--end of program--\n");
    return 0;
}


