#ifndef MOCKEDWARDS
#define MOCKEDWARDS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define INIT        0
#define SUCCESS     100
#define FAIL        -100
#define ERROR_MSG   "something went wrong"
#define MAXLINE     1024

void error(const char *);
int callExternalService(char * request, char * response);
int createRequestHeader(char * request, int contentLength);
int createSoapEnv(char * valueToInput, char * request);
int parseXmlGetOutput(char * token, char * response, char * lpDS_output);

#endif
