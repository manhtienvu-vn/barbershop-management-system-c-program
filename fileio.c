#include "fileio.h"

extern CustomerQueue* g_customerQueue;
extern BarberNode* g_barberList;

static void get_current_time_string(char* buffer, int buffer_size){
    /* Get the number of seconds from 1900 to now*/
    time_t rawtime;
    time(&rawtime);

    /* Convert seconds to format (Day Month Year) with struct tm*/
    struct tm *timeinfo;
    timeinfo = localtime(&rawtime);

    /* Format time value to a string*/
    strftime(buffer, buffer_size, "%d/%m/%Y %H:%M:%S", timeinfo);
}

void IO_SaveCustomerToCheckoutFiles(CustomerNode* node){
    FILE* file;
    file = fopen("checkout_history.csv", "r");

    if (file == NULL){
        /* Create a new file if it does not exist*/
        file = fopen("checkout_history.csv", "w");
        if(file == NULL){
            printf("[ERROR]: Cannot save customer info to CHECKOUT file. File is currently opened.\n");
            return;
        }
        /* Create Table Header in CSV File*/
        fprintf(file, "[Customer ID], [Customer Name], [Service Charge]\n");
        if(ferrror(file)){
            printf("[ERROR]: Error writing to CHECKOUT file.\n");
            return;
        }
    }
    else {
        file = fopen("checkout_history.csv", "a");
    }

    char checkout_time[30];
    get_current_time_string(checkout_time, sizeof(checkout_time));

    fprintf(file, "%d, %s, %f, %s\n", 
            node->data.id,
            node->data.name,
            node->data.service_charge,
            checkout_time);

    if (ferror(file)){
        printf("[ERROR]: Error writing to file.\n");
        return;
    } 
    printf("[CHECKOUT] Successfully checkout for Customer: %s.\n", node->data.name);   
}

void IO_SaveCustomerToWaitingListFile(CustomerNode* new_node){
    FILE* file;
    file = fopen("waiting_list.csv", "r");

    if (file == NULL){
        /* Create a new file if it does not exist*/
        file = fopen("waiting_list.csv", "w");
        if (file == NULL){
            printf("[ERROR]: Cannot open WAITING-LIST file. File is currently opened.\n");
            return;
        }
        /* Create Table Header in CSV File*/
        fprintf(file, "[Customer ID], [Customer Name]\n");
        if (ferrror(file)){
            printf("[ERROR]: Error writing to WAITING-LIST file.\n");
            return;
        }
    }
    else {
        /* If file already exists, append new info to it*/
        file = fopen("waiting_list.csv", "a");
    }

    fprintf(file, "%d, %s\n", 
            new_node->data.id,
            new_node->data.name);

    if(ferror(file)){
        printf("[ERROR]: Error writing to WAITING-LIST file.\n");
        return;
    } 

    printf("[WAITING-LIST] Successfully add to waiting list customer: %s.\n", new_node->data.name);   
}


void IO_RemoveCustomerFromWaitingListFile(CustomerNode* node){
    /* Method: Create a new file and copy all customer's info
    from the waiting_list.csv file, except to the to-be-removed customer*/
    FILE* file;
    if(g_customerQueue == NULL){
        printf("[ERROR] Customer waiting list is empty.\n");
        return;
    }

    file = fopen("waiting_list.csv", "w");
    if(file == NULL){
        printf("[ERROR]: Cannot open WAITING-LIST file. File is currently opened.\n");
        return;
    }
    fprintf(file, "[Customer ID], [Customer Name]\n");

    CustomerNode *temp = g_customerQueue;
    while(temp != NULL){
        if(strcmp(node->data.name, temp->data.name) && (temp->data.id == node->data.id)){
            /* Skip this barber*/
            temp = temp->next;
        }
        else{
            fprintf(file, "%d, %s, %d\n", 
            temp->data.id,
            temp->data.name,
            temp->data.status);

            if(ferror(file)){
                printf("[ERROR]: Error writing to BARBER-LIST file.\n");
                return;
            } 
        }
    }
}

