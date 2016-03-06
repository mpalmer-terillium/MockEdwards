#include "../include/mockedwards.h"


void error(const char *msg, int *status) {
    *status = FAIL;
    perror(msg);
}

struct mockcontext *get_context(const char *ip_addr, int port, const char *serv_name, const char *serv_ep) {

    struct mockcontext *ctx = (struct mockcontext *) calloc(sizeof(struct mockcontext), 1);
    strncpy(ctx->ip_addr, ip_addr, strlen(ip_addr));
    ctx->port = port;
    strncpy(ctx->serv_name, serv_name, strlen(serv_name));
    strncpy(ctx->serv_endp, serv_ep, strlen(serv_ep));

    return ctx;
}

int callExternalService(struct mockcontext *ctx, char *soapEnv, char *response, char *header) {

    int sockfd, n;
    struct sockaddr_in serv_addr;
    socklen_t addr_size;
    int contentLength, headerLength, status = INIT;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error(ERROR_MSG_OP_SCKET, &status);
        return status;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(ctx->port);
    serv_addr.sin_addr.s_addr = inet_addr(ctx->ip_addr);
    memset(serv_addr.sin_zero, '\0', sizeof(serv_addr.sin_zero));
    addr_size = sizeof(serv_addr);

    contentLength = strlen(soapEnv);
    headerLength = strlen(header);

    debug_print("HEADER: %s\n\n", header);
    debug_print("SOAPEnv: %s\n\n", soapEnv);

    if(connect(sockfd, (struct sockaddr *) &serv_addr, addr_size) < 0) {
        error(ERROR_MSG_CON_SCKT, &status);
        return status;
    }

    if(write(sockfd, header, headerLength) < 0) {
        error(ERROR_MSG_WRT_HEDR, &status);
        return status;
    }

    if(write(sockfd, soapEnv, contentLength) < 0) {
        error(ERROR_MSG_WRT_ENVL, &status);
        return status;
    }

    bzero(response, MAXLINE);
    while((n = read(sockfd, response, MAXLINE - 1)) > 0) {
        ;
    }
    if(n < 0) {
        error(ERROR_MSG_READ_ENV, &status);
        return status;
    }

    close(sockfd);
    return status = SUCCESS;
}

int createRequestHeader(struct mockcontext *ctx, char * header, int contentLength) {

    char i0[] = "POST http://";
    char i1[] = ":";
    char i2[] = " HTTP/1.1\r\n";
    char i3[] = "Host: ";
    char i4[] = "\r\n";

    int size_s0 = strlen(i0) +
                  strlen(ctx->ip_addr) +
                  strlen(i1) +
                  4 + // port length (maybe use snprintf and get size?)
                  strlen(ctx->serv_name) +
                  strlen(ctx->serv_endp) +
                  strlen(i2);

    int size_s1 = strlen(i3) +
                  strlen(ctx->ip_addr) +
                  strlen(i1) +
                  4 +
                  strlen(ctx->serv_name) +
                  strlen(ctx->serv_endp) +
                  strlen(i2);

    char s0[size_s0 + 1];
    snprintf(s0, sizeof(s0), "%s%s%s%d%s%s%s",  i0,
                                                ctx->ip_addr,
                                                i1,
                                                ctx->port,
                                                ctx->serv_name,
                                                ctx->serv_endp,
                                                i2);
    char s1[size_s1 + 1];
    snprintf(s1, sizeof(s1), "%s%s%s%d%s", i3,
                                           ctx->ip_addr,
                                           i1,
                                           ctx->port,
                                           i4);
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
