#include "ui.h"
#include "config.h"
#include <stdio.h> 
#include <stdbool.h>

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

int UI_GetInput(int MIN_RANGE, int MAX_RANGE){
    int input_command;
    scanf("%d", &input_command);

    while (invalid_input_error(input_command, MIN_RANGE, MAX_RANGE) == true){
        UI_LogInvalidInputError();
        scanf("%d", &input_command);
    }

    UI_LogSuccess();

    return input_command;
}

void UI_ShowUpdateCustomer(){
    printf("|-----------------------------------------------------------------|\n");
    printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
    printf("|==================*CUSTOMER MANAGEMENT PAGE*=====================|\n");
    printf("| 1. Add customer to waiting list.                                |\n");
    printf("| 2. Remove customer from waiting list.                           |\n");
    printf("| 3. Return to MENU.                                              |\n");
    printf("| 4. Exit.                                                        |\n");
    printf("|-----------------------------------------------------------------|\n");
    printf("[TYPE YOUR CHOICE]: ");
}


void UI_HandleAddCustomerNameWaitingList(){

    UI_LogSuccess();
    
    printf("[Press SPACE to CANCEL] Type the customer name to ADD (EXACTLY Upper/Lowercase): ");
    
}




void UI_HandleUpdateCustomer(){
    UI_ShowUpdateCustomer();

    typedef enum {ADD_CUSTOMER_WAITING_LIST = 0, REMOVE_CUSTOMER_WAITING_LIST, RETURN_MENU, EXIT} SubState;

    int substate = UI_GetInput(ADD_CUSTOMER_WAITING_LIST, EXIT);

    return substate;
}

void UI_ShowUpdateBarber(){
    printf("|-----------------------------------------------------------------|\n");
    printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
    printf("|================== *BARBER MANAGEMENT PAGE* =====================|\n");
    printf("| 1. Add new barber.                                              |\n");
    printf("| 2. Update barber status (AVAILABLE/BUSY).                       |\n");
    printf("| 3. Remove barber from barber list.                              |\n");
    printf("| 4. Return to MENU.                                              |\n");
    printf("| 5. Exit.                                                        |\n");
    printf("|-----------------------------------------------------------------|\n");
    printf("[TYPE YOUR CHOICE]: ");
}

void UI_HandleAddBarber(){
    char name[30];

    UI_LogSuccess();
    
    printf("[Press SPACE to CANCEL] Type the barber name to ADD (EXACTLY Upper/Lowercase): ");
    fgets(name, sizeof(name), stdin);
}

void UI_HandleRemoveBarber(){
    char name[30];

    UI_LogSuccess();
    
    printf("[Press SPACE to CANCEL] Type the barber name to REMOVE (EXACTLY Upper/Lowercase): ");
    fgets(name, sizeof(name), stdin);

}

void UI_HandleUpdateBarberStatus(){
    UI_LogSuccess();
    
    printf("[Press SPACE to CANCEL] Type (0/1) for (AVAILABLE/BUSY): ");
    
    int status = UI_GetInput(AVAILABLE, BUSY);
}


void UI_HandleUpdateBarber(){
    typedef enum {ADD_BARBER = 0, UPDATE_BARBER_STATUS, REMOVE_BARBER, EXIT} SubState;
    UI_ShowUpdateBarber();
    int status = UI_GetInput(ADD_BARBER, EXIT);
}

void UI_HandleCustomerCheckout(){
    char name[30];

    UI_LogSuccess();
    
    printf("[Press SPACE to CANCEL] Type the customer name to CHECKOUT (EXACTLY Upper/Lowercase): ");
    fgets(name, sizeof(name), stdin);
}

void UI_HandleViewCustomerWaitingList(){

}

void UI_HandleViewCheckoutHistory(){

}

void UI_HandleExit(){
    
}

void UI_ShowMenu(){
    printf("|-----------------------------------------------------------------|\n");
    printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
    printf("|=================================================================|\n");
    printf("| 1. Update customer in waiting list.                             |\n");
    printf("| 2. Update barber's status.                                      |\n");
    printf("| 3. Payment & Checkout.                                          |\n");        
    printf("| 4. View customer waiting list.                                  |\n");
    printf("| 5. View history.                                                |\n");
    printf("| 6. Exit.                                                        |\n");
    printf("|-----------------------------------------------------------------|\n");
    printf("[TYPE YOUR CHOICE]: ");
}

void UI_ClearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}