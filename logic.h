/**
 * @file logic.h
 * @brief Header file containing data structures, core algorithms, and operation handlers.
 * @note Strictly adheres to Google C++ Style Guide and dynamic memory allocation.
 */

#ifndef LOGIC_H_
#define LOGIC_H_

// ============================================================================
// DATA DEFINITIONS (STRUCTS & ENUMS)
// ============================================================================

/**
 * @brief Working status of a barber.
 */
typedef enum {
    AVAILABLE = 0,
    BUSY = 1
} BarberStatus;

/**
 * @brief Customer information.
 */
typedef struct {
    int id;
    char* name; 
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

// ============================================================================
// SYSTEM INITIALIZATION
// ============================================================================

/**
 * @brief Initializes the global lists and queues for the system.
 * Must be called once at the start of main().
 */
void System_Init();

// ============================================================================
// TARGET OPERATION HANDLERS (CLI Wrappers)
// ============================================================================

void OP_HandleAddCustomerWaitingList(void);
void OP_HandleRemoveCustomerWaitingList(void);
void OP_HandleCustomerCheckout(void);
void OP_HandleAddBarber(void);
void OP_HandleUpdateBarberStatus(void);
void OP_HandleRemoveBarber(void);

// ============================================================================
// DISPLAY & UTILITY FUNCTIONS
// ============================================================================

/**
 * @brief Displays the current status of all barbers.
 */
void DisplayAllBarbers();

/**
 * @brief Displays the customers currently waiting in the queue.
 */
void DisplayWaitingQueue();

#endif // LOGIC_H_  
