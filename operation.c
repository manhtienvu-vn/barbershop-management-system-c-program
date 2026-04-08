#include "operation.h"

void OP_HandleAddCustomerWaitingList(CustomerQueue* queue){
    UI_HandleAddCustomerWaitingList();
    char name[30];
    fgets(name, sizeof(name), stdin);
    LOGIC_EnqueueCustomer(queue, name);
}

void OP_HandleRemoveCustomerWaitingList(){
    UI_HandleRemoveCustomerWaitingList();
    
    char name[30];
    fgets(name, sizeof(name), stdin);
    
}