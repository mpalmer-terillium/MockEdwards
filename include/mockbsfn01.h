#ifndef MOCKBSFN01
#define MOCKBSFN01

#include "../include/mockedwards.h"
#include "../include/mockcontext.h"

#define OUTPUT_TOKEN_START_DSBSFN01     "<appmsg>"
#define OUTPUT_TOKEN_END_DSBSFN01       "</appmsg>"
#define INPUT_TOKEN_START_DSBSFN01      "<amount>"
#define INPUT_TOKEN_END_DSBSFN01        "</amount>"

struct DSBSFN01 {

    char szInput[101];
    char szOutput[1001];
    char szErrorMsg[101];

};

int mockbsfn01_callBSFN(struct mockcontext *, struct DSBSFN01 *);
int mockbsfn01_createSoapEnv(struct DSBSFN01 *, char *);
int mockbsfn01_parseXmlResponse(char *, char *, char *, struct DSBSFN01 *);

#endif
