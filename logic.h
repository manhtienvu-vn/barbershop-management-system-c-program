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
    char* name; 
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
void System_Init();

// TARGET OPERATION HANDLERS

void LOGIC_HandleAddCustomerWaitingList(void);
void LOGIC_HandleStartCustomerService(void);
void LOGIC_HandleCustomerStartService(void);
void LOGIC_HandleCustomerCheckout(void);
void LOGIC_HandleAddBarber(void);
void LOGIC_HandleUpdateBarberStatus(void);
void LOGIC_HandleRemoveBarber(void);

// DISPLAY & UTILITY FUNCTIONS

/**
 * @brief Displays the current status of all barbers.
 */
void LOGIC_DisplayAllBarbers();

/**
 * @brief Displays the customers currently waiting in the queue.
 */
void LOGIC_DisplayWaitingQueue();

#endif // LOGIC_H_  