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
void IO_SaveCustomerToWaitingListFile(Customer customer);
void IO_RemoveCustomerFromWaitingListFile(Customer customer);
void IO_SaveCustomerToServingListFile(Customer customer);
void IO_SaveCustomerToCheckoutFiles(Customer customer);

/* BARBER INFORMATION MANAGEMENT*/
void IO_SaveBarberToListFile(Barber barber);
void IO_RemoveBarberFromListFile(Barber barber);
void IO_UpdateBarberStatusToListFile(Barber barber);
void IO_ViewCheckoutHistory();
void IO_RefreshWaitingListFile();
void IO_RefreshServingListFile();
void IO_RefreshBarberListFile();
void IO_RefreshAllFiles();

#endif 