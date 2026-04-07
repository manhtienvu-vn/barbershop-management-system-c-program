#include "ui.h"
#include "config.h"
#include <stdio.h> 

static UI_State ui_state;

void UI_GetInput(){
    int input_command;
    scanf("%d", &input_command);

    while(input_command < 0 || input_command > 3){
        printf("[ERROR]: Invalid command. Try again!\n");
        printf("[TYPE YOUR CHOICE HERE]: \n");
        scanf("%d", &input_command);

        switch(input_command){
            case MENU:
                if (ui_state == MENU){
                    while(input_command == MENU){
                        printf("[TYPE YOUR CHOICE HERE]: \n");
                        scanf("%d", &input_command);
                    }
                }
                break;

            case BARBER_PAGE:
                ui_state = BARBER_PAGE;
                break;

            case CUSTOMER_PAGE:
                break;

            case PROFITS_PAGE:
                break;
        }
    }
    
}

static void show_update_customer(){

}

static void show_update_barber(){

}

void UI_Handler(){

}

void UI_ShowMenu(){
    printf("|-----------------------------------------------------------------|\n");
    printf("|******** VINUNIVERSITY BARBERSHOP MANAGEMENT APPLICATION ********|\n");
    printf("|=================================================================|\n");
    printf("| 1. Add new customer.                                            |\n");
    printf("| 2. Update barber's status.                                      |\n");
    printf("| 3. Payment & Checkout.                                          |\n");        
    printf("| 4. View customer waiting list.                                  |\n");
    printf("| 5. View total profits.                                          |\n");
    printf("| 6. Exit.                                                        |\n");
    printf("|-----------------------------------------------------------------|\n");
    printf("\n");
    printf("TYPE YOUR CHOICE HERE: \n");
}

static void UI_ClearScreen(){

}