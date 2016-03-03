#ifndef MOCKBSFN02
#define MOCKBSFN02

#include "../include/mockedwards.h"
#include "../include/mockcontext.h"

#define INPUT_TOKEN_START_DSBSFN02      "<optyName>"
#define INPUT_TOKEN_END_DSBSFN02        "</optyName>"
#define OUTPUT_TOKEN_START_DSBSFN02     "<response>"
#define OUTPUT_TOKEN_END_DSBSFN02       "</response>"

struct DSBSFN02 {

    char szInput[101];
    char szOutput[1001];
    char szErrorMsg[101];

};

int mockbsfn02_callBSFN(struct mockcontext *, struct DSBSFN02 *);
int mockbsfn02_createSoapEnv(struct DSBSFN02 *, char *);
int mockbsfn02_parseXmlResponse(char *, char *, char *, struct DSBSFN02 *);

#endif