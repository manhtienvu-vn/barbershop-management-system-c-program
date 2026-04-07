#include "database.h"
#include <stdio.h>

void DATA_CreateFiles(){
    FILE* file;
    
    /* Check if the file named 'customer_checkout.csv' exists*/
    file = fopen("customer_checkout.csv", "r");

    if(file == NULL){
        /* If the given name file does not exist, create a new file*/
        fopen("customer_checkout.csv", "w");
    }

    /* Check if the file named 'customer_waiting_list.csv' exists*/
    file = fopen("customer_waiting_list.csv", "r");

    if(file == NULL){
        /* If the given name file does not exist, create a new file*/
        fopen("customer_waiting_list.csv", "w");
    }
}

