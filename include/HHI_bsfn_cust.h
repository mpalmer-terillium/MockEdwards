#ifndef HHI_BSFN_CUST_H
#define HHI_BSFN_CUST_H

#include "mockedwards.h"
#include "mockcontext.h"

#define HHI_BSFN_CUST_NAME			"HHI Integegraion Customer BSFN"

#define HHI_ACCT_NUM_START			"<accountnum>"
#define HHI_ACCT_NUM_END			"</accountnum>"
#define HHI_CUST_RESPONSE_START		"<response>"
#define HHI_CUST_RESPONSE_END		"</response>"


struct DSBSFN_HHI_CUST {
    char szAccountNum[101];
    /* this could include anything related to customer - need to know what to use */
    /* const char *szAction; maybe have an action? or simplify and just have this do updates */
    char szResponse[1001];
    char szErrorMsg[101];
};

int HHI_CUST_callBSFN(struct mockcontext *ctx, struct DSBSFN_HHI_CUST *lpDS);
int HHI_CUST_createSoapEnv(struct DSBSFN_HHI_CUST *, char *);
int HHI_CUST_parseXMLResponse(char *, char *, char *, struct DSBSFN_HHI_CUST *);
void HHI_CUST_logger(struct DSBSFN_HHI_CUST *lpDSHHICUST, int status);



#endif /* HHI_BSFN_CUST_H */