void IO_SaveCustomerToServingListFile(CustomerNode* node){
    FILE* file;
    file = fopen("serving_list.csv", "a");

    if(file == NULL){
        printf("[ERROR]: Cannot save customer info to CHECKOUT file. File is currently opened.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0){
        /* If the file is empty, create Table Header */
        fprintf(file, "[Customer ID], [Customer Name], [Assigned Barber ID]\n");
    }

    char start_time[30];
    get_current_time_string(start_time, sizeof(start_time));

    fprintf(file, "%d, %s, %d, %s\n", 
            node->data.id,
            node->data.name,
            node->data.assigned_barber_id,
            start_time);

    if (ferror(file)){
        printf("[ERROR]: Error writing to file.\n");
        return;
    }
    
    fclose(file);
    printf("[SERVICE] Start service for Customer: %s.\n", node->data.name);   
}


void IO_SaveBarberToListFile(BarberNode* new_node){
    FILE* file;
    file = fopen("barber_list.csv", "r");

    if(file == NULL){
        /* Create a new file if it does not exist*/
        file = fopen("barber_list.csv", "w");
        if(file == NULL){
            printf("[ERROR]: Cannot open BARBER-LIST file. File is currently opened.\n");
            return;
        }
        /* Create Table Header in CSV File*/
        fprintf(file, "[Barber ID], [Barber Name], [Status]\n");
        if(ferrror(file)){
            printf("[ERROR]: Error writing to BARBER-LIST file.\n");
            return;
        }
    }
    else{
        /* If file already exists, append new info to it*/
        file = fopen("barber_list.csv", "a");
    }

    fprintf(file, "%d, %s, %d\n", 
        new_node->data.id,
        new_node->data.name,
        new_node->data.status);

    if(ferror(file)){
        printf("[ERROR]: Error writing to BARBER-LIST file.\n");
        return;
    } 
    printf("[BARBER-LIST] Successfully add to barber list: %s.\n", new_node->data.name);  
}


void IO_RemoveBarberFromListFile(BarberNode* node){
    /* Method: Create a new file and copy all barber's info
    from the barber_list.csv file, except to the to-be-removed barber*/
    FILE* file;
    if(g_barberList == NULL){
        printf("[ERROR] Barber list is empty.\n");
        return;
    }

    file = fopen("barber_list.csv", "w");
    if(file == NULL){
        printf("[ERROR]: Cannot open BARBER-LIST file. File is currently opened.\n");
        return;
    }
    fprintf(file, "[Barber ID], [Barber Name], [Status]\n");

    BarberNode *temp = g_barberList;
    while(temp != NULL){
        if(strcmp(temp->data.name, node->data.name) == 0 && (temp->data.id == node->data.id)){
            /* Skip this barber*/
            temp = temp->next;
        }
        else{
            fprintf(file, "%d, %s, %d\n", 
            temp->data.id,
            temp->data.name,
            temp->data.status);

            if(ferror(file)){
                printf("[ERROR]: Error writing to BARBER-LIST file.\n");
                return;
            } 
        }
    }
}

void IO_UpdateBarberStatusToListFile(BarberNode* node, BarberStatus status){
    /* Method: Create a new file and copy all barber's info
    from the barber_list.csv file, update status of the to-be-updated barber*/
    FILE* file;
    if(g_barberList == NULL){
        printf("[ERROR] Barber list is empty.\n");
        return;
    }

    file = fopen("barber_list.csv", "w");
    if(file == NULL){
        printf("[ERROR]: Cannot open BARBER-LIST file. File is currently opened.\n");
        return;
    }
    fprintf(file, "[Barber ID], [Barber Name], [Status]\n");

    BarberNode *temp = g_barberList;
    int check = 0;

    while(temp != NULL){
        if(strcmp(temp->data.name, node->data.name) == 0 && (temp->data.id == node->data.id)){
            /* Update this barber's status*/
            temp->data.status = status;
            check = 1;
            printf("[BARBER-LIST] Successfully update barber's status.\n");
        }

        fprintf(file, "%d, %s, %d\n", 
        temp->data.id,
        temp->data.name,
        temp->data.status);
        temp = temp->next;

        if(ferror(file)){
            printf("[ERROR]: Error writing to BARBER-LIST file.\n");
            return;
        }
    }

    if (check == 0){
        printf("[ERROR] To-be-updated Barber does not exist.\n");
    }
}




