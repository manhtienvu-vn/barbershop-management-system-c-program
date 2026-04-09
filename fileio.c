/**
 * @file logic.c
 * @brief Implements data structures and operation handlers for the Barbershop.
 */

#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// GLOBAL STATE (Encapsulated within this module)
// ============================================================================

static CustomerQueue* g_customerQueue = NULL;
static BarberNode* g_barberList = NULL;

// ============================================================================
// CORE DATA STRUCTURE ALGORITHMS (Internal)
// ============================================================================

/**
 * @brief Internal function to initialize the queue.
 */
static CustomerQueue* CreateQueue() {
    CustomerQueue* queue = (CustomerQueue*)malloc(sizeof(CustomerQueue));
    if (queue != NULL) {
        queue->front = NULL;
        queue->rear = NULL;
        queue->count = 0;
    }
    return queue;
}

void System_Init() {
    g_customerQueue = CreateQueue();
    g_barberList = NULL;
}

// ============================================================================
// OPERATION HANDLER IMPLEMENTATIONS
// ============================================================================

void OP_HandleAddCustomerWaitingList(void) {
    if (g_customerQueue == NULL) {
        printf("[!] Error: System not initialized.\n");
        return;
    }

    int id;
    char nameBuffer[100];

    printf("\n--- ADD CUSTOMER TO WAITING LIST ---\n");
    printf("Enter Customer ID: ");
    if (scanf("%d", &id) != 1) return;
    
    printf("Enter Customer Name: ");
    scanf(" %[^\n]", nameBuffer); // Read string with spaces

    CustomerNode* new_node = (CustomerNode*)malloc(sizeof(CustomerNode));
    if (new_node == NULL) {
        printf("[!] Memory allocation failed.\n");
        return;
    }

    new_node->data.id = id;
    new_node->data.name = (char*)malloc(strlen(nameBuffer) + 1);
    strcpy(new_node->data.name, nameBuffer);
    new_node->next = NULL;

    if (g_customerQueue->rear == NULL) {
        g_customerQueue->front = new_node;
        g_customerQueue->rear = new_node;
    } else {
        g_customerQueue->rear->next = new_node;
        g_customerQueue->rear = new_node;
    }
    g_customerQueue->count++;

    int waitTime = (g_customerQueue->count - 1) * 30;
    printf("[+] Customer '%s' added to queue. Estimated wait time: %d minutes.\n", nameBuffer, waitTime);
}

void OP_HandleRemoveCustomerWaitingList(void) {
    if (g_customerQueue == NULL || g_customerQueue->front == NULL) {
        printf("[!] The waiting queue is currently empty.\n");
        return;
    }

    int id;
    printf("\n--- REMOVE CUSTOMER FROM QUEUE (LEAVING EARLY) ---\n");
    printf("Enter Customer ID to remove: ");
    if (scanf("%d", &id) != 1) return;

    CustomerNode* current = g_customerQueue->front;
    CustomerNode* prev = NULL;

    while (current != NULL && current->data.id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("[!] Customer ID %d not found in the queue.\n", id);
        return;
    }

    // Node to delete is the head
    if (prev == NULL) {
        g_customerQueue->front = current->next;
    } else {
        prev->next = current->next;
    }

    // Node to delete is the tail
    if (current == g_customerQueue->rear) {
        g_customerQueue->rear = prev;
    }

    printf("[-] Customer '%s' removed from the queue.\n", current->data.name);
    free(current->data.name);
    free(current);
    g_customerQueue->count--;
}

void OP_HandleCustomerCheckout(void) {
    printf("\n--- CUSTOMER CHECKOUT ---\n");
    int barberId;
    printf("Enter the ID of the Barber who finished the cut: ");
    if (scanf("%d", &barberId) != 1) return;

    BarberNode* current = g_barberList;
    while (current != NULL) {
        if (current->data.id == barberId) {
            current->data.status = AVAILABLE;
            printf("[+] Checkout successful. Barber '%s' is now AVAILABLE.\n", current->data.name);
            return;
        }
        current = current->next;
    }
    printf("[!] Barber ID %d not found.\n", barberId);
}

