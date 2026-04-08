#ifndef FILEIO_H
#define FILEIO_H

void IO_LoadAllFiles();
void IO_SaveCustomerToCheckoutFile();
void IO_SaveCustomerToWaitingListFile();
void IO_RemoveCustomerFromWaitingListFile();
void IO_SaveBarberToListFile();
void IO_RemoveBarberFromListFile();
void IO_UpdateBarberStatusToListFile();

#endif 