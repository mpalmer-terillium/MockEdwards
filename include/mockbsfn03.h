#ifndef MOCKBSFN03
#define MOCKBSFN03

#include "../include/mockedwards.h"
#include "../include/mockcontext.h"

#define INPUT_TOKEN_START_DSBSFN03      "<message>"
#define INPUT_TOKEN_END_DSBSFN03        "</message>"
#define OUTPUT_TOKEN_START_DSBSFN03     "<response>"
#define OUTPUT_TOKEN_END_DSBSFN03       "</response>"

struct DSBSFN03 {

    char szInput[101];
    char szOutput[1001];
    char szErrorMsg[101];

};

int mockbsfn03_callBSFN(struct mockcontext *, struct DSBSFN03 *);
int mockbsfn03_createSoapEnv(struct DSBSFN03 *, char *);
int mockbsfn03_parseXmlResponse(char *, char *, char *, struct DSBSFN03 *);

#endif