#include "fileio.h"

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

void IO_SaveCustomerToWaitingListFile(Customer customer){
    FILE* file;
    file = fopen("waiting_list.csv", "a");

    if(file == NULL){
        printf("[IO ERROR]: Cannot save customer info to WAITING-LIST file. File is currently opened.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0){
        /* If the file is empty, create Table Header */
        fprintf(file, "Customer ID, Customer Name\n");
    }

    fprintf(file, "%d, %s\n", customer.id, customer.name);

    if(ferror(file)){
        printf("[IO ERROR]: Error writing to WAITING-LIST file.\n");
        fclose(file);
        return;
    } 
    fclose(file);
    printf("[IO SUCCESS] Added to waiting list customer: '%s', ID: '%d'.\n", customer.name, customer.id);   
}


void IO_RemoveCustomerFromWaitingListFile(Customer customer){
    /* Method: Create a new file and copy all customer's info
    from the waiting_list.csv file, except to the to-be-removed customer*/
    FILE* file;
    if(g_customerQueue == NULL){
        printf("[ERROR] Customer waiting list is empty.\n");
        return;
    }

    /* Create a totally new file to write data */
    file = fopen("waiting_list.csv", "w");
    if(file == NULL){
        printf("[ERROR]: Cannot open WAITING-LIST file. File is currently opened.\n");
        return;
    }
    fprintf(file, "Customer ID, Customer Name\n");

    CustomerNode *temp = g_customerQueue->front;
    while(temp != NULL){
        if(strcmp(customer.name, temp->data.name) == 0 && (temp->data.id == customer.id)){
            /* Skip this customer*/
            temp = temp->next;
            continue;
        }
        fprintf(file, "%d, %s\n", 
        temp->data.id,
        temp->data.name);
        /* Proceed to the next customer node */
        temp = temp->next;
    }
    fclose(file);
}

void IO_SaveCustomerToServingListFile(Customer customer){
    FILE* file;
    file = fopen("serving_list.csv", "a");

    if(file == NULL){
        printf("[IO ERROR]: Cannot save customer info to CHECKOUT file. File is currently opened.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0){
        /* If the file is empty, create Table Header */
        fprintf(file, "Customer ID, Customer Name, Assigned Barber ID\n");
    }

    char start_time[30];
    get_current_time_string(start_time, sizeof(start_time));

    fprintf(file, "%d, %s, %d, %s\n", customer.id, customer.name, customer.assigned_barber_id, start_time);

    if (ferror(file)){
        printf("[IO ERROR]: Error writing to SERVING-LIST file.\n");
        fclose(file);
        return;
    }
    fclose(file);
}


void IO_SaveCustomerToCheckoutFiles(Customer customer){
    FILE* file;
    file = fopen("checkout.csv", "a");

    if(file == NULL){
        printf("[IO ERROR]: Cannot save customer info to CHECKOUT file. File is currently opened.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0){
        /* If the file is empty, create Table Header */
        fprintf(file, "Customer ID, Customer Name, Service Charge\n");
    }

    char checkout_time[30];
    get_current_time_string(checkout_time, sizeof(checkout_time));
    customer.service_charge = 80000;
    
    fprintf(file, "%d, %s, %f, %s\n", customer.id, customer.name, customer.service_charge, checkout_time);

    if (ferror(file)){
        printf("[IO ERROR]: Error writing to file.\n");
        fclose(file);
        return;
    } 
    fclose(file);
    printf("[IO SUCCESS] Checked out for Customer: '%s', ID: '%d'.\n", customer.name, customer.id);   
}

void IO_SaveBarberToListFile(Barber barber){
    FILE* file;
    file = fopen("barber_list.csv", "a");

    if(file == NULL){
        printf("[IO ERROR]: Cannot open BARBER-LIST file. File is currently opened.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0){
        /* If the file is empty, create Table Header */
        fprintf(file, "Barber ID, Barber Name, Status\n");
    }

    fprintf(file, "%d, %s, %d\n", barber.id, barber.name, (int)(barber.status));

    if(ferror(file)){
        printf("[IO ERROR]: Error writing to BARBER-LIST file.\n");
        fclose(file);
        return;
    } 
    fclose(file);
    printf("[IO SUCCESS] Added barber '%s', ID: '%d' barber list.\n", barber.name, barber.id);  
}

void IO_RemoveBarberFromListFile(Barber barber){
    /* Method: Create a new file and copy all barber's info
    from the barber_list.csv file, except to the to-be-removed barber*/
    FILE* file;
    if(g_barberList == NULL){
        printf("[IO ERROR] Barber list is empty.\n");
        return;
    }

    file = fopen("barber_list.csv", "w");
    if(file == NULL){
        printf("[IO ERROR]: Cannot open BARBER-LIST file. File is currently opened.\n");
        return;
    }
    fprintf(file, "Barber ID, Barber Name, Status\n");

    BarberNode *temp = g_barberList;
    while(temp != NULL){
        if(strcmp(temp->data.name, barber.name) == 0 && (temp->data.id == barber.id)){
            /* Skip this barber*/
            temp = temp->next;
        }
        else{
            fprintf(file, "%d, %s, %d\n", temp->data.id, temp->data.name, (int)(temp->data.status));

            if(ferror(file)){
                printf("[IO ERROR]: Error writing to BARBER-LIST file.\n");
                fclose(file);
                return;
            } 
        }
    }
    fclose(file);
}

void IO_UpdateBarberStatusToListFile(Barber barber){
    /* Method: Create a new file and copy all barber's info
    from the barber_list.csv file, update status of the to-be-updated barber*/
    FILE* file;
    if(g_barberList == NULL){
        printf("[IO ERROR] Barber list is empty.\n");
        return;
    }

    file = fopen("barber_list.csv", "w");
    if(file == NULL){
        printf("[IO ERROR]: Cannot open BARBER-LIST file. File is currently opened.\n");
        return;
    }
    fprintf(file, "Barber ID, Barber Name, Status\n");

    BarberNode *temp = g_barberList;
    int check = 0;

    while(temp != NULL){
        if(strcmp(temp->data.name, barber.name) == 0 && (temp->data.id == barber.id)){
            /* Update this barber's status*/
            temp->data.status = barber.status;
            check = 1;
            printf("[IO SUCCESS] Updated barber's status.\n");
        }

        fprintf(file, "%d, %s, %d\n", temp->data.id, temp->data.name, (int)(temp->data.status));

        temp = temp->next;

        if(ferror(file)){
            printf("[IO ERROR]: Error writing to BARBER-LIST file.\n");
            fclose(file);
            return;
        }
    }

    if (check == 0){
        printf("[ERROR] Barber does not exist.\n");
    }
    fclose(file);
}

void IO_ViewCheckoutHistory(){
    FILE* file;
    file = fopen("checkout.csv", "r");

    if (file == NULL){
        printf("[IO ERROR] CHECKOUT file does not exist.");
        return;
    }

    printf("\n--- CHECKOUT HISTORY ---\n");
    /* Skip the table header line */
    char buffer[255];
    fgets(buffer, sizeof(buffer), file);

    Customer customer;
    char time_stamp[30];
    int count = 1;

    while (fscanf(file, "%d, %[^,], %f, %[^\n]\n", &customer.id, customer.name, &customer.service_charge, time_stamp) == 4){
        printf("%d. [%s] Customer ID: '%-4d' | Customer Name: '%-15s' | Service Charge: '%.0f' VND\n", 
               count++, time_stamp, customer.id, customer.name, customer.service_charge);
    }
    printf("================================================================\n");
    fclose(file);
}

void IO_RefreshWaitingListFile(){
    FILE* file;
    file = fopen("waiting_list.csv", "w");
    fclose(file);
}

void IO_RefreshServingListFile(){
    FILE* file;
    file = fopen("serving_list.csv", "w");
    fclose(file);
}

void IO_RefreshBarberListFile(){
    FILE* file;
    file = fopen("barber_list.csv", "w");
    fclose(file);
}

void IO_RefreshAllFiles(){
    FILE* file1;
    FILE* file2;
    FILE* file3;
    file1 = fopen("waiting_list.csv", "w");
    file2 = fopen("serving_list.csv", "w");
    file3 = fopen("barber_list.csv", "w");
    fclose(file1);
    fclose(file2);
    fclose(file3);
}




