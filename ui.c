#include "ui.h"


/* Use these enum variables to switch between ui pages */
UI_State g_state = MENU_PAGE, g_lastState = MENU_PAGE;
UI_SubState g_subState = NO;

static bool invalid_input_error(int input_command, int MIN_RANGE, int MAX_RANGE){
    if (input_command < MIN_RANGE || input_command > MAX_RANGE){
        return true;
    }
    return false;
}

static void UI_LogInvalidInputError(){
    printf("[ERROR]: Invalid command. Try again!\n");
    printf("[TYPE YOUR CHOICE]: ");
}

static void UI_LogSuccess(){
    printf("[SUCCESS]: Action performed successfully!\n");
}

int UI_GetInputCommand(int MIN_RANGE, int MAX_RANGE){
    int input_command;

    while (scanf(" %d", &input_command) != 1 || invalid_input_error(input_command, MIN_RANGE, MAX_RANGE) == true){
        UI_LogInvalidInputError();
        scanf("%*s");
    }

    return input_command;
}

void UI_ClearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void UI_ShowMenu(){
    UI_ClearScreen();
    printf("|-----------------------------------------------------------------|\n");
    printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
    printf("|=================================================================|\n");
    printf("| 1. Open Customer Management Page.                               |\n");
    printf("| 2. Open Barber Management Page.                                 |\n");
    printf("| 3. Exit.                                                        |\n");
    printf("|-----------------------------------------------------------------|\n");
    printf("[TYPE YOUR CHOICE (1, 2, 3)]: ");
}

void UI_HandleMenuPage(){
    UI_ShowMenu();
    int command = UI_GetInputCommand(CUSTOMER_PAGE, STATE_EXIT);
    g_state = command;
}

void UI_ShowCustomerManagementPage(){
    if (g_state != g_lastState) {
        UI_ClearScreen();
        printf("|-----------------------------------------------------------------|\n");
        printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
        printf("|==================*CUSTOMER MANAGEMENT PAGE*=====================|\n");
        printf("| 1. Add customer to waiting list.                                |\n");
        printf("| 2. Remove customer from waiting list.                           |\n");
        printf("| 3. Start service: from waiting list to serving list.            |\n");
        printf("| 4. Payment & Checkout.                                          |\n");
        printf("| 5. View waiting list.                                           |\n");
        printf("| 6. View serving list.                                           |\n");
        printf("| 7. View checkout history.                                       |\n");       
        printf("| 8. Return to MENU.                                              |\n");
        printf("| 9. Exit.                                                        |\n");
        printf("|-----------------------------------------------------------------|\n");
        printf("[TYPE YOUR CHOICE (1, 2, 3, 4, 5, 6, 7, 8, 9)]: ");
    }
    else {
        printf("[TYPE YOUR CHOICE (1, 2, 3, 4, 5, 6, 7, 8, 9)]: ");
    }
}

CustomerStr UI_HandleAddCustomerWaitingList(){
    CustomerStr customer;

    UI_LogSuccess();
    
    printf("\n--- ADD CUSTOMER TO WAITING LIST ---\n");
    printf("[UI] Enter customer name (EXACTLY Upper/Lowercase): ");
    scanf(" %[^\n]", customer.name);

    printf("[UI] Enter customer ID (Integer): ");
    scanf(" %d", &customer.id);
    
    return customer;
}

CustomerStr UI_HandleRemoveCustomerWaitingList(){
    CustomerStr customer;
    UI_LogSuccess();
    
    printf("\n--- REMOVE CUSTOMER FROM WAITING LIST ---\n");
    printf("[UI] Enter customer name (EXACTLY Upper/Lowercase): ");
    scanf(" %[^\n]", customer.name);

    printf("[UI] Enter customer ID (Integer): ");
    scanf(" %d", &customer.id);
    
    return customer;
}

void UI_HandleStartCustomerService(void){
    UI_LogSuccess();
    printf("\n--- START CUSTOMER SERVICE (MOVE FROM WAITING TO SERVING LIST) ---\n");
}

