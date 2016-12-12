#ifndef LIBNETFILES_H_
#define LIBNETFILES_H_
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <netdb.h>
int netopen(const char *pathname, int flags);
ssize_t netread(int fildes, void *buf, size_t nbyte);
ssize_t netwrite(int fildes, const void *buf, size_t nbyte);
int netclose(int fd);
netserverinit(char * hostname, int filemode);

#endif