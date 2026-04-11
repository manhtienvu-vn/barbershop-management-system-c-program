#ifndef LOGIC_H_
#define LOGIC_H_

#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// DATA DEFINITIONS (STRUCTS & ENUMS)

/**
 * @brief Customer information.
 */
typedef struct {
    int id;
    char name[30]; 
    int assigned_barber_id;
} Customer;

/**
 * @brief Singly Linked List node for the Customer Queue.
 */
typedef struct CustomerNode {
    Customer data;
    struct CustomerNode* next;
} CustomerNode;

/**
 * @brief Queue structure to manage waiting customers on the sofa.
 */
typedef struct {
    CustomerNode* front; 
    CustomerNode* rear;  
    int count;           
} CustomerQueue;

/**
 * @brief Barber information.
 */
typedef struct {
    int id;
    char* name;
    BarberStatus status;
} Barber;

/**
 * @brief Singly Linked List node for the Barber list.
 */
typedef struct BarberNode {
    Barber data;
    struct BarberNode* next;
} BarberNode;

// SYSTEM INITIALIZATION

/**
 * @brief Initializes the global lists and queues for the system.
 * Must be called once at the start of main().
 */
void LOGIC_SystemInit();

// TARGET OPERATION HANDLERS
void LOGIC_HandleAddCustomerWaitingList(CustomerStr customer); 
void LOGIC_HandleRemoveCustomerWaitingList(CustomerStr customer);
void LOGIC_HandleStartCustomerService(void);
void LOGIC_HandleCustomerCheckout(CustomerStr customer);
void LOGIC_HandleAddBarber(BarberStr barber);
void LOGIC_HandleUpdateBarberStatus(BarberStr barber);
void LOGIC_HandleRemoveBarber(BarberStr barber);

// DISPLAY & UTILITY FUNCTIONS

void LOGIC_DisplayWaitingQueue();
void LOGIC_DisplayServingList();
void LOGIC_DisplayBarberList();

#endif // LOGIC_H_  