void OP_HandleAddBarber(void) {
    int id;
    char nameBuffer[100];

    printf("\n--- ADD NEW BARBER ---\n");
    printf("Enter Barber ID: ");
    if (scanf("%d", &id) != 1) return;

    printf("Enter Barber Name: ");
    scanf(" %[^\n]", nameBuffer);

    BarberNode* new_node = (BarberNode*)malloc(sizeof(BarberNode));
    if (new_node == NULL) {
        printf("[!] Memory allocation failed.\n");
        return;
    }

    new_node->data.id = id;
    new_node->data.name = (char*)malloc(strlen(nameBuffer) + 1);
    strcpy(new_node->data.name, nameBuffer);
    new_node->data.status = AVAILABLE; 
    new_node->next = NULL;

    if (g_barberList == NULL) {
        g_barberList = new_node;
    } else {
        BarberNode* temp = g_barberList;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    printf("[+] Barber '%s' added successfully.\n", nameBuffer);
}

void OP_HandleUpdateBarberStatus(void) {
    int id, statusInput;
    printf("\n--- UPDATE BARBER STATUS ---\n");
    printf("Enter Barber ID: ");
    if (scanf("%d", &id) != 1) return;

    printf("Select New Status (0 = AVAILABLE, 1 = BUSY): ");
    if (scanf("%d", &statusInput) != 1) return;

    BarberNode* current = g_barberList;
    while (current != NULL) {
        if (current->data.id == id) {
            current->data.status = (statusInput == 1) ? BUSY : AVAILABLE;
            printf("[+] Status updated successfully for Barber '%s'.\n", current->data.name);
            return;
        }
        current = current->next;
    }
    printf("[!] Barber ID %d not found.\n", id);
}

void OP_HandleRemoveBarber(void) {
    if (g_barberList == NULL) {
        printf("[!] Barber list is empty.\n");
        return;
    }

    int id;
    printf("\n--- REMOVE BARBER ---\n");
    printf("Enter Barber ID to remove: ");
    if (scanf("%d", &id) != 1) return;

    BarberNode* current = g_barberList;
    BarberNode* prev = NULL;

    // Head node deletion
    if (current != NULL && current->data.id == id) {
        g_barberList = current->next;
        printf("[-] Barber '%s' removed from system.\n", current->data.name);
        free(current->data.name);
        free(current);
        return;
    }

    // Search
    while (current != NULL && current->data.id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("[!] Barber ID %d not found.\n", id);
        return;
    }

    prev->next = current->next;
    printf("[-] Barber '%s' removed from system.\n", current->data.name);
    free(current->data.name);
    free(current);
}

// ============================================================================
// UTILITY FUNCTIONS (For testing & UI viewing)
// ============================================================================

void DisplayAllBarbers() {
    printf("\n--- CURRENT BARBER ROSTER ---\n");
    if (g_barberList == NULL) {
        printf("No barbers in the system right now.\n");
        return;
    }

    BarberNode* temp = g_barberList;
    while (temp != NULL) {
        printf("ID: %-4d | Name: %-15s | Status: %s\n", 
               temp->data.id, 
               temp->data.name, 
               (temp->data.status == BUSY) ? "BUSY (Cutting)" : "AVAILABLE");
        temp = temp->next;
    }
}

void DisplayWaitingQueue() {
    printf("\n--- WAITING SOFA QUEUE (%d waiting) ---\n", g_customerQueue ? g_customerQueue->count : 0);
    if (g_customerQueue == NULL || g_customerQueue->front == NULL) {
        printf("The sofa is empty.\n");
        return;
    }

    CustomerNode* temp = g_customerQueue->front;
    int pos = 1;
    while (temp != NULL) {
        printf("%d. ID: %-4d | Name: %s\n", pos++, temp->data.id, temp->data.name);
        temp = temp->next;
    }
}