#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"

void IO_LoadAllFiles();

/* WAITING FOR SERVICE (in the bench hahahahahaha) */
void IO_SaveCustomerToWaitingListFile(CustomerNode* new_node);
void IO_RemoveCustomerFromWaitingListFile(CustomerNode* node);

/* CUSTOMER BEING SERVED BY BARBER (in the barber chair) */
void IO_SaveCustomerToServingListFile(CustomerNode* node);
void IO_SaveCustomerToCheckoutFile(CustomerNode* node);

/* BARBER INFORMATION MANAGEMENT*/
void IO_SaveBarberToListFile(BarberNode* new_node);
void IO_RemoveBarberFromListFile(BarberNode* node);
void IO_UpdateBarberStatusToListFile(BarberNode* node, BarberStatus status);

#endif 