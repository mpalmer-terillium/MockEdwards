#ifndef MOCKBSFN01
#define MOCKBSFN01

#include "../include/mockedwards.h"
#include "../include/mockcontext.h"

#include <stdio.h>
#include <string.h>


struct DSBSFN01 {

    char szInput[101];
    char szOutput[1001];
    char szErrorMsg[101];

};

int mockbsfn01_callBSFN(struct mockcontext *, struct DSBSFN01 *);
int mockbsfn01_createSoapEnv(struct mockcontext *, struct DSBSFN01 *, char *);
int mockbsfn01_parseXmlGetOutput(char *, char *, struct DSBSFN01 *);

#endif
