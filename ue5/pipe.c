#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void main(){
	int fd[2], l;
	char buffer[80];

	// Erzeugung der Pipe. Die Datei-Deskriptoren werden in fd geschrieben
	// 0 = Lesekanal
	// 1 = Schreibkanal
	if (pipe(fd) != 0){
		perror("pipe: pipe() failed");
		return(1);
	}

	// Kind-Prozess wird erzeugt
	if (fork() == 0){
		// Schreibkanal schließen
		close(fd[1]);
		// Aus Datei-Deskriptor lesen
		if ((l = read(fd[0], buffer, 79)) == -1)
			perror("pipe: read() failed");
		else{
			buffer[l] = '\0';
			printf("String erhalten von : `%s`\n", buffer);
		}

		close(fd[0]);
		return(0);
	}

	close(fd[0]);
	write(fd[1], "SWD17!", 5);
	wait(NULL);
	close(fd[1]);
	
}



