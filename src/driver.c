#include "../include/mockedwards.h"
#include "../include/mockbsfn01.h"


int main(void)
{
    int status = INIT;
    struct DSBSFN01 *lpDS = (struct DSBSFN01 *) malloc(sizeof(struct DSBSFN01));

    strncpy(lpDS->szInput, "200.00", 100);

    status = mockbsfn01_callBSFN(lpDS);

    if (status == SUCCESS) {
        fprintf(stdout, "INPUT: %s\nOUTPUT: %s\n", lpDS->szInput, lpDS->szOutput);
    } else {
        fprintf(stdout, "ERROR: %s\n", lpDS->szErrorMsg);
    }

    free(lpDS);
    return 0;
}
