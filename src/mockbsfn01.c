#include "../include/mockbsfn01.h"
#include "../include/mockedwards.h"


int mockbsfn01_callBSFN(struct DSBSFN01 *lpDS)
{
    char header[MAXLINE], soapEnv[MAXLINE], response[MAXLINE];
    int status = INIT;

    status = createSoapEnv(lpDS, soapEnv);
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_SOAP_ENV);

    status = createRequestHeader(header, strlen(soapEnv));
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_REQ_HEAD);

    status = callExternalService(soapEnv, response, header);
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_CALL_EXT);

    status = parseXmlGetOutput((char *) "valueAsReturnedOnResponse", response, lpDS);
    if(status != SUCCESS)
        snprintf(lpDS->szErrorMsg, 101, "%s", ERROR_MSG_PRS_RESP);

    return status;
}

int createRequestHeader(char * header, int contentLength) {

    header[0] = '\0';
    sprintf(header, "POST /PayTrace/IntegrationPort HTTP/1.1\r\n");
    sprintf(header, "%sAccept-Encoding: gzip,deflate\r\n", header);
    sprintf(header, "%sContent-Type: text/xml;charset=UTF-8\r\n", header);
    sprintf(header, "%sSOAPAction: \"\"\r\n", header);
    sprintf(header, "%sContent-Length: %d\r\n", header, contentLength);
    sprintf(header, "%sHost: 192.168.1.105:7101\r\n", header);
    sprintf(header, "%sConnection: Keep-Alive\r\n", header);
    sprintf(header, "%sUser-Agent: Apache-HttpClient/4.1.1 (java 1.5)\r\n", header);
    sprintf(header, "%s\r\n", header);

    return SUCCESS;
}

int createSoapEnv(struct DSBSFN01 *lpDS, char * soapEnv) {

    char s0[]  = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n";
    char s1[]  = "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:ser=\"http://service.integration.paytrace.com.src/\">\r\n";
    char s2[]  = "<soapenv:Header/>\r\n";
    char s3[]  = "<soapenv:Body>\r\n";
    char s4[]  = "<ser:processExternalRequest>\r\n";
    char s5[]  = "<externalValueObject>\r\n";
    char s6[100];
    snprintf(s6, sizeof(s6), "%s%s%s", "<amount>", lpDS->szInput, "</amount>\r\n");
    char s7[]  = "<creditCardNumber></creditCardNumber>\r\n";
    char s8[]  = "<expirationMonth></expirationMonth>\r\n";
    char s9[]  = "<expirationYear></expirationYear>\r\n";
    char s10[] = "<method></method>\r\n";
    char s11[] = "<parmName></parmName>\r\n";
    char s12[] = "<password></password>\r\n";
    char s13[] = "<terms></terms>\r\n";
    char s14[] = "<transactionType></transactionType>\r\n";
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

int parseXmlGetOutput(char * token, char * response, struct DSBSFN01 *lpDS) {

    /*
        Find token in response.
        might need to have a start token and end token:
        maybe pass in "result", then look for a start of <result> and
        an end of </result> and use those two values to get the middle.
        Everything between the end of the first token and the start of
        second token.
    */

    char *respValue = strstr(response, token);

    snprintf(lpDS->szOutput, MAXLINE, "%s", respValue);

    printf("Returned Response: %s\n", response);

    return SUCCESS;
}
