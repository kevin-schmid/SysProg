#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv){
    printf("--beginning of program\n");

    int counter = 0;
    pid_t pid = fork();

    if (pid > 0){
        // parent process
        counter = counter + 10;
        printf("Parent PPID:%d PID:%d counter:%d \n", getppid(), getpid(), counter);
    }
    else if (pid == 0){
        counter = counter + 1;
        printf("Child: PPID:%d PID:%d counter:%d \n", getppid(), getpid(), counter);
        // child process
    } else{
        printf("fork() failed!\n");
        return 1;
    }

    printf("--end of program--\n");
    return 0;
}


