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

void OP_HandleStartCustomerService(){
    UI_HandleStartCustomerService();
    LOGIC_HandleStartCustomerService();
}

void OP_HandleCustomerCheckout(){
    UI_HandleStartCustomerService();
    LOGIC_HandleStartCustomerService();
}

void OP_HandleAddBarber(){
    UI_HandleAddBarber();
    LOGIC_HandleAddBarber();
}

void OP_HandleUpdateBarberStatus(){
    UI_HandleUpdateBarberStatus();
    LOGIC_HandleUpdateBarberStatus();
}

void OP_HandleRemoveBarber(){
    UI_HandleRemoveBarber();
    LOGIC_HandleRemoveBarber();
}

void OP_HandleExit(){
    UI_HandleExit();
    LOGIC_HandleExit();
}