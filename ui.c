#include "ui.h"
#include "common.h"
#include <stdio.h> 
#include <stdbool.h>

static bool invalid_input_error(int input_command, int MIN_RANGE, int MAX_RANGE){
    if (input_command < MIN_RANGE || input_command > MAX_RANGE){
        return true;
    }
    return false;
}

static void UI_LogInvalidCommandError(){
    printf("[ERROR]: Invalid command. Try again!\n");
    printf("[TYPE YOUR CHOICE]: ");
}

static void UI_LogSuccess(){
    printf("[SUCCESS]: Action performed successfully!\n");
}

int UI_GetInputCommand(int MIN_RANGE, int MAX_RANGE){
    int input_command;
    scanf("%d", &input_command);

    while (invalid_input_error(input_command, MIN_RANGE, MAX_RANGE) == true){
        UI_LogInvalidInputError();
        scanf("%d", &input_command);
    }

    UI_LogSuccess();

    return input_command;
}

void UI_ShowCustomerPage(){
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


Customer UI_HandleAddCustomerWaitingList(){
    Customer customer;

    UI_LogSuccess();
    
    printf("Type the customer name to ADD (EXACTLY Upper/Lowercase): ");
    fgets(customer.name, sizeof(customer.name), stdin);

    printf("Type the customer ID to ADD (Integer): ");
    scanf("%d", &customer.id);
    
    return customer;
}


void UI_HandleCustomerPage(){
    UI_ShowUpdateCustomer();

    typedef enum {ADD_CUSTOMER_WAITING_LIST = 0, REMOVE_CUSTOMER_WAITING_LIST, RETURN_MENU, EXIT} SubState;

    int command = UI_GetInput(ADD_CUSTOMER_WAITING_LIST, EXIT);

    switch(command){
        case ADD_CUSTOMER_WAITING_LIST:
            break;

        case REMOVE_CUSTOMER_WAITING_LIST:
            break;

        case RETURN_MENU:
            break;

        case EXIT:
            break;
    }
}

void UI_ShowBarberPage(){
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

Barber UI_HandleAddBarber(){
    Barber barber;
    UI_LogSuccess();
    
    printf("Type the barber name to ADD (EXACTLY Upper/Lowercase): ");
    fgets(barber.name, sizeof(barber.name), stdin);
    printf("Type the barber ID to ADD (Integer):  ");
    scanf("%d", &barber.id);
    
    return barber;
}

Barber UI_HandleRemoveBarber(){
    Barber barber;

    UI_LogSuccess();
    
    printf("Type the barber ID to REMOVE (Integer): ");
    scanf("%d", &barber.id);

    return barber;
}

Barber UI_HandleUpdateBarberStatus(){
    Barber barber;
    UI_LogSuccess();
    
    printf("Type the barber ID to UPDATE status (Integer): ");
    scanf("%d", &barber.id);
    printf("Type (0/1) for (AVAILABLE/BUSY): ");
    scanf("%d", &barber.status);
    
    return barber;
}


void UI_HandleBarberPage(){
    typedef enum {ADD_BARBER = 0, UPDATE_BARBER_STATUS, REMOVE_BARBER, EXIT} SubState;
    UI_ShowUpdateBarber();
    int command = UI_GetInput(ADD_BARBER, EXIT);

    switch(command){
        case ADD_BARBER:
            break;

        case UPDATE_BARBER_STATUS:
            break;

        case REMOVE_BARBER:
            break;

        case EXIT:
            break;
    }
}

Customer UI_HandleCustomerCheckout(){
    Customer customer;

    UI_LogSuccess();
    
    printf("Type the customer name to CHECKOUT (EXACTLY Upper/Lowercase): ");
    fgets(customer.name, sizeof(customer.name), stdin);

    return customer;
}

void UI_HandleViewCustomerWaitingList(){
    printf("|-----------------------------------------------------------------|\n");
    printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
    printf("|================ *CUSTOMER WAITING LIST PAGE* ===================|\n");
}

void UI_HandleViewCustomerServingList(){
    printf("|-----------------------------------------------------------------|\n");
    printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
    printf("|================ *CUSTOMER SERVING LIST PAGE* ===================|\n");
}

void UI_HandleViewCheckoutHistory(){
    printf("|-----------------------------------------------------------------|\n");
    printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
    printf("|====================== *CHECK-OUT PAGE* =========================|\n");
}

void UI_HandleExit(){
    printf("|-----------------------------------------------------------------|\n");
    printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
    printf("|=================== AUTOMATICALLY SAVING DATA ===================|\n");
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