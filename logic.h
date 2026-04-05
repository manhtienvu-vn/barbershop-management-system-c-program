/**
 * @file logic.h
 * @brief Header file containing data structures and function declarations for the Barbershop system.
 * @note Strictly adheres to Google C++ Style Guide and dynamic memory allocation requirements.
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
    char* name; // Using char* for dynamic memory allocation instead of static arrays
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
    CustomerNode* front; // Front of the queue (next person to be served)
    CustomerNode* rear;  // Rear of the queue (newly arrived person)
    int count;           // Number of waiting customers
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
// FUNCTION DECLARATIONS: CUSTOMER QUEUE MANAGEMENT
// ============================================================================

/**
 * @brief Initializes the customer queue.
 * @return CustomerQueue* Pointer to the newly allocated queue.
 */
CustomerQueue* CreateQueue();

/**
 * @brief Adds a new customer to the queue (Enqueue).
 * @param queue Pointer to the queue.
 * @param id Customer ID.
 * @param name Customer name.
 */
void EnqueueCustomer(CustomerQueue* queue, int id, const char* name);

/**
 * @brief Checks the number of customers currently waiting on the sofa.
 * @param queue Pointer to the queue.
 * @return int Number of waiting customers.
 */
int GetWaitingCount(CustomerQueue* queue);

/**
 * @brief Calculates the estimated wait time for a newly arrived customer.
 * @param queue Pointer to the queue.
 * @return int Wait time in minutes (assuming 1 customer takes 30 minutes).
 */
int CalculateWaitTime(CustomerQueue* queue);

// ============================================================================
// FUNCTION DECLARATIONS: BARBER LINKED LIST MANAGEMENT
// ============================================================================

/**
 * @brief Adds a new barber to the list.
 * @param head Pointer to the head node of the barber list.
 * @param id Barber ID.
 * @param name Barber name.
 * @return BarberNode* Returns the new head pointer of the list.
 */
BarberNode* AddBarber(BarberNode* head, int id, const char* name);

/**
 * @brief Changes the status of a barber (e.g., to BUSY when cutting hair).
 * @param head Pointer to the head node.
 * @param id ID of the barber to update.
 * @param new_status New status (AVAILABLE or BUSY).
 */
void SetBarberStatus(BarberNode* head, int id, BarberStatus new_status);

/**
 * @brief Removes a barber from the list (when they quit/leave).
 * @param head Pointer to the head node.
 * @param id ID of the barber to remove.
 * @return BarberNode* Returns the new head pointer.
 */
BarberNode* RemoveBarber(BarberNode* head, int id);

/**
 * @brief Displays the entire list of barbers and their current status.
 * @param head Pointer to the head node.
 */
void DisplayBarbers(BarberNode* head);

#endif // LOGIC_H_
