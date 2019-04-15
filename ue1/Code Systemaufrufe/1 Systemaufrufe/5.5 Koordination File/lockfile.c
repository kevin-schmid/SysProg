#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main (int argc, char* argv[]){
char* file = argv[1];
int fd;
struct flock lock;
printf ("opening %s\n", file);

/* opening a file in write only */
fd = open (file, O_WRONLY);
printf ("locking\n");

/* fill lock with 0, set lock type exclusive */
memset (&lock, 0, sizeof(lock));
lock.l_type = F_WRLCK;

/* record lock with wait is set */
fcntl (fd, F_SETLKW, &lock);
printf ("locked; hit Enter to unlock... ");

/* wait for input */
getchar ();
printf ("unlocking\n");

/* set lock type to unlock, record unlock, close file*/
lock.l_type = F_UNLCK;
fcntl (fd, F_SETLKW, &lock);
close (fd);
return 0;
}
