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
#include <assert.h>
#include "../include/mockbsfn01.h"
#include "../include/mockcontext.h"

#define INIT                    0
#define SUCCESS                 100
#define FAIL                    -100
#define MAXLINE                 1024
#define ERROR_MSG_GEN           "Something went wrong"
#define ERROR_MSG_SOAP_ENV      "Error creating soapEnv"
#define ERROR_MSG_REQ_HEAD      "Error creating request header"
#define ERROR_MSG_CALL_EXT      "Error calling external service"
#define ERROR_MSG_PRS_RESP      "Error parsing response"
#define ERROR_MSG_OP_SCKET      "Error opening socket"
#define ERROR_MSG_CON_SCKT      "Error connecting to socket"
#define ERROR_MSG_WRT_HEDR      "Error writing header to socket"
#define ERROR_MSG_WRT_ENVL      "Error writing soapEnv to socket"
#define ERROR_MSG_READ_ENV      "Error reading from socket"

#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

#define debug_print(fmt, ...) \
            do { if(DEBUG_TEST) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

void error(const char *, int *);
int callExternalService(struct mockcontext *, char *, char *, char *);
struct mockcontext *get_context(const char *, int, const char *, const char *);
int createRequestHeader(struct mockcontext *, char *, int);

#endif
