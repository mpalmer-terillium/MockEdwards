#ifndef MOCKBSFN02
#define MOCKBSFN02

#include "../include/mockedwards.h"
#include "../include/mockcontext.h"

#include <stdio.h>
#include <string.h>


struct DSBSFN02 {

    char szInput[101];
    char szOutput[1001];
    char szErrorMsg[101];

};

int mockbsfn02_callBSFN(struct mockcontext *, struct DSBSFN02 *);
int mockbsfn02_createSoapEnv(struct mockcontext *, struct DSBSFN02 *, char *);
int mockbsfn02_parseXmlGetOutput(char *, char *, struct DSBSFN02 *);

#endif
