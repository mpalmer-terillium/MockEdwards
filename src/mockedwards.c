#include "../include/mockedwards.h"


void error(const char *msg) {
    perror(msg);
    exit(0);
}

int callExternalService(char * soapEnv, char * response) {

    int sockfd, n;
    struct sockaddr_in serv_addr;
    socklen_t addr_size;
    char header[MAXLINE];
    int contentLength, headerLength;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("Error opening socket");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(7101);
    serv_addr.sin_addr.s_addr = inet_addr("192.168.1.105");
    memset(serv_addr.sin_zero, '\0', sizeof(serv_addr.sin_zero));
    addr_size = sizeof(serv_addr);

    contentLength = strlen(soapEnv);
    n = createRequestHeader(header, contentLength);
    headerLength = strlen(header);

    connect(sockfd, (struct sockaddr *) &serv_addr, addr_size);

    printf("HEADER: %s\n", header);
    printf("SOAPEnv: %s\n", soapEnv);

    n = write(sockfd, header, headerLength);
    if(n < 0)
        error("Error writing header to socket");

    n = write(sockfd, soapEnv, contentLength);
    if(n < 0)
        error("Error writing soapEnv to socket");

    bzero(response, MAXLINE);
    n = read(sockfd, response, MAXLINE - 1);
    if(n < 0)
        error("Error reading from socket");

    close(sockfd);
    return SUCCESS;
}

int createRequestHeader(char * request, int contentLength) {

    request[0] = '\0';
    sprintf(request, "POST /PayTrace/IntegrationPort HTTP/1.1\r\n");
    sprintf(request, "%sAccept-Encoding: gzip,deflate\r\n", request);
    sprintf(request, "%sContent-Type: text/xml;charset=UTF-8\r\n", request);
    sprintf(request, "%sSOAPAction: \"\"\r\n", request);
    sprintf(request, "%sContent-Length: %d\r\n", request, contentLength);
    sprintf(request, "%sHost: 192.168.1.105:7101\r\n", request);
    sprintf(request, "%sConnection: Keep-Alive\r\n", request);
    sprintf(request, "%sUser-Agent: Apache-HttpClient/4.1.1 (java 1.5)\r\n", request);
    sprintf(request, "%s\r\n", request);

    return SUCCESS;
}

int createSoapEnv(char * valueToInput, char * soapEnv) {

    char s0[]  = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n";
    char s1[]  = "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:ser=\"http://service.integration.paytrace.com.src/\">\r\n";
    char s2[]  = "<soapenv:Header/>\r\n";
    char s3[]  = "<soapenv:Body>\r\n";
    char s4[]  = "<ser:processExternalRequest>\r\n";
    char s5[]  = "<externalValueObject>\r\n";
    char s6[100];
    snprintf(s6, sizeof(s6), "%s%s%s", "<amount>", valueToInput, "</amount>\r\n");
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

int parseXmlGetOutput(char * token, char * response, char * lpDS_output) {

    /* find token in response */

    snprintf(lpDS_output, 101, "%s", response);

    printf("Returned Response: %s\n", response);

    return SUCCESS;
}
