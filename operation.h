#ifndef OPERATION_H
#define OPERATION_H

#include "logic.h"
#include "fileio.h"
#include "common.h"
#include "ui.h"

extern UI_State g_state, g_lastState;
extern UI_SubState g_subState;

extern CustomerQueue* g_customerQueue;
extern CustomerNode* g_servingList;
extern BarberNode* g_barberList;

void OP_LoadSystemFromAllFiles();
void OP_HandleCustomerSubstate();
void OP_HandleBarberSubstate();
void OP_RunProgram();

#endif