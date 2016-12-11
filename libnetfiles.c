/*************Client Program 


4 functions 

1: open connection (Socket connection) - Opens file on the remote machine
2: netOpen netClose netRead netWrite (Messaging prtocol implemeted to send/receive msgs to/from the fileserver)

3: netserverinit(char * hostname) 
netserverinit(char * hostname, int filemode) (for ext. A only) This initializes your connection with the given hostname


{main code 
1: Initialize connection (call init)
2: Open connecion
3: read something
4: write something
5: close connection

} *******************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "libnetfiles.h"

#define PORT_NO 16080

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int sockfd = -1;
struct sockaddr_in serverAddressInfo;

/*** netOpen: netopen(const char *pathname, int flags)
	The argument flags must include one of the following access modes: O_RDONLY,
	O_WRONLY, or O_RDWR. These request opening the file read-only, write-only, or
	read/write, respectively.
RETURN VALUE:
			netopen() returns the new file descriptor, or -1 if an error occurred (in which case, errno is set
			appropriately).
ERRORS:
	EACCES
	EINTR
	EISDIR
	ENOENT
	EROFS***/

int netopen(const char * pathname, int flags){
	
	errno = 0;
	int fileDescriptor = open(pathname, flags);

	if (fileDescriptor > -1){
		
		return fileDescriptor;

	} else {
		//Opening file failed, set errno and return -1
		perror("Error opening file");
		return -1;

	}
}

/*** netRead: ssize_t netread(int fildes, void *buf, size_t nbyte)
RETURN VALUE: a non-negative integer indicating the number of bytes actually read. 
			  Otherwise, the function should return -1 and set errno to
			  indicate the error.
ERRORS:
	ETIMEDOUT
	EBADF
	ECONNRESET***/

ssize_t netread(int fileDesc, void *buffer, size_t noOfByte) {
	
	errno = 0;
	ssize_t bytesRead = read(fileDesc, buffer, noOfByte);

	if (bytesRead > -1){
		
		return bytesRead;

	} else {
		//Reading of file failed, set errno and return -1
		perror("Error reading the file");
		return -1;	

	}
}

/*** netWrite: ssize_t netwrite(int fildes, const void *buf, size_t nbyte)
RETURN VALUE:
			the number of bytes actually written to the file associated with fildes. This number should never be greater than nbyte. 
			Otherwise, -1 should be returned and errno set to indicate the error.
ERRORS:
	EBADF
	ETIMEOUT
	ECONNRESET ***/

ssize_t netwrite(int fileDesc, const void *buffer, size_t noOfByte) {
	
	errno = 0;
	int bytesToWrite = write(fileDesc, buffer, noOfByte);

	if (bytesToWrite > -1){
	
		return bytesToWrite;

	} else {
		//Writing to file failed, set errno and return -1
		perror("Error writing to file");
		return -1;

	}
}

/*** netClose: int netclose(int fd)
RETURN VALUE: netclose() returns zero on success. On error, -1 is returned, and errno is set 		appropriately.
ERRORS:
	EBADF ***/

int netclose(int fileDesc) {
	
	errno = 0;
	int fpClose = close(fileDesc);

	if (fpClose == -1){
		//Closing of file failed, set errno and return -1
		perror("Error closing the file");
		return -1;

	} else {
		
		return 0;

	}
}

/*** netserverinit(char * hostname, int filemode) (for ext. A only)
RETURN: 0 on success, -1 on error and h_errnor set correctly
ERRORS:
	HOST_NOT_FOUND 
	optional (if you do extension A): INVALID_FILE_MODE (be sure to include #define of this error code in your .h if you implement it)
***/

netserverinit(char * hostName, int fileMode) {
	
	
	h_errno = 0;
	
	struct addrinfo hints, * infoptr;
	struct addrinfo * p;
	int connectVal;
	
	//Allocating memory by initializing with zero
	memset(&hints, 0, sizeof(hints));
	
	hints.ai_family = AF_INET; 		//IPv4 Address
	hints.ai_socktype = SOCK_STREAM;

	int result = getaddrinfo(hostName, NULL, &hints, &infoptr);

	if (result) {
		//connection failed
		h_errno = HOST_NOT_FOUND;
		freeaddrinfo(ptr); //free up the memory
		//return -1;
		exit(0);

	} else {
		//connection successful
		
		//Create socket
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		
		if(sockfd < 0) {
			//Building of socket failed
			error("Error creating a socket!");
			exit(0);
		}
		else {
			//Socket created successfully
			
			for (p = infoptr; p != NULL; p = p->ai_next) {
				
				struct sockaddr_in * sockptr;
				sockptr = (struct sockaddr_in *) (p -> ai_addr);
				
				sockptr -> sin_port = htons(PORT_NO);
				sockptr -> sin_family = AF_INET;
				
				//getnameinfo(p->ai_addr, p->ai_addrlen, host, sizeof(host), service, sizeof(service), NI_NUMERICHOST);
				
				connectVal = connect(sockfd, (struct sockaddr *) (p -> ai_addr), (struct sockaddr *) (p -> ai_addrlen));
				
				if(connectVal == 0) {
					//Connection successful
					break;
				}
				
				if(connectVal < 0) {
					//Connection failed
					error("ERROR connecting!");
				}
			}
			
			freeaddrinfo(ptr); //free up the memory
			return 0;
		}
	}	
}