#include "../include/mockbsfn03.h"
#include "../include/mockedwards.h"


int mockbsfn03_callBSFN(struct mockcontext *ctx, struct DSBSFN03 *lpDS) {

    char header[MAXLINE], soapEnv[MAXLINE], response[MAXLINE];
    int status = INIT;

    status = mockbsfn03_createSoapEnv(lpDS, soapEnv);
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_SOAP_ENV);

    status = createRequestHeader(ctx, header, strlen(soapEnv));
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_REQ_HEAD);

    status = callExternalService(ctx, soapEnv, response, header);
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_CALL_EXT);

    status = mockbsfn03_parseXmlResponse((char *) OUTPUT_TOKEN_START_DSBSFN03, (char *) OUTPUT_TOKEN_END_DSBSFN03, response, lpDS);
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_PRS_RESP);

    debug_print("%s\n", response);

    return status;
}

int mockbsfn03_createSoapEnv(struct DSBSFN03 *lpDS, char * soapEnv) {

    char line_end[] = "\r\n";

    int size_s6 = strlen(INPUT_TOKEN_START_DSBSFN03) + strlen(lpDS->szInput) +
                  strlen(INPUT_TOKEN_END_DSBSFN03) + strlen(line_end);

//    char s0[]  = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n";
    char s1[]  = "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:ser=\"http://service.mockqueue.com/\">\r\n";
    char s2[]  = "<soapenv:Header/>\r\n";
    char s3[]  = "<soapenv:Body>\r\n";
    char s4[]  = "<ser:addNewMessage>\r\n";
    char s5[size_s6 + 1];
    snprintf(s5, sizeof(s5), "%s%s%s%s", INPUT_TOKEN_START_DSBSFN03, lpDS->szInput, INPUT_TOKEN_END_DSBSFN03, line_end);
    char s6[] = "</ser:addNewMessage>\r\n";
    char s7[] = "</soapenv:Body>\n";
    char s8[] = "</soapenv:Envelope>\n";

    soapEnv[0] = '\0';
//    strcat(soapEnv, s0);
    strcat(soapEnv, s1);
    strcat(soapEnv, s2);
    strcat(soapEnv, s3);
    strcat(soapEnv, s4);
    strcat(soapEnv, s5);
    strcat(soapEnv, s6);
    strcat(soapEnv, s7);
    strcat(soapEnv, s8);

    return SUCCESS;
}

int mockbsfn03_parseXmlResponse(char *start_token, char *end_token, char *response, struct DSBSFN03 *lpDS) {

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
