#ifndef UI_H
#define UI_H

#include "config.h"
#include <stdlib.h> 

typedef enum{
    MENU_PAGE = 0
    CUSTOMER_PAGE,
    BARBER_PAGE,
    STATE_EXIT
} UI_State;

typedef enum {
    NO = 0,
    ADD_CUSTOMER_WAITING_LIST,
    REMOVE_CUSTOMER_WAITING_LIST,
    START_CUSTOMER_SERVICE,
    PAYMENT_CHECKOUT,
    RETURN_MENU,
    EXIT1,
    ADD_BARBER,
    UPDATE_BARBER_STATUS,
    REMOVE_BARBER,
    EXIT2
} UI_Substate;


void UI_ShowMenu();
int UI_GetInput(int MIN_RANGE, int MAX_RANGE);

void UI_ClearScreen();
#endif 