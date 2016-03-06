#ifndef MOCKBSFN03
#define MOCKBSFN03

#include "../include/mockedwards.h"
#include "../include/mockcontext.h"

#define BSFN03_NAME             "BSFN03"

#define MESSAGE_DSBSFN03        "<message>"
#define MESSAGE_END_DSBSFN03    "</message>"
#define TYPE_DSBSFN03           "<messageType>"
#define TYPE_END_DSBSFN03       "</messageType>"
#define RESPONSE_DSBSFN03       "<response>"
#define RESPONSE_END_DSBSFN03   "</response>"

struct DSBSFN03 {

    char szMessage[101];
    char szType[101];
    char szResponse[1001];
    char szErrorMsg[101];

};

int mockbsfn03_callBSFN(struct mockcontext *, struct DSBSFN03 *);
int mockbsfn03_createSoapEnv(struct DSBSFN03 *, char *);
int mockbsfn03_parseXmlResponse(char *, char *, char *, struct DSBSFN03 *);
void mockbsfn03_logger_message(struct DSBSFN03 *lpDS, int status);

#endif