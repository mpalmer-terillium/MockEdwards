#include "../include/mockedwards.h"


void error(const char *msg, int *status) {
    *status = FAIL;
    perror(msg);
    exit(0);
}

struct mockcontext *get_context(const char *ip_addr, int port, const char *serv_name, const char *serv_ep) {

    struct mockcontext *ctx = (struct mockcontext *) malloc(sizeof(struct mockcontext));
    strncpy(ctx->ip_addr, ip_addr, 20);
    ctx->port = port;
    strncpy(ctx->serv_name, serv_name, 100);
    strncpy(ctx->serv_endp, serv_ep, 100);

    return ctx;
}

int callExternalService(struct mockcontext *ctx, char *soapEnv, char *response, char *header) {

    int sockfd, n;
    struct sockaddr_in serv_addr;
    socklen_t addr_size;
    int contentLength, headerLength, status = INIT;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("Error opening socket", &status);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(ctx->port);
    serv_addr.sin_addr.s_addr = inet_addr(ctx->ip_addr);
    memset(serv_addr.sin_zero, '\0', sizeof(serv_addr.sin_zero));
    addr_size = sizeof(serv_addr);

    contentLength = strlen(soapEnv);
    headerLength = strlen(header);

    connect(sockfd, (struct sockaddr *) &serv_addr, addr_size);

    printf("HEADER: %s\n", header);
    printf("SOAPEnv: %s\n", soapEnv);

    n = write(sockfd, header, headerLength);
    if(n < 0)
        error("Error writing header to socket", &status);

    n = write(sockfd, soapEnv, contentLength);
    if(n < 0)
        error("Error writing soapEnv to socket", &status);

    bzero(response, MAXLINE);
    n = read(sockfd, response, MAXLINE - 1);
    if(n < 0)
        error("Error reading from socket", &status);

    close(sockfd);
    return status = SUCCESS;
}

int createRequestHeader(struct mockcontext *ctx, char * header, int contentLength) {

    char s0[100];
    snprintf(s0, sizeof(s0), "%s%s%s%d%s%s%s", "POST http://",
                                                ctx->ip_addr,
                                                ":",
                                                ctx->port,
                                                ctx->serv_name,
                                                ctx->serv_endp,
                                               " HTTP/1.1\r\n");
    char s1[100];
    snprintf(s1, sizeof(s1), "%s%s%s%d%s", "Host: ",
                                           ctx->ip_addr,
                                           ":",
                                           ctx->port,
                                           "\r\n");
    header[0] = '\0';
    sprintf(header, "%s", s0);
    sprintf(header, "%sAccept-Encoding: gzip,deflate\r\n", header);
    sprintf(header, "%sContent-Type: text/xml;charset=UTF-8\r\n", header);
    sprintf(header, "%sSOAPAction: \"\"\r\n", header);
    sprintf(header, "%sContent-Length: %d\r\n", header, contentLength);
    sprintf(header, "%s%s", header, s1);
    sprintf(header, "%sConnection: Keep-Alive\r\n", header);
    sprintf(header, "%sUser-Agent: Apache-HttpClient/4.1.1 (java 1.5)\r\n", header);
    sprintf(header, "%s\r\n", header);

    return SUCCESS;
}
