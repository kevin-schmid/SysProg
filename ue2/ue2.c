#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

static int global_var = 1;

int main (void) {
	pid_t pid_child;
	pid_t pid_grandchild;
	int lokal_var = 1;
	int is_grandchild = 0;
	switch (pid_child = fork ()) {

	case -1:
		printf ("Fehler bei fork()\n");
		fflush(stdout);
		break;

	case 0:
		switch(pid_grandchild = fork()) {
			case -1:
				printf ("Fehler bei fork()\n");
				fflush(stdout);
				break;
			case 0:
				sleep(2);
				printf ("--- Im Enkelkindprozess ---\n");
				printf ("global_var = %d Speicheradresse : %p\n", global_var, &global_var);
				printf ("lokal_var  = %d Speicheradresse : %p\n", lokal_var, &lokal_var);
				fflush(stdout);

				global_var += 2;
				lokal_var += 2;

				printf ("--- Im Enkelkindprozess ---\n");
				printf ("global_var = %d Speicheradresse : %p\n", global_var, &global_var);
				printf ("lokal_var  = %d Speicheradresse : %p\n", lokal_var, &lokal_var);
				fflush(stdout);

				is_grandchild = 1;
				break;
		}
		if(!is_grandchild) {
			sleep(1);
			printf ("--- Im Kindprozess ---\n");
			printf ("global_var = %d Speicheradresse : %p\n", global_var, &global_var);
			printf ("lokal_var  = %d Speicheradresse : %p\n", lokal_var, &lokal_var);
			fflush(stdout);

			++global_var;
			++lokal_var;
			sleep(2);

			printf ("--- Im Kindprozess ---\n");
			printf ("global_var = %d Speicheradresse : %p\n", global_var, &global_var);
			printf ("lokal_var  = %d Speicheradresse : %p\n", lokal_var, &lokal_var);
			fflush(stdout);
		}
		break;

	default:
		printf ("--- Im Elternprozess ---\n");
		printf ("global_var = %d Speicheradresse : %p\n", global_var, &global_var);
		printf ("lokal_var  = %d Speicheradresse : %p\n", lokal_var, &lokal_var);
		fflush(stdout);

		sleep (4);

		printf ("--- Im Elternprozess ---\n");
		printf ("global_var = %d Speicheradresse : %p\n", global_var, &global_var);
		printf ("lokal_var  = %d Speicheradresse : %p\n", lokal_var, &lokal_var);
		fflush(stdout);
		break;
	}
	return EXIT_SUCCESS;
}
