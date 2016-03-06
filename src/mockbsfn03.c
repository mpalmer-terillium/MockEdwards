#include "../include/mockbsfn03.h"
#include "../include/mockedwards.h"

int mockbsfn03_callBSFN(struct mockcontext *ctx, struct DSBSFN03 *lpDS) {

    char header[MAXLINE], soapEnv[MAXLINE], response[MAXLINE];

    if (mockbsfn03_createSoapEnv(lpDS, soapEnv) != SUCCESS) {
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_SOAP_ENV);
        return FAIL;
    }

    if (createRequestHeader(ctx, header, strlen(soapEnv)) != SUCCESS) {
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_REQ_HEAD);
        return FAIL;
    }

    if (callExternalService(ctx, soapEnv, response, header) != SUCCESS) {
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_CALL_EXT);
        return FAIL;
    }

    if (mockbsfn03_parseXmlResponse((char *) RESPONSE_DSBSFN03, (char *) RESPONSE_END_DSBSFN03, response, lpDS) != SUCCESS) {
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_PRS_RESP);
        return FAIL;
    }

    debug_print("RESPONSE\n%s\n", response);

    return SUCCESS;
}

int mockbsfn03_createSoapEnv(struct DSBSFN03 *lpDS, char * soapEnv) {

    char line_end[] = "\r\n";

    int size_s5 = strlen(MESSAGE_DSBSFN03) + strlen(lpDS->szMessage) +
            strlen(MESSAGE_END_DSBSFN03) + strlen(line_end);

    int size_s6 = strlen(TYPE_DSBSFN03) + strlen(lpDS->szType) +
            strlen(TYPE_END_DSBSFN03) + strlen(line_end);

    char s0[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n";
    char s1[] = "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:ser=\"http://service.mockqueue.com/\">\r\n";
    char s2[] = "<soapenv:Header/>\r\n";
    char s3[] = "<soapenv:Body>\r\n";
    char s4[] = "<ser:addNewMessage>\r\n";
    char s5[size_s5 + 1];
    snprintf(s5, sizeof (s5), "%s%s%s%s", MESSAGE_DSBSFN03, lpDS->szMessage, MESSAGE_END_DSBSFN03, line_end);
    char s6[size_s6 + 1];
    snprintf(s6, sizeof (s6), "%s%s%s%s", TYPE_DSBSFN03, lpDS->szType, TYPE_END_DSBSFN03, line_end);
    char s7[] = "</ser:addNewMessage>\r\n";
    char s8[] = "</soapenv:Body>\n";
    char s9[] = "</soapenv:Envelope>\n";

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

    return SUCCESS;
}

int mockbsfn03_parseXmlResponse(char *start_token, char *end_token, char *response, struct DSBSFN03 *lpDS) {

    char *respValue = strstr(response, start_token);
    char *respEnd = strstr(response, end_token);
    char *start = respValue + strlen(start_token);
    int len = respEnd - start;

    if (len > 0) {
        strncpy(lpDS->szResponse, start, len);
        return SUCCESS;
    } else {
        return FAIL;
    }
}

void mockbsfn03_logger_message(struct DSBSFN03 *lpDS, int status) {
    if (status == SUCCESS) {
        fprintf(stdout, "\nFunction: %s\nMessage: %s\nType: %s\nResponse: %s\n\n",
                BSFN03_NAME, lpDS->szMessage, lpDS->szType, lpDS->szResponse);
    } else {
        fprintf(stdout, "\nFunction: %s\nError: %s\n\n", BSFN03_NAME, lpDS->szErrorMsg);
    }
}
