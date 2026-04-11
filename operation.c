#include "operation.h"

extern UI_State g_state, g_lastState;
extern UI_SubState g_subState;

void OP_LoadSystemFromAllFiles(){

}

void OP_HandleCustomerSubstate(){
    Customer customer;
    switch (g_subState){
        case ADD_CUSTOMER_WAITING_LIST:
            customer = UI_HandleAddCustomerWaitingList();
            LOGIC_HandleAddCustomerWaitingList(customer);
            IO_SaveCustomerToWaitingListFile(customer);
            break;
        
        case REMOVE_CUSTOMER_WAITING_LIST:
            customer = UI_HandleRemoveCustomerWaitingList();
            LOGIC_HandleRemoveCustomerWaitingList(customer);
            IO_RemoveCustomerFromWaitingListFile(customer);
            break;

        case START_CUSTOMER_SERVICE:
            customer = UI_HandleStartCustomerService();
            LOGIC_HandleStartCustomerService(customer);
            IO_SaveCustomerToServingListFile(customer);
            break;
        
        case PAYMENT_CHECKOUT:
            customer = UI_HandleCustomerCheckout();
            LOGIC_HandleCustomerCheckout(customer);
            IO_SaveCustomerToCheckoutFiles(customer);
            break;

        case RETURN_MENU:
            g_subState = NO;
            g_state = MENU;
            break;

        case EXIT:
            g_subState = NO;
            g_state = EXIT_STATE;
            break;
    }

    if(g_state != EXIT_STATE && g_state != MENU_PAGE){
        g_subState = NO;
        g_state = CUSTOMER_PAGE;
    }

}

void OP_HandleBarberSubstate(){
    Barber barber;
    switch (g_subState){
        case ADD_BARBER:
            barber = UI_HandleAddBarber();
            LOGIC_HandleAddBarber(barber);
            IO_SaveBarberToListFile(barber);
            break;
        
        case UPDATE_BARBER_STATUS:
            barber = UI_HandleUpdateBarberStatus();
            LOGIC_UpdateBarberStatus(barber);
            IO_UpdateBarberStatusToListFile(barber, barber.status);
            break;

        case REMOVE_BARBER:
            barber = UI_HandleRemoveBarber();
            LOGIC_HandleRemoveBarber(barber);
            IO_RemoveBarberFromListFile(barber);
            break;

        case RETURN_MENU:
            g_subState = NO;
            g_state = MENU_PAGE;
            break;

        case EXIT:
            g_subState = NO;
            g_state = EXIT_STATE;
            break;
    }
    g_subState = NO;
    g_state = BARBER_PAGE;
}

void OP_RunProgram(){
    /* Initialize data structures (linkedlists, queue) from .csv files in computer*/
    OP_LoadSystemFromAllFiles();

    while(g_state != STATE_EXIT){
        switch(g_state) {
            case MENU_PAGE:
                UI_HandleMenuPage();
                break;
            
            case CUSTOMER_PAGE:
                UI_HandleCustomerManagementPage();
                OP_HandleCustomerSubstate();
                break;
            
            case BARBER_PAGE:
                UI_HandleBarberManagementPage();
                OP_HandleBarberSubstate();
                break;
            
            case EXIT_STATE:
                UI_HandleExit();
                break;
        }
        g_lastState = g_state;
    }
}