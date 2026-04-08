#ifndef UI_H
#define UI_H

#include "config.h"
#include <stdlib.h> 

typedef enum{
    PAGE_UPDATE_CUSTOMER = 0 ,
    PAGE_UPDATE_BARBER = 1,
    PAGE_CHECKOUT = 2,
    PAGE_VIEW_WAITING_LIST = 3,
    PAGE_VIEW_HISTORY = 4,
    PAGE_EXIT = 5
} UI_State;

void UI_ShowMenu();
int UI_GetInput(int MIN_RANGE, int MAX_RANGE);
void UI_ClearScreen();
#endif 