CustomerStr UI_HandleCustomerCheckout(){
    CustomerStr customer;
    UI_LogSuccess();
    
    printf("\n--- CUSTOMER CHECKOUT ---\n");
    printf("[UI] Enter customer name (EXACTLY Upper/Lowercase): ");
    scanf(" %[^\n]", customer.name);

    printf("[UI] Enter customer ID (Integer): ");
    scanf(" %d", &customer.id);
    
    return customer;
}

void UI_HandleCustomerManagementPage(){
    UI_ShowCustomerManagementPage();
    int command = UI_GetInputCommand(ADD_CUSTOMER_WAITING_LIST, EXIT1);
    g_subState = command;
}

void UI_ShowBarberManagementPage(){
    if (g_state != g_lastState){
        UI_ClearScreen();
        printf("|-----------------------------------------------------------------|\n");
        printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
        printf("|================== *BARBER MANAGEMENT PAGE* =====================|\n");
        printf("| 8. Return to MENU.                                              |\n");
        printf("| 10. Add new barber.                                             |\n");
        printf("| 11. Update barber status (AVAILABLE/BUSY).                      |\n");
        printf("| 12. Remove barber from barber list.                             |\n");
        printf("| 13. View barber list.                                           |\n");
        printf("| 14. Exit.                                                       |\n");
        printf("|-----------------------------------------------------------------|\n");
        printf("[TYPE YOUR CHOICE (8, 10, 11, 12, 13, 14)]: ");
    }
    else {
        printf("[TYPE YOUR CHOICE (8, 10, 11, 12, 13, 14)]: ");
    }
    
}

BarberStr UI_HandleAddBarber(){
    BarberStr barber;
    UI_LogSuccess();
    
    printf("[UI] Type the barber name to ADD (EXACTLY Upper/Lowercase): ");
    scanf(" %[^\n]", barber.name);
    printf("[UI] Type the barber ID to ADD (Integer):  ");
    scanf(" %d", &barber.id);
    
    return barber;
}

BarberStr UI_HandleRemoveBarber(){
    BarberStr barber;
    UI_LogSuccess();
    printf("[UI] Type the barber name to REMOVE (EXACTLY Upper/Lowercase): ");
    scanf(" %[^\n]", barber.name);
    printf("[UI] Type the barber ID to REMOVE (Integer): ");
    scanf(" %d", &barber.id);

    return barber;
}

BarberStr UI_HandleUpdateBarberStatus(){
    BarberStr barber;
    UI_LogSuccess();
    printf("[UI] Type the barber name to UPDATE (EXACTLY Upper/Lowercase): ");
    scanf(" %[^\n]", barber.name);
    printf("[UI] Type the barber ID to UPDATE status (Integer): ");
    scanf(" %d", &barber.id);
    printf("[UI] Type (0/1) for (AVAILABLE/BUSY): ");
    scanf(" %d", &barber.status);
    
    return barber;
}


void UI_HandleBarberManagementPage(){
    UI_ShowBarberManagementPage();
    int command = UI_GetInputCommand(RETURN_MENU, EXIT2);
    g_subState = command;
}


void UI_HandleViewCustomerWaitingList(){
    UI_ClearScreen();
    printf("|-----------------------------------------------------------------|\n");
    printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
    printf("|================ *CUSTOMER WAITING LIST PAGE* ===================|\n");
}

void UI_HandleViewCustomerServingList(){
    UI_ClearScreen();
    printf("|-----------------------------------------------------------------|\n");
    printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
    printf("|================ *CUSTOMER SERVING LIST PAGE* ===================|\n");
}

void UI_HandleViewCheckoutHistory(){
    UI_ClearScreen();
    printf("|-----------------------------------------------------------------|\n");
    printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
    printf("|====================== *CHECK-OUT PAGE* =========================|\n");
}

void UI_HandleExit(){
    printf("|-----------------------------------------------------------------|\n");
    printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
    printf("|=================== AUTOMATICALLY SAVING DATA ===================|\n");
    printf("|=======================    THANK YOU!    ========================|\n");
}

