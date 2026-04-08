#include "ui.h"
#include "config.h"
#include "logic.h"
#include <stdio.h> 
#include <stdbool.h>

static bool invalid_input_error(int input_command, int MIN_RANGE, int MAX_RANGE){
    if (input_command < MIN_RANGE || input_command > MAX_RANGE){
        return true;
    }
    return false;
}

static void log_invalid_input_error(){
    printf("[ERROR]: Invalid command. Try again!\n");
    printf("[TYPE YOUR CHOICE]: ");
}

static void log_success(){
    printf("[SUCCESS]: Action performed successfully!\n");
}

int UI_GetInput(int MIN_RANGE, int MAX_RANGE){
    int input_command;
    scanf("%d", &input_command);

    while (invalid_input_error(input_command, MIN_RANGE, MAX_RANGE) == true){
        log_invalid_input_error();
        scanf("%d", &input_command);
    }

    log_success();

    return input_command;
}

static void show_update_customer(){
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


static void handle_add_customer_waiting_list(){
    char name[30];

    log_success();
    
    printf("[Press SPACE to CANCEL] Type the customer name (EXACTLY Upper/Lowercase): ");
    fgets(name, sizeof(name), stdin);
}



static void handle_update_customer(){
    show_update_customer();

    typedef enum {ADD_CUSTOMER_WAITING_LIST = 0, REMOVE_CUSTOMER_WAITING_LIST, RETURN_MENU, EXIT} SubState;
    SubState substate;

    substate = UI_GetInput(ADD_CUSTOMER_WAITING_LIST, EXIT);

    // switch(substate){
    //     case ADD_CUSTOMER_WAITING_LIST:

    // }
    
}

static void show_update_barber(){
    printf("|-----------------------------------------------------------------|\n");
    printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
    printf("|================== *BARBER MANAGEMENT PAGE* =====================|\n");
    printf("| 1. Add new barber.                                              |\n");
    printf("| 2. Update barber status (AVAILABLE/BUSY).                       |\n");
    printf("| 3. Return to MENU.                                              |\n");
    printf("| 4. Exit.                                                        |\n");
    printf("|-----------------------------------------------------------------|\n");
    printf("[TYPE YOUR CHOICE]: ");
}

static void handle_add_barber(){
    char name[30];

    log_success();
    
    printf("[Press SPACE to CANCEL] Type the barber name (EXACTLY Upper/Lowercase): ");
    fgets(name, sizeof(name), stdin);
}

static void handle_update_barber_status(){
    int status;

    log_success();
    
    printf("[Press SPACE to CANCEL] Type (0/1) for (AVAILABLE/BUSY): ");
    
    status = UI_GetInput(AVAILABLE, BUSY);
}


static void handle_update_barber(){

}

static void handle_checkout(){}
static void handle_view_waiting_list(){}
static void handle_view_history(){}
static void handle_exit(){}

void UI_Handler(int ui_state){
    switch (ui_state){
        case PAGE_UPDATE_CUSTOMER:
            handle_update_customer();
            break;
        case PAGE_UPDATE_BARBER:
            handle_update_barber();
            break;
        case PAGE_CHECKOUT:
            handle_checkout();
            break;
        case PAGE_VIEW_WAITING_LIST:
            handle_view_waiting_list();
            break;
        case PAGE_VIEW_HISTORY:
            handle_view_history();
            break;
        case PAGE_EXIT:
            handle_exit();
            break;
    }
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