#ifndef LOGIC_H_
#define LOGIC_H_

#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// DATA DEFINITIONS (STRUCTS & ENUMS)


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
void LOGIC_HandleAddCustomerWaitingList(Customer customer); 
void LOGIC_HandleRemoveCustomerWaitingList(Customer customer);
void LOGIC_HandleStartCustomerService(void);
void LOGIC_HandleCustomerCheckout(Customer* customer);
void LOGIC_HandleAddBarber(Barber barber);
void LOGIC_HandleUpdateBarberStatus(Barber barber);
void LOGIC_HandleRemoveBarber(Barber barber);

// DISPLAY & UTILITY FUNCTIONS

void LOGIC_DisplayWaitingQueue();
void LOGIC_DisplayServingList();
void LOGIC_DisplayBarberList();

#endif // LOGIC_H_  