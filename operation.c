#include "operation.h"

void OP_LoadSystemFromAllFiles() {
    char buffer[512];
    char time_trash[50];

    // --- 1. LOAD WAITING LIST FROM CSV FILE  ---
    FILE* f1 = fopen("waiting_list.csv", "r");
    if (f1 == NULL) {
        f1 = fopen("waiting_list.csv", "w");
        if (f1 != NULL) { 
            fprintf(f1, "Customer ID, Customer Name\n");
            fclose(f1); 
        }
    } 
    else {
        g_customerQueue->count = 0;
        g_customerQueue->front = g_customerQueue->rear = NULL; 

        while (fgets(buffer, sizeof(buffer), f1)) {
            if (strstr(buffer, "Customer ID") || strlen(buffer) < 3){
                /* Skip the table header line*/
                continue;
            }
            CustomerNode* node = (CustomerNode*)malloc(sizeof(CustomerNode));
            if (sscanf(buffer, " %d , %[^\n\r,]", &node->data.id, node->data.name) == 2) {
                node->next = NULL; 
                if (g_customerQueue->front == NULL){ 
                    g_customerQueue->front = g_customerQueue->rear = node;
                }
                else {
                    /* Add node to the rear: FIFO (derive out from front node to serve)*/ 
                    g_customerQueue->rear->next = node; 
                    g_customerQueue->rear = node; 
                }
                g_customerQueue->count++;
            } 
            else {
                free(node);
            }
        }
        fclose(f1);
    }

    // --- 2. LOAD SERVING LIST FROM CSV FILE ---
    FILE* f2 = fopen("serving_list.csv", "r");
    if (f2 == NULL) {
        f2 = fopen("serving_list.csv", "w");
        if (f2 != NULL) { 
            fprintf(f2, "Customer ID, Customer Name, Barber ID, Time\n"); 
            fclose(f2); 
        }
    } 
    else {
        g_servingList = NULL;
        while (fgets(buffer, sizeof(buffer), f2)) {
            if (strstr(buffer, "Customer ID") || strlen(buffer) < 5){
                /* Skip the table header line*/
                continue;
            }
            CustomerNode* node = (CustomerNode*)malloc(sizeof(CustomerNode));
            if (sscanf(buffer, " %d , %[^,] , %d , %[^\n\r]", &node->data.id, node->data.name, &node->data.assigned_barber_id, time_trash) == 4) {
                node->next = g_servingList;
                g_servingList = node;
            } 
            else {
                free(node);
            }
        }
        fclose(f2);
    }

    // --- 3. LOAD BARBER LIST FROM CSV FILE ---
    FILE* f3 = fopen("barber_list.csv", "r");

    if (f3 == NULL) {
        f3 = fopen("barber_list.csv", "w");
        if (f3 != NULL) { 
            fprintf(f3, "Barber ID, Barber Name, Status\n"); 
            fclose(f3); 
        }
    } 
    else {
        g_barberList = NULL;
        while (fgets(buffer, sizeof(buffer), f3)) {
            if (strstr(buffer, "Barber ID") || strlen(buffer) < 3){
                /* Skip the table header line*/
                continue;
            }
            BarberNode* node = (BarberNode*)malloc(sizeof(BarberNode));
            int status_val;
            if (sscanf(buffer, " %d , %[^,] , %d", &node->data.id, node->data.name, &status_val) == 3) {
                node->data.status = (BarberStatus)status_val;
                node->next = NULL; 

                if (g_barberList == NULL){
                    g_barberList = node;
                }
                else {
                    BarberNode* temp = g_barberList;
                    while (temp->next != NULL){
                        temp = temp->next; // Sẽ không treo nếu node->next đã là NULL
                    }
                    temp->next = node;
                }
            } 
            else{
                free(node);
            }
        }
        fclose(f3);
    }
    printf("[SYSTEM] Load completed. Waiting: %d\n", g_customerQueue->count);
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
            UI_HandleStartCustomerService();
            LOGIC_HandleStartCustomerService();
            if (g_servingList != NULL) {
                customer.id = g_servingList->data.id;
                customer.assigned_barber_id = g_servingList->data.assigned_barber_id;
                strcpy(customer.name, g_servingList->data.name); 
                IO_RemoveCustomerFromWaitingListFile(customer);
                IO_SaveCustomerToServingListFile(customer);
                IO_UpdateAllBarberStatus();
            }
            break;
        
        case PAYMENT_CHECKOUT:
            customer = UI_HandleCustomerCheckout();
            LOGIC_HandleCustomerCheckout(&customer);
            IO_SaveCustomerToCheckoutFiles(customer);

            break;
        
        case VIEW_WAITING_LIST:
            LOGIC_DisplayWaitingQueue();
            break;

        case VIEW_SERVING_LIST:
            LOGIC_DisplayServingList();
            break;

        case VIEW_CHECKOUT:
            IO_ViewCheckoutHistory();
            break;

        case RETURN_MENU:
            g_lastState = CUSTOMER_PAGE;
            g_state = MENU_PAGE;
            break;

        case EXIT1:
            g_state = STATE_EXIT;
            return;
    }

    g_subState = NO;
    if(g_state != STATE_EXIT && g_state != MENU_PAGE){
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
            LOGIC_HandleUpdateBarberStatus(barber);
            IO_UpdateBarberStatusToListFile(barber);
            break;

        case REMOVE_BARBER:
            barber = UI_HandleRemoveBarber();
            LOGIC_HandleRemoveBarber(barber);
            IO_RemoveBarberFromListFile(barber);
            break;

        case VIEW_BARBER_LIST:
            LOGIC_DisplayBarberList();
            break;

        case RETURN_MENU:
            g_lastState = BARBER_PAGE;
            g_state = MENU_PAGE;
            break;

        case EXIT2:
            g_state = STATE_EXIT;
            return;
    }
    g_subState = NO;
    if(g_state != STATE_EXIT && g_state != MENU_PAGE){
        g_state = BARBER_PAGE;
    }
}

void OP_RunProgram(){
    LOGIC_SystemInit();
    /* Initialize data structures (linkedlists, queue) from .csv files in computer*/
    OP_LoadSystemFromAllFiles();

    while(g_state != STATE_EXIT){
        UI_State temp_state = g_state;
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
            
            case STATE_EXIT:
                UI_HandleExit();
                break;
        }

        if (g_state == STATE_EXIT){
            exit(0);
        }
        g_lastState = temp_state;
    }
}