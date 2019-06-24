#include "share.h"

static void produce (int shmid, int semid, char *buffer) {
   printf ("waiting ...");
   fflush (stdout);

   /* Sperre setzen - Client will schreiben */
   locksem (semid, SN_EMPTY);
   printf ("\n... CS locked\n");
   printf ("consumer input: ");
   fgets (buffer, BUFFERSIZE, stdin);
   unlocksem (semid, SN_FULL);
   return;
}

static void client (int shmid) {
   int semid;
   void *shmdata;
   char *buffer;

   /* Shared-Memory-Verbindung zu Server */
   shmdata = shmat (shmid, NULL, 0);

   if (shmdata == (void *) -1) {
      printf ("shmat() doesn't work: shmid %d\n", shmid);
      return;
   }

   /* Holt die Shared-Memory ID */
   semid = *(int *) shmdata;
   buffer = shmdata + sizeof (int);
   printf("producer: shared-memory-ID: %d, semaphor-ID: %d\n",
            shmid, semid);


   while (1) {
      char input[3];
      printf ("\n\nmenu\n1. send data\n");
      printf ("2. exit producer\n");
      fgets (input, sizeof (input), stdin);
      switch (input[0]) {
      case '1':
         produce (shmid, semid, buffer);
         break;
      case '2':
         exit (EXIT_FAILURE);
         break;
      }
   }
   return;
}

int main (int argc, char **argv) {
   if (argc < 2) {
      printf ("call: %s shared-memory-ID\n", *argv);
   }
   else {
      client (atoi (argv[1]));
   }
   return EXIT_SUCCESS;
}
