#include "../include/mockedwards.h"

#include "../include/mockbsfn03.h"
#include "../include/HHI_bsfn_cust.h"
#include "../include/HHI_bsfn_item.h"


int hhi_integration_test() {
	
	int status = INIT;
	char serv_addr_local[] = "192.168.1.105"; // may change - see router DHCP table
	int serv_port_local = 7101;  // check this - what port is WLS listening on?
	
	struct DSBSFN_HHI_CUST *lpDSHHICUST = malloc(sizeof(struct DSBSFN_HHI_CUST));
	struct DSBSFN_HHI_ITEM *lpDSHHIITEM = calloc(sizeof(struct DSBSFN_HHI_ITEM), 1);
	struct mockcontext *ctx = get_context(serv_addr_local, serv_port_local, "/ConceptConfiguratorTest", "/JDEToConceptServicePort");
	
	strncpy(lpDSHHICUST->szAccountNum, "1234", 100);
	status = HHI_CUST_callBSFN(ctx, lpDSHHICUST);
	HHI_CUST_logger(lpDSHHICUST, status);
	
	strncpy(lpDSHHIITEM->szItemNum, "ITEM NUM", 100);
	status = HHI_ITEM_callBSFN(ctx, lpDSHHIITEM);
	HHI_ITEM_logger(lpDSHHIITEM, status);
	
	return 0;
}
	

int mockbsfn03_sendMessage(struct DSBSFN03 *lpDS, const char *type, struct mockcontext *ctx) {
    strncpy(lpDS->szMessage, "New Message", 100);
    strncpy(lpDS->szType, type, 100);
    return mockbsfn03_callBSFN(ctx, lpDS);
}

int internal_integration_test() {

	int status = INIT;
    char serv_addr_local[] = "127.0.0.1";
    int serv_port_local = 8080;
    
    struct DSBSFN03 *lpDS03 = (struct DSBSFN03 *) calloc(sizeof(struct DSBSFN03), 1);
    struct mockcontext *ctx = get_context(serv_addr_local, serv_port_local, "/MockQueueService", "/MockQueueService");
    
    status = mockbsfn03_sendMessage(lpDS03, "PayTrace", ctx);
    mockbsfn03_logger_message(lpDS03, status);
    
    status = mockbsfn03_sendMessage(lpDS03, "SalesCloud", ctx);
    mockbsfn03_logger_message(lpDS03, status);
    
    status = mockbsfn03_sendMessage(lpDS03, "Unknown", ctx);
    mockbsfn03_logger_message(lpDS03, status);

    free(lpDS03);
    free(ctx);
    
    return 0;
}


int main(void)
{
    //internal_integration_test();
    
    hhi_integration_test();
    
    return 0;
}
