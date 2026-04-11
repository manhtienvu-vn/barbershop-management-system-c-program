#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include "common.h"

extern CustomerQueue* g_customerQueue;
extern BarberNode* g_barberList;

void IO_LoadAllFiles();

/* WAITING FOR SERVICE (in the bench hahahahahaha) */
void IO_SaveCustomerToWaitingListFile(CustomerStr customer);
void IO_RemoveCustomerFromWaitingListFile(CustomerStr customer);
void IO_SaveCustomerToServingListFile(CustomerStr customer);
void IO_SaveCustomerToCheckoutFiles(CustomerStr customer);

/* BARBER INFORMATION MANAGEMENT*/
void IO_SaveBarberToListFile(BarberStr barber);
void IO_RemoveBarberFromListFile(BarberStr barber);
void IO_UpdateBarberStatusToListFile(BarberStr barber);
void IO_ViewCheckoutHistory();
void IO_RefreshWaitingListFile();
void IO_RefreshServingListFile();
void IO_RefreshBarberListFile();
void IO_RefreshAllFiles();

#endif 