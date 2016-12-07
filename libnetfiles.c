/*************Client Program 

//16080
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

/*** netOpen: 
INPUT: 
OUTPUT:

ERRORS (check open manpage for definition)
reqiured:
EACCES
EINTR
EISDIR
ENOENT
EROFS***/
#include "libnetfiles.h"
int netopen(const char * file, int flags){
	
	errno = 0;
	int fileDescriptor = open(file, flags);

	if (fileDescriptor > -1){
		
		return fileDescriptor;

	} else {
		//fails, set errno and return -1
		perror("netopen failed:");
		return -1;

	}
}

/*** ssize_t netread(int fildes, void *buf, size_t nbyte)
RETURN VALUE: a non-negative integer indicating the number of bytes actually read. 
			  Otherwise, the function should return -1 and set errno to
			  indicate the error.
ERRORS:
required:
ETIMEDOUT
EBADF
ECONNRESET***/

ssize_t netread(int fildes, void *buf, size_t nbyte) {
	
	
	
}

/***ssize_t netwrite(int fildes, const void *buf, size_t nbyte)
RETURN VALUE:
			the number of bytes actually written to the file associated with fildes. This number should never be greater than nbyte. 
			Otherwise, -1 should be returned and errno set to indicate the error.
ERRORS:
EBADF
ETIMEOUT
ECONNRESET ***/

ssize_t netwrite(int fildes, const void *buf, size_t nbyte) {
	
}

/*** int netclose(int fd)
RETURN VALUE: netclose() returns zero on success. On error, -1 is returned, and errno is set 		   	appropriately.
ERRORS
EBADF ***/

int netclose(int fd) {
	
	
}
