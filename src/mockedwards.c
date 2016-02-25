#include "../include/mockedwards.h"


void error(const char *msg, int *status) {
    *status = FAIL;
    perror(msg);
    exit(0);
}

int callExternalService(char * soapEnv, char * response, char * header) {

    int sockfd, n;
    struct sockaddr_in serv_addr;
    socklen_t addr_size;
    int contentLength, headerLength, status = INIT;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("Error opening socket", &status);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(7101);
    serv_addr.sin_addr.s_addr = inet_addr("192.168.1.105");
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
