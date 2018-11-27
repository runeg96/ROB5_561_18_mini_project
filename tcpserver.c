#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <netdb.h>

#define SERV_TCP_PORT  50000

#define MAX_LENGTH 2000

int sockfd;

void slut () {
								close(sockfd); exit(1);
}

int main(int argc, char *argv[]) {
								// Initializing all variables
								int newsockfd;
								struct sockaddr_in serv_addr, cli_addr;
								int n, cli_size, childpid;
								char string[MAX_LENGTH];
								char even;
								int temp1=0, temp2=0;
								int temp = 0;
								cli_size = sizeof(cli_addr);

								// Creating the socket
								if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
																printf("server: can't open stream socket");
																exit(0);
								}

								serv_addr.sin_family = AF_INET;
								serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
								serv_addr.sin_port = htons(SERV_TCP_PORT);

								// Binding the port specified
								signal (SIGINT, slut);
								if (bind(sockfd, (struct sockaddr *) &serv_addr,
																	sizeof(serv_addr)) < 0) {
																printf("server: can't bind local port\n");
																exit(0);
								}

								// listen(sockfd, 5);

								while (1) {
																// Listening for any communication on the port
																listen(sockfd, 5);
																// accepting and saving the connection
																newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,
																																			&cli_size);
																// creating a new thread to manage the connection
																if (!(childpid = fork())) {
																								close(sockfd);
																								// read what is comming from the IP address
																								n = read(newsockfd, string, MAX_LENGTH);


																								// checking if the number from the IP address is even
																								temp2 = *string;

																								if (temp2%2!=0) {
																																even=0;
																								} else {
																																even=1;
																								}
																								printf("CarrierID: %d\n", *string);
																								printf("Even: %d\n", even);
																								// Sending the value of even to the IP address
																								write(newsockfd, (void*)&even, sizeof(even));

																								// terminating the thread
																								exit(0);
																}
																close(newsockfd);

								}

}
