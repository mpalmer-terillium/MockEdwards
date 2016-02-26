#include "../include/mockedwards.h"

#include "../include/mockbsfn01.h"
#include "../include/mockbsfn02.h"


void logger_info(const char *, char *, char *,char *, int);

int main(void)
{
    int status = INIT;
    char serv_addr[] = "192.168.1.105";
    int serv_port = 7101;

    struct DSBSFN01 *lpDS01 = (struct DSBSFN01 *) calloc(sizeof(struct DSBSFN01), 1);
    struct mockcontext *ctx1 = get_context(serv_addr, serv_port, "/PayTrace", "/IntegrationPort");

    strncpy(lpDS01->szInput, "200.00", 100);
    status = mockbsfn01_callBSFN(ctx1, lpDS01);

    logger_info("BSFN01", lpDS01->szInput, lpDS01->szOutput, lpDS01->szErrorMsg, status);

    struct DSBSFN02 *lpDS02 = (struct DSBSFN02 *) calloc(sizeof(struct DSBSFN02), 1);
    struct mockcontext *ctx2 = get_context(serv_addr, serv_port, "/OSCOpportunityService", "/OptyServiceImplService");

    strncpy(lpDS02->szInput, "TEST OP WS", 100);
    status = mockbsfn02_callBSFN(ctx2, lpDS02);

    logger_info("BSFN02", lpDS02->szInput, lpDS02->szOutput, lpDS02->szErrorMsg, status);

    free(lpDS01);
    free(lpDS02);
    free(ctx1);
    free(ctx2);
    return 0;
}

void logger_info(const char *name, char *input, char *output, char *error, int status) {
    if(status == SUCCESS) {
        fprintf(stdout, "Function: %s\nInput: %s\nOutput: %s\n\n", name, input, output);
    } else {
        fprintf(stdout, "Function: %s\nError: %s\n\n", name, error);
    }
}
