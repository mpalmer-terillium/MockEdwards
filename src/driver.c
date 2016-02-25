#include "../include/mockedwards.h"
#include "../include/mockcontext.h"

#include "../include/mockbsfn01.h"
#include "../include/mockbsfn02.h"


int main(void)
{
    int status = INIT;

    struct DSBSFN01 *lpDS01 = (struct DSBSFN01 *) malloc(sizeof(struct DSBSFN01));
    struct mockcontext *ctx1 = get_context("192.168.1.105", 7101, "/PayTrace", "/IntegrationPort");

    strncpy(lpDS01->szInput, "200.00", 100);
    status = mockbsfn01_callBSFN(ctx1, lpDS01);

    if (status == SUCCESS) {
        fprintf(stdout, "INPUT: %s\nOUTPUT: %s\n", lpDS01->szInput, lpDS01->szOutput);
    } else {
        fprintf(stdout, "ERROR: %s\n", lpDS01->szErrorMsg);
    }

    struct DSBSFN02 *lpDS02 = (struct DSBSFN02 *) malloc(sizeof(struct DSBSFN02));
    struct mockcontext *ctx2 = get_context("192.168.1.105", 7101, "/OSCOpportunityService", "/OptyServiceImplService");

    strncpy(lpDS02->szInput, "TEST OP WS", 100);
    status = mockbsfn02_callBSFN(ctx2, lpDS02);

    if (status == SUCCESS) {
        fprintf(stdout, "INPUT: %s\nOUTPUT: %s\n", lpDS02->szInput, lpDS02->szOutput);
    } else {
        fprintf(stdout, "ERROR: %s\n", lpDS02->szErrorMsg);
    }

    free(lpDS01);
    free(lpDS02);
    free(ctx1);
    free(ctx2);
    return 0;
}
