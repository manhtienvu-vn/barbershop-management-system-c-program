#ifndef COMMON_H
#define COMMON_H

#define WAITING_TIME 30

// typedef struct{
//     char name[30];
//     int id;
//     int assigned_barber_id;
//     float service_charge;
// } CustomerStr;


/**
 * @brief Customer information.
 */
typedef struct {
    int id;
    char name[20]; 
    int assigned_barber_id;
    float service_charge;
} Customer;


/**
 * @brief Working status of a barber.
 */
typedef enum {
    AVAILABLE = 0,
    BUSY = 1
} BarberStatus;


// typedef struct{
//     char name[20];
//     int id;
//     BarberStatus status;
// } BarberStr;

/**
 * @brief Barber information.
 */
typedef struct {
    int id;
    char name[20];
    BarberStatus status;
} Barber;


#endif