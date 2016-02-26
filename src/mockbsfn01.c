#include "../include/mockbsfn01.h"
#include "../include/mockedwards.h"


int mockbsfn01_callBSFN(struct mockcontext *ctx, struct DSBSFN01 *lpDS)
{
    char header[MAXLINE], soapEnv[MAXLINE], response[MAXLINE];
    int status = INIT;

    status = mockbsfn01_createSoapEnv(lpDS, soapEnv);
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_SOAP_ENV);

    status = createRequestHeader(ctx, header, strlen(soapEnv));
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_REQ_HEAD);

    status = callExternalService(ctx, soapEnv, response, header);
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_CALL_EXT);

    status = mockbsfn01_parseXmlResponse((char *) OUTPUT_TOKEN_START_DSBSFN01,
                                          (char *) OUTPUT_TOKEN_END_DSBSFN01,
                                          response,
                                          lpDS);
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_PRS_RESP);

    return status;
}

int mockbsfn01_createSoapEnv(struct DSBSFN01 *lpDS, char * soapEnv) {

    /* Here also use the context to create the method call - this and the
       header should be built as dynamically as possible, or at least in a way
       that mimics the actual edwards calls */

    char s0[]  = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n";
    char s1[]  = "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:ser=\"http://service.integration.paytrace.com.src/\">\r\n";
    char s2[]  = "<soapenv:Header/>\r\n";
    char s3[]  = "<soapenv:Body>\r\n";
    char s4[]  = "<ser:processExternalRequest>\r\n";
    char s5[]  = "<externalValueObject>\r\n";
    char s6[100];
    snprintf(s6, sizeof(s6), "%s%s%s", "<amount>", lpDS->szInput, "</amount>\r\n");
    char s7[]  = "<creditCardNumber>4012881888818888</creditCardNumber>\r\n";
    char s8[]  = "<expirationMonth>12</expirationMonth>\r\n";
    char s9[]  = "<expirationYear>16</expirationYear>\r\n";
    char s10[] = "<method>processtranx</method>\r\n";
    char s11[] = "<parmName>PARMLIST</parmName>\r\n";
    char s12[] = "<password></password>\r\n";
    char s13[] = "<terms>Y</terms>\r\n";
    char s14[] = "<transactionType>Authorization</transactionType>\r\n";
    char s15[] = "<username></username>\r\n";
    char s16[] = "</externalValueObject>\r\n";
    char s17[] = "</ser:processExternalRequest>\r\n";
    char s18[] = "</soapenv:Body>\n";
    char s19[] = "</soapenv:Envelope>\n";

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
    strcat(soapEnv, s12);
    strcat(soapEnv, s13);
    strcat(soapEnv, s14);
    strcat(soapEnv, s15);
    strcat(soapEnv, s16);
    strcat(soapEnv, s17);
    strcat(soapEnv, s18);
    strcat(soapEnv, s19);

    return SUCCESS;
}

int mockbsfn01_parseXmlResponse(char *start_token, char *end_token, char *response, struct DSBSFN01 *lpDS) {

    char *respValue = strstr(response, start_token);
    char *respEnd = strstr(response, end_token);
    char *respStart = respValue + strlen(start_token);
    int len = respEnd - respStart;

    strncpy(lpDS->szOutput, respStart, len);

    return SUCCESS;
}
