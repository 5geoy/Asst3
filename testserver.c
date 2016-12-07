/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
	if (argc < 2){
        	fprintf(stderr,"ERROR, no port provided\n");
        	exit(1);
    	}

	//STEP 1: socket()
	int portno = atoi(argv[1]);	// convert the text representation of the port number given by the user to an int  
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);	// try to build a socket .. if it doesn't work, complain and exit
    	if (sockfd < 0)
       		error("ERROR opening socket");
	
	//STEP 2: bind()
	struct sockaddr_in serverAddressInfo;
	bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));	// zero out the socket address info struct .. always initialize!
	serverAddressInfo.sin_port = htons(portno);	// set the remote port .. translate from a 'normal' int to a super-special 'network-port-int'  
    	serverAddressInfo.sin_family = AF_INET;	// set a flag to indicate the type of network address we'll be using
    	serverAddressInfo.sin_addr.s_addr = INADDR_ANY;	// set a flag to indicate the type of network address we'll be willing to accept connections from
    	int binderr = bind(sockfd, (struct sockaddr *) &serverAddressInfo, sizeof(serverAddressInfo));	// bind the server socket to a specific local port, so the client has a target to connect to   
    	if (binderr < 0)
		error("ERROR on binding");

	//STEP 3: listen()
    	int listenerr = listen(sockfd, 5);	// set up the server socket to listen for client connections
	if (listenerr < 0)
		error("ERROR on listening");

	//STEP 4: accept()
	struct sockaddr_in clientAddressInfo;
    	int clilen = sizeof(clientAddressInfo);	// determine the size of a clientAddressInfo struct
    	int newsockfd = accept(sockfd, (struct sockaddr *) &clientAddressInfo, &clilen);	// block until a client connects, when it does, create a client socket
    	if (newsockfd < 0) 
        	error("ERROR on accept");

	char buffer[256];
    	bzero(buffer,256);	// zero out the char buffer to receive a client message
    	int n = read(newsockfd, buffer, 255);	// try to read from the client socket
    	if (n < 0)
		error("ERROR reading from socket");
    	printf("Here is the message: %s\n",buffer);
	n = write(newsockfd,"I got your message",18);	// try to write to the client socket
    	if (n < 0)
		error("ERROR writing to socket");

	return 0; 
}