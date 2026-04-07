#ifndef UI_H
#define UI_H

#include "config.h"

typedef enum{
    MENU = DEFAULT_MENU_STATE ,
    BARBER_PAGE,
    CUSTOMER_PAGE,
    PROFITS_PAGE
} UI_State;

void UI_ShowMenu();

#endif 