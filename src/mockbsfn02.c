#include "../include/mockbsfn02.h"
#include "../include/mockedwards.h"


int mockbsfn02_callBSFN(struct mockcontext *ctx, struct DSBSFN02 *lpDS)
{
    char header[MAXLINE], soapEnv[MAXLINE], response[MAXLINE];
    int status = INIT;

    status = mockbsfn02_createSoapEnv(lpDS, soapEnv);
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_SOAP_ENV);

    status = createRequestHeader(ctx, header, strlen(soapEnv));
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_REQ_HEAD);

    status = callExternalService(ctx, soapEnv, response, header);
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_CALL_EXT);

    status = mockbsfn02_parseXmlResponse((char *) OUTPUT_TOKEN_START_DSBSFN02, (char *) OUTPUT_TOKEN_END_DSBSFN02, response, lpDS);
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_PRS_RESP);

    return status;
}

int mockbsfn02_createSoapEnv(struct DSBSFN02 *lpDS, char * soapEnv) {

    char s0[]  = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n";
    char s1[]  = "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:ser=\"http://service.optyservice.osc.com/\">\r\n";
    char s2[]  = "<soapenv:Header/>\r\n";
    char s3[]  = "<soapenv:Body>\r\n";
    char s4[]  = "<ser:processOSCIntegrationRequest>\r\n";
    char s5[]  = "<request>\r\n";
    char s6[100];
    snprintf(s6, sizeof(s6), "%s%s%s", "<optyName>", lpDS->szInput, "</optyName>\r\n");
    char s7[]  = "<transactionType>READ</transactionType>\r\n";
    char s8[] = "</request>\r\n";
    char s9[] = "</ser:processOSCIntegrationRequest>\r\n";
    char s10[] = "</soapenv:Body>\n";
    char s11[] = "</soapenv:Envelope>\n";

    soapEnv[0] = '\0';
    strcat(soapEnv, s0);
    strcat(soapEnv, s1);
    strcat(soapEnv, s2);
    strcat(soapEnv, s3);
    strcat(soapEnv, s4);
    strcat(soapEnv, s5);
    strcat(soapEnv, s6);
    strcat(soapEnv, s7);
    strcat(soapEnv, s8);
    strcat(soapEnv, s9);
    strcat(soapEnv, s10);
    strcat(soapEnv, s11);

    return SUCCESS;
}

int mockbsfn02_parseXmlResponse(char *start_token, char *end_token, char *response, struct DSBSFN02 *lpDS) {

    char *respValue = strstr(response, start_token);
    char *respEnd = strstr(response, end_token);
    char *start = respValue + strlen(start_token);
    int len = respEnd - start;

    if(len > 0) {
        strncpy(lpDS->szOutput, start, len);
        return SUCCESS;
    } else {
        return FAIL;
    }
}
