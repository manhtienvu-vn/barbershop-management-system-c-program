#ifndef OPERATION_H
#define OPERATION_H

#include "logic.h"
#include "fileio.h"
#include "common.h"
#include "ui.h"

void OP_HandleAddCustomerWaitingList();
void OP_HandleRemoveCustomerWaitingList();
void OP_HandleStartCustomerService();
void OP_HandleCustomerCheckout();
void OP_HandleAddBarber();
void OP_HandleUpdateBarberStatus();
void OP_HandleRemoveBarber();
void OP_HandleExit();

#endif