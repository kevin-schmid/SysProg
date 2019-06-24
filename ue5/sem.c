/* TODO: Kommentare als Dokumentation ergänzen */
/* Bei markierten Abschnitten oder wo immer es passt */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define LOCK       -1
#define UNLOCK      1
#define PERM 0666      /* Zugriffsrechte definieren */
#define KEY  1
  
static struct sembuf semaphore;
static int semid;

static int init_semaphore (void) {

   /* todo: */
   semid = semget (KEY, 0, IPC_PRIVATE);

   if (semid < 0) {
      umask(0);

   /* todo: */
      semid = semget (KEY, 1, IPC_CREAT | IPC_EXCL | PERM);
      if (semid < 0) {
         printf ("error creating semaphor ...\n");
         return -1;
      }

      printf ("Semaphor-ID : %d\n", semid);

      /* todo: */
      if (semctl (semid, 0, SETVAL, (int) 1) == -1)
         return -1;
   }
   return 1;
}

static int semaphore_operation (int op) {
   semaphore.sem_op = op;
   semaphore.sem_flg = SEM_UNDO;
   if( semop (semid, &semaphore, 1) == -1) {
      perror(" semop ");
      exit (EXIT_FAILURE);
   }
   return 1;

}

/* todo: */
int main (void) {
   int res;
   res = init_semaphore ();

   if (res < 0)
      return EXIT_FAILURE;


   printf ("entering CS ...\n");
   semaphore_operation ( LOCK );

   
   printf ("PID %d verwendet Semaphor %d\n",
      getpid(), semid);

   printf ("in CS ...\n");
   sleep (10);
   semaphore_operation ( UNLOCK );

   printf ("after CS ...\n");

    /* todo: */
   // semctl (semid, 0, IPC_RMID, 0);
   return EXIT_SUCCESS;
}
