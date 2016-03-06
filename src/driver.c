#include "../include/mockedwards.h"

#include "../include/mockbsfn03.h"

int sendMessage(struct DSBSFN03 *lpDS, const char *type, struct mockcontext *ctx) {
    strncpy(lpDS->szMessage, "New Message", 100);
    strncpy(lpDS->szType, type, 100);
    return mockbsfn03_callBSFN(ctx, lpDS);
}

int main(void)
{
    int status = INIT;
    char serv_addr_local[] = "127.0.0.1";
    int serv_port_local = 8080;
    
    struct DSBSFN03 *lpDS03 = (struct DSBSFN03 *) calloc(sizeof(struct DSBSFN03), 1);
    struct mockcontext *ctx = get_context(serv_addr_local, serv_port_local, "/MockQueueService", "/MockQueueService");
    
    status = sendMessage(lpDS03, "PayTrace", ctx);
    mockbsfn03_logger_message(lpDS03, status);
    
    status = sendMessage(lpDS03, "SalesCloud", ctx);
    mockbsfn03_logger_message(lpDS03, status);
    
    status = sendMessage(lpDS03, "Unknown", ctx);
    mockbsfn03_logger_message(lpDS03, status);

    free(lpDS03);
    free(ctx);
    return 0;
}
