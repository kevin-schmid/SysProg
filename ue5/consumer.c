#include "share.h"

static void delete (void) {
   int res;
   printf ("\nconsumer stopped and semaphor deleted %d.\n",
            DeleteSemid);
   if (semctl (DeleteSemid, 0, IPC_RMID, 0) == -1) {
      printf ("error deleting semaphor\n");
   }

   /* Wenn Serverprozess beendet wird - */
   /* Segment automatisch löschen       */
   res = shmctl (DeleteShmid, IPC_RMID, NULL);
   if (res == -1)
      printf ("error with shmctl() shmid %d, Kommando %d\n",
          DeleteShmid, IPC_RMID);   
   return;
}

static void sigdelete (int signum) {
   exit(EXIT_FAILURE);
}

static void consume (void) {
   union semun sunion;
   int semid, shmid;
   int res;
   void *shmdata;
   char *buffer;

   /* Ein Semaphor erstellen */
   semid = safesemget (IPC_PRIVATE, 2, SHM_R | SHM_W);
   DeleteSemid = semid;

   /* Semaphor beim Beenden entfernen */
   atexit (&delete);

   /* Signalhandler einrichten */
   my_signal (SIGINT, &sigdelete);

   /* Semaphor initialisieren */
   sunion.val = 1;
   safesemctl (semid, SN_EMPTY, SETVAL, sunion);
   sunion.val = 0;
   safesemctl (semid, SN_FULL, SETVAL, sunion);

   /* Ein Shared-Memory-Segment einrichten */
   shmid = shmget (IPC_PRIVATE, SHMDATASIZE,
             IPC_CREAT | SHM_R | SHM_W);
   if (shmid == -1)
      printf ("error with key %d, with size %d\n",
               IPC_PRIVATE, SHMDATASIZE);
               
    DeleteShmid = shmid;

   /* Shared-Memory-Segment anbinden */
   shmdata = shmat (shmid, NULL, 0);
   if (shmdata == (void *) -1)
      printf ("error with shmat(): shmid %d\n", shmid);

   /* Kennung am Anfang des Segments schreiben */
   *(int *) shmdata = semid;
   buffer = shmdata + sizeof (int);
   printf ("consumer is using shared-memory-ID %d\n", shmid);
   while (1) {
      printf ("waiting ...");
      fflush (stdout);

      /* Sperren und Warten */
      locksem (semid, SN_FULL);
      printf ("\n... done.\n");

      /* Ein Client hat etwas geschrieben */
      printf ("message received: %s\n", buffer);

      /* Sperre aufheben */
      unlocksem (semid, SN_EMPTY);
   }
   return;
}
int main (int argc, char **argv) {
   consume ();
   printf("--- consumer stopped ---\n");
   return EXIT_SUCCESS;
}

