#include "logic.h"

// GLOBAL STATE
CustomerQueue* g_customerQueue = NULL;
CustomerNode* g_servingList = NULL;
BarberNode* g_barberList = NULL;

// CORE DATA STRUCTURE ALGORITHMS 
CustomerQueue* CreateQueue() {
    CustomerQueue* queue = (CustomerQueue*)malloc(sizeof(CustomerQueue));
    if (queue != NULL) {
        queue->front = NULL;
        queue->rear = NULL;
        queue->count = 0;
    }
    return queue;
}

void LOGIC_SystemInit() {
    /* Create a queue for customer's waiting list*/
    g_customerQueue = CreateQueue();
    g_servingList = NULL;
    g_barberList = NULL;
}

// OPERATION HANDLER IMPLEMENTATIONS

void LOGIC_HandleAddCustomerWaitingList(Customer customer) {
    if (g_customerQueue == NULL) {
        printf("[LOGIC ERROR]: System not initialized.\n");
        return;
    }

    CustomerNode* new_node = (CustomerNode*)malloc(sizeof(CustomerNode));
    if (new_node == NULL) {
        printf("[LOGIC ERROR] Memory allocation failed.\n");
        return;
    }

    new_node->data.id = customer.id;
    new_node->data.assigned_barber_id = -1;
    strcpy(new_node->data.name, customer.name);
    new_node->next = NULL;

    if (g_customerQueue->rear == NULL) {
        g_customerQueue->front = new_node;
        g_customerQueue->rear = new_node;
    } else {
        g_customerQueue->rear->next = new_node;
        g_customerQueue->rear = new_node;
    }
    g_customerQueue->count++;

    int waitTime = (g_customerQueue->count - 1) * WAITING_TIME;
    printf("[LOGIC SUCCESS] Customer '%s' added to queue. Estimated wait time: %d minutes.\n", customer.name, waitTime);
}

void LOGIC_HandleRemoveCustomerWaitingList(Customer customer) {
    if (g_customerQueue == NULL || g_customerQueue->front == NULL) {
        printf("[LOGIC ERROR] The waiting queue is currently empty.\n");
        return;
    }

    CustomerNode* current = g_customerQueue->front;
    CustomerNode* prev = NULL;

    while (current != NULL && current->data.id != customer.id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("[LOGIC ERROR] Customer ID %d not found in the queue.\n", customer.id);
        return;
    }

    // Node to delete is the head
    if (prev == NULL) {
        g_customerQueue->front = current->next;
    } else {
        prev->next = current->next;
    }

    // Node to delete is the rear
    if (current == g_customerQueue->rear) {
        g_customerQueue->rear = prev;
    }

    printf("[LOGIC SUCCESS] Customer '%s' removed from the queue.\n", current->data.name);
    free(current);
    g_customerQueue->count--;
}

void LOGIC_HandleStartCustomerService(void){
    if (g_customerQueue->count > 0){
        BarberNode* temp = g_barberList;
        while (temp != NULL && temp->data.status != AVAILABLE) {
            temp = temp->next;
        }

        /* If all barbers are BUSY */
        if (temp == NULL){
            printf("[LOGIC ERROR]: All barbers are BUSY. Please wait until a barber finishes.\n");
            return;
        }

        /* If found an AVAILABLE barber*/
        /* Derive the front node (First Customer in the Queue) to serving linked-list*/
        CustomerNode* serving_node = g_customerQueue->front;
        CustomerNode* next_node = serving_node->next;

        g_customerQueue->front = next_node;
        /* Update new front node of the waiting queue*/
        g_customerQueue->count--;

        if (g_customerQueue->front == NULL){
            /* If this customer is the last one in the waiting queue,
               then update rear node to NULL */
            g_customerQueue->rear = NULL;
        }

        serving_node->next = g_servingList;
        g_servingList = serving_node;

        /* Assigned the AVAILABLE barber to this customer*/
        serving_node->data.assigned_barber_id = temp->data.id;
        temp->data.status = BUSY;

        printf("[LOGIC SUCCESS]: Customer %s, ID: '%d' is now being served by Barber %s, ID: '%d'.\n",
                serving_node->data.name, serving_node->data.id, temp->data.name, temp->data.id);
    }
    else{
        printf("[LOGIC ERROR]: No customer is waiting.\n");
    }
}

void LOGIC_HandleCustomerCheckout(Customer customer) {
    CustomerNode* current = g_servingList;
    CustomerNode* prev = NULL;

    while (current != NULL && current->data.id != customer.id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("[LOGIC ERROR] Customer ID %d not found in serving list.\n", customer.id);
        return;
    }


    /* Update new status for the assigned barber of this customer to be AVAILABLE */
    Barber barber;
    barber.id = current->data.assigned_barber_id;
    barber.status = AVAILABLE;
    LOGIC_HandleUpdateBarberStatus(barber);

    /* If node to delete is the head*/
    if(prev == NULL){
        g_servingList = current->next;
    }
    else {
        prev->next = current->next;
    }
    
    printf("[LOGIC SUCCESS] Checked out Customer %s, ID: %d.\n", customer.name, customer.id);

    free(current);
}

void LOGIC_HandleAddBarber(Barber barber) {
    BarberNode* new_node = (BarberNode*)malloc(sizeof(BarberNode));
    if (new_node == NULL) {
        printf("[LOGIC ERROR] Memory allocation failed.\n");
        return;
    }

    new_node->data.id = barber.id;
    strcpy(new_node->data.name, barber.name);
    new_node->data.status = AVAILABLE; 
    new_node->next = NULL;

    if (g_barberList == NULL) {
        g_barberList = new_node;
    } 
    else {
        BarberNode* temp = g_barberList;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    printf("[LOGIC SUCCESS] Barber '%s' added successfully.\n", barber.name);
}

void LOGIC_HandleUpdateBarberStatus(Barber barber) {
    BarberNode* current = g_barberList;
    while (current != NULL) {
        if (current->data.id == barber.id) {
            current->data.status = barber.status;
            printf("[LOGIC SUCCESS] Status updated successfully for Barber '%s', ID: '%d'.\n", current->data.name, current->data.id);
            return;
        }
        current = current->next;
    }
    printf("[LOGIC ERROR] Barber ID '%d' not found.\n", barber.id);
}

void LOGIC_HandleRemoveBarber(Barber barber) {
    if (g_barberList == NULL) {
        printf("[LOGIC ERROR] Barber list is empty.\n");
        return;
    }

    BarberNode* current = g_barberList;
    BarberNode* prev = NULL;

    // Head node deletion
    if (current != NULL && current->data.id == barber.id) {
        g_barberList = current->next;
        printf("[LOGIC SUCCESS] Barber '%s', ID: '%d' removed from system.\n", current->data.name, current->data.id);
        free(current);
        return;
    }

    // Search
    while (current != NULL && current->data.id != barber.id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("[LOGIC ERROR] Barber ID '%d' not found.\n", barber.id);
        return;
    }

    prev->next = current->next;
    printf("[LOGIC SUCCESS] Barber '%s', ID: '%d' removed from system.\n", current->data.name, current->data.id);
    free(current);
}

void LOGIC_DisplayWaitingQueue() {
    printf("\n--- WAITING LIST QUEUE (%d waiting) ---\n", g_customerQueue ? g_customerQueue->count : 0);
    if (g_customerQueue == NULL || g_customerQueue->front == NULL) {
        printf("The waiting list is empty.\n");
        return;
    }

    CustomerNode* temp = g_customerQueue->front;
    int pos = 1;
    while (temp != NULL) {
        printf("%d. ID: '%-4d' | Name: '%s'\n", pos++, temp->data.id, temp->data.name);
        temp = temp->next;
    }
}

void LOGIC_DisplayServingList() {
    printf("\n--- SERVING LIST  ---\n");
    if (g_servingList == NULL) {
        printf("The serving list is empty.\n");
        return;
    }

    CustomerNode* temp = g_servingList;
    int pos = 1;
    while (temp != NULL) {
        printf("%d. Customer ID: %-4d | Customer Name: %s | Assigned Barber ID: %d\n", pos++, temp->data.id, temp->data.name, temp->data.assigned_barber_id);
        temp = temp->next;
    }
}

void LOGIC_DisplayBarberList() {
    printf("\n--- BARBER LIST  ---\n");
    if (g_barberList == NULL) {
        printf("The barber list is empty.\n");
        return;
    }

    BarberNode* temp = g_barberList;
    int pos = 1;
    while (temp != NULL) {
        char buff[20];
        if (temp->data.status){
            strcpy(buff, "BUSY");
        }
        else{
            strcpy(buff, "AVAILABLE");
        }
        printf("%d. Barber ID: '%-4d' | Barber Name: '%s' | Status: '%s'\n", pos++, temp->data.id, temp->data.name, buff);
        temp = temp->next;
    }
}


