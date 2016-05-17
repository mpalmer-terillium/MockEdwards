#include "../include/HHI_bsfn_cust.h"
#include "../include/mockedwards.h"



int HHI_CUST_callBSFN(struct mockcontext *ctx, struct DSBSFN_HHI_CUST *lpDS) {

    char header[MAXLINE], soapEnv[MAXLINE], response[MAXLINE];

    if (HHI_CUST_createSoapEnv(lpDS, soapEnv) != SUCCESS) {
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

    if (HHI_CUST_parseXMLResponse((char *) HHI_CUST_RESPONSE_START, (char *) HHI_CUST_RESPONSE_END, response, lpDS) != SUCCESS) {
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_PRS_RESP);
        return FAIL;
    }

    debug_print("RESPONSE\n%s\n", response);

    return SUCCESS;
}

int HHI_CUST_createSoapEnv(struct DSBSFN_HHI_CUST *lpDS, char * soapEnv) {

    char line_end[] = "\r\n";

    int size_s5 = strlen(HHI_ACCT_NUM_START) + strlen(lpDS->szAccountNum) +
            strlen(HHI_ACCT_NUM_END) + strlen(line_end);

    char s0[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n";
    char s1[] = "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:ser=\"http://service.mockqueue.com/\">\r\n";
    char s2[] = "<soapenv:Header/>\r\n";
    char s3[] = "<soapenv:Body>\r\n";
    char s4[] = "<ser:processCustomer>\r\n";
    char s5[] = "<Customer>\r\n";
    char s6[size_s5 + 1];
    snprintf(s5, sizeof (s5), "%s%s%s%s", HHI_ACCT_NUM_START, lpDS->szAccountNum, HHI_ACCT_NUM_END, line_end);
    char s7[] = "</Customer>\r\n";
    char s8[] = "</ser:processCustomer>\r\n";
    char s9[] = "</soapenv:Body>\n";
    char s10[] = "</soapenv:Envelope>\n";

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

    return SUCCESS;
}

int HHI_CUST_parseXMLResponse(char *start_token, char *end_token, char *response, struct DSBSFN_HHI_CUST *lpDS) {

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

void HHI_CUST_logger(struct DSBSFN_HHI_CUST *lpDS, int status) {
    if (status == SUCCESS) {
        fprintf(stdout, "\nFunction: %s\nMessage: %s\nResponse: %s\n\n",
                HHI_BSFN_CUST_NAME, lpDS->szAccountNum, lpDS->szResponse);
    } else {
        fprintf(stdout, "\nFunction: %s\nError: %s\n\n", HHI_BSFN_CUST_NAME, lpDS->szErrorMsg);
    }
}
