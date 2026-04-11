#ifndef UI_H
#define UI_H

#include "common.h"
#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h> 

typedef enum{
    MENU_PAGE = 0,
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
    VIEW_WAITING_LIST,
    VIEW_SERVING_LIST,
    VIEW_CHECKOUT,
    RETURN_MENU,
    EXIT1,
    ADD_BARBER,
    UPDATE_BARBER_STATUS,
    REMOVE_BARBER,
    VIEW_BARBER_LIST,
    EXIT2
} UI_SubState;

int UI_GetInputCommand(int MIN_RANGE, int MAX_RANGE);
void UI_ShowMenu();
void UI_ClearScreen();

void UI_HandleMenuPage();

void UI_ShowCustomerManagementPage();
CustomerStr UI_HandleAddCustomerWaitingList();
CustomerStr UI_HandleRemoveCustomerWaitingList();
void UI_HandleStartCustomerService(void);
CustomerStr UI_HandleCustomerCheckout();
void UI_HandleCustomerManagementPage();

void UI_ShowBarberManagementPage();
BarberStr UI_HandleAddBarber();
BarberStr UI_HandleRemoveBarber();
BarberStr UI_HandleUpdateBarberStatus();
void UI_HandleBarberManagementPage();

void UI_HandleViewCustomerWaitingList();
void UI_HandleViewCustomerServingList();
void UI_HandleViewCheckoutHistory();
void UI_HandleExit();

#endif 