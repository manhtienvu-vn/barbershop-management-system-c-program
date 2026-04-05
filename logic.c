/**
 * @file logic.c
 * @brief Implements the logic functions for the Barbershop system.
 */

#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// IMPLEMENTATION: CUSTOMER QUEUE MANAGEMENT
// ============================================================================

CustomerQueue* CreateQueue() {
    CustomerQueue* queue = (CustomerQueue*)malloc(sizeof(CustomerQueue));
    if (queue == NULL) {
        printf("Error: Cannot allocate memory for the Queue!\n");
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
    return queue;
}

void EnqueueCustomer(CustomerQueue* queue, int id, const char* name) {
    if (queue == NULL) return;

    CustomerNode* new_node = (CustomerNode*)malloc(sizeof(CustomerNode));
    if (new_node == NULL) {
        printf("Error: Cannot allocate memory for CustomerNode!\n");
        return;
    }

    new_node->data.id = id;
    new_node->data.name = (char*)malloc(strlen(name) + 1);
    strcpy(new_node->data.name, name);
    new_node->next = NULL;

    if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
    queue->count++;
}

int GetWaitingCount(CustomerQueue* queue) {
    if (queue == NULL) return 0;
    return queue->count;
}

int CalculateWaitTime(CustomerQueue* queue) {
    if (queue == NULL) return 0;
    // Each waiting customer takes 30 minutes
    return queue->count * 30;
}

// ============================================================================
// IMPLEMENTATION: BARBER LINKED LIST MANAGEMENT
// ============================================================================

BarberNode* AddBarber(BarberNode* head, int id, const char* name) {
    BarberNode* new_node = (BarberNode*)malloc(sizeof(BarberNode));
    if (new_node == NULL) {
        printf("Error: Cannot allocate memory for BarberNode!\n");
        return head;
    }

    new_node->data.id = id;
    new_node->data.name = (char*)malloc(strlen(name) + 1);
    strcpy(new_node->data.name, name);
    new_node->data.status = AVAILABLE; // Default status for a new barber is AVAILABLE
    new_node->next = NULL;

    // Insert at the end of the list
    if (head == NULL) {
        return new_node;
    }

    BarberNode* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;

    return head;
}

void SetBarberStatus(BarberNode* head, int id, BarberStatus new_status) {
    BarberNode* temp = head;
    while (temp != NULL) {
        if (temp->data.id == id) {
            temp->data.status = new_status;
            return;
        }
        temp = temp->next;
    }
    printf("Barber with ID %d not found.\n", id);
}

BarberNode* RemoveBarber(BarberNode* head, int id) {
    if (head == NULL) return NULL;

    BarberNode* temp = head;
    BarberNode* prev = NULL;

    // If the barber to be removed is the head node
    if (temp != NULL && temp->data.id == id) {
        head = temp->next;
        free(temp->data.name); // Free dynamically allocated string
        free(temp);            // Free the node
        return head;
    }

    // Search for the barber to be removed
    while (temp != NULL && temp->data.id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If barber was not found
    if (temp == NULL) {
        printf("Barber with ID %d not found for removal.\n", id);
        return head;
    }

    // Unlink the node from the list and free memory
    prev->next = temp->next;
    free(temp->data.name);
    free(temp);

    return head;
}

void DisplayBarbers(BarberNode* head) {
    printf("\n--- BARBER LIST ---\n");
    if (head == NULL) {
        printf("There are currently no barbers available.\n");
        return;
    }

    BarberNode* temp = head;
    while (temp != NULL) {
        printf("ID: %d | Name: %-15s | Status: %s\n", 
               temp->data.id, 
               temp->data.name, 
               (temp->data.status == BUSY) ? "BUSY (Cutting)" : "AVAILABLE (Resting)");
        temp = temp->next;
    }
    printf("-------------------\n");
}
