#include "../include/mockbsfn01.h"
#include "../include/mockedwards.h"


int mockbsfn01_callBSFN(struct DSBSFN01 *lpDS)
{
    char soapEnv[MAXLINE];
    char response[MAXLINE];
    int status = INIT;

    if(createSoapEnv(lpDS->szInput, soapEnv) == SUCCESS) {
        if(callExternalService(soapEnv, response) == SUCCESS) {
            status = parseXmlGetOutput((char *) "output_token", response, lpDS->szOutput);
        } else {
            snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG);
            status = FAIL;
        }
    }
    return status;
}
