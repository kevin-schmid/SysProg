# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/poll.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# define BUF_SIZE 1000
# define TIMEOUT 1000 

int main(int argc, char *argv[]){
int sock_fd, port, length, err;
struct sockaddr_in server_addr, from_addr;
socklen_t addr_size;

struct pollfd pollfd;
static char buffer[BUF_SIZE];

if (argc != 4){
fprintf(stderr,
"Usage: udp-client ip-addr port message\n");
return(1);
}

if (sscanf(argv[2], "%d", &port) != 1){
fprintf(stderr, "udp-client: bad port number %s\n",
argv[2]);
return(1);
}

/*--- Socket öffnen ---*/
sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
if (sock_fd == -1){
perror("udp-client: Can not create new socket");
return(1);
}

/*--- Serveradresse festlegen ---*/
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(port);
err = inet_aton(argv[1], &(server_addr.sin_addr));
if (err == 0){
fprintf(stderr, "udp-client: Bad IP-Address %s\n",
argv[1]);
return(1);
}

/*--- Nachricht senden ---*/
length = sendto(sock_fd, argv[3], strlen(argv[3]), 0,
(struct sockaddr *)&server_addr,
sizeof(struct sockaddr));
if (length != strlen(argv[3]))
perror("udp-client: sendto() failed");

/*--- auf Antwort warten ---*/
pollfd.fd = sock_fd; /* Was passiert hier? */
pollfd.events = POLLIN | POLLPRI;
 err = poll(&pollfd, 1, TIMEOUT);
if (err < 0)
perror("udp-client: poll() failed");
else if (err == 0)
printf("<No answer received.>\n");

else{
addr_size = sizeof(struct sockaddr_in);
length = recvfrom(sock_fd, buffer, BUF_SIZE-1, 0,(struct sockaddr *)&from_addr,
&addr_size);

if (length == -1)
perror("udp-client: recvfrom() failed");
else{
buffer[length] = '\0';
printf("Response from %s: %s\n",
inet_ntoa(from_addr.sin_addr), buffer);
 }
}
close(sock_fd);
return(0);
}





