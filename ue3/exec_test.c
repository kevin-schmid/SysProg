#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main (void) {
    pid_t pid;
    switch (pid = fork()) {
        case -1:
            printf("Fehler bei fork()\n");
            exit(EXIT_FAILURE);
        case 0:
            printf("...Kindprozess...\n");
            printf("[Kind] Die PID des Kindprozesses ist %d\n",getpid());
            printf("[Kind] Die PID des Elternprozesses ist %d\n", getppid());
            execl("/bin/date", "-u", NULL);
        default:
            sleep(1);
            printf("...Elternprozess...\n");
            printf("[Eltern] Die PID des Elternprozesses ist %d\n", getpid());
            printf("[Eltern] Die PID des Kindprozesses ist %d\n",pid);
            printf("[%d ]Programmende\n", getpid());
    }
    return EXIT_SUCCESS;
}
