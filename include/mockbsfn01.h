#ifndef MOCKBSFN01
#define MOCKBSFN01

#include <stdio.h>
#include <string.h>


struct DSBSFN01 {

    char szInput[101];
    char szOutput[1001];
    char szErrorMsg[101];

};

int mockbsfn01_callBSFN(struct DSBSFN01 *);

#endif
