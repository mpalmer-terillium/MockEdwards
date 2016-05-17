#ifndef HHI_BSFN_ITEM_H
#define HHI_BSFN_ITEM_H

#include "mockedwards.h"
#include "mockcontext.h"

#define HHI_BSFN_ITEM_NAME			"HHI Integegraion Item BSFN"

#define HHI_ITEM_NUM_START			"<accountnum>"
#define HHI_ITEM_NUM_END			"</accountnum>"
#define HHI_ITEM_RESPONSE_START		"<response>"
#define HHI_ITEM_RESPONSE_END		"</response>"


struct DSBSFN_HHI_ITEM {
    char szItemNum[101];
    /* this could include anything related to customer - need to know what to use */
    /* const char *szAction; maybe have an action? or simplify and just have this do updates */
    char szResponse[1001];
    char szErrorMsg[101];
};

int HHI_ITEM_callBSFN(struct mockcontext *ctx, struct DSBSFN_HHI_ITEM *lpDS);
int HHI_ITEM_createSoapEnv(struct DSBSFN_HHI_ITEM *, char *);
int HHI_ITEM_parseXMLResponse(char *, char *, char *, struct DSBSFN_HHI_ITEM *);
void HHI_ITEM_logger(struct DSBSFN_HHI_ITEM *lpDSHHITEM, int status);



#endif /* HHI_BSFN_ITEM_H */
