# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# define BUF_SIZE 1000

int main(int argc, char *argv[]){
int sock_fd, client_fd, port, err, length, stop;
struct sockaddr_in my_addr, client_addr;
socklen_t addr_size;
static char buffer[BUF_SIZE];

if ((argc != 2) || (strcmp(argv[1], "-h") == 0)){
fprintf(stderr, "Usage: udp-server port\n");
return(1);
}

if (sscanf(argv[1], "%d", &port) != 1){
fprintf(stderr, "udp-server: Bad port number %s.\n",
argv[1]);
return(1);
}

/*--- Socket öffnen ---*/
sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
if (sock_fd == -1)
{
perror("udp-server: Can not create new socket");
return(1);
}

/*--- Socket an Port binden ---*/
my_addr.sin_family = AF_INET;
my_addr.sin_port = htons(port);
my_addr.sin_addr.s_addr = INADDR_ANY;
err = bind(sock_fd, (struct sockaddr *)&my_addr,
sizeof(struct sockaddr_in));
if (err == -1)
{
perror("udp-server: bind() failed");
return(1);
}

stop = 0;
while (!stop){ 
/*--- Paket empfangen ---*/
addr_size = sizeof(struct sockaddr_in);
length = recvfrom(sock_fd, buffer, BUF_SIZE-1, 0,
(struct sockaddr *)&client_addr,
&addr_size);
if (length == -1)
perror("udp-server: recvfrom() failed");

/*--- Paket erstellen ---*/
else{ 
buffer[length] = '\0';
printf("Datagram from %s:\n%s\n",
inet_ntoa(client_addr.sin_addr), buffer);

if (strcmp(buffer, "quit") == 0){
strcpy(buffer, "Server stopped.");
stop = 1;
}

else
strcpy(buffer, "Message received.");

/*--- Antwort senden ---*/
length = sendto(sock_fd, buffer, strlen(buffer), 0,
(struct sockaddr *)&client_addr,
sizeof(struct sockaddr));
if (length < strlen(buffer))
perror("udp-server: sendto() failed");
}
}
close(client_fd);
close(sock_fd);
return(0);
}







