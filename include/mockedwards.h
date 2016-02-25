#ifndef MOCKEDWARDS
#define MOCKEDWARDS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../include/mockbsfn01.h"
#include "../include/mockcontext.h"

#define INIT                0
#define SUCCESS             100
#define FAIL                -100
#define ERROR_MSG_GEN       "something went wrong"
#define ERROR_MSG_SOAP_ENV  "Error creating soapEnv"
#define ERROR_MSG_REQ_HEAD  "Error creating request header"
#define ERROR_MSG_CALL_EXT  "Error calling external service"
#define ERROR_MSG_PRS_RESP  "Error parsing response"
#define MAXLINE             1024


void error(const char *, int *);
int callExternalService(struct mockcontext *, char *, char *, char *);
struct mockcontext *get_context(const char *, int, const char *, const char *);
int createRequestHeader(struct mockcontext *, char *, int);

#endif
