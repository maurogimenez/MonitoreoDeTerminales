#include <semaphore.h>

#ifndef MONITOR_H_
    #define MONITOR_H_

    typedef struct shared{      //Estructura de la memoria compartida
        int intentos;
        sem_t *sem1;
        char first_mem[3000];
        sem_t *sem2;
        char second_mem[3000];
        sem_t *sem3;
        char third_mem[3000];
    }shared;

    int statsController(int mon_csd);
    unsigned long getSize(int mon_csd); //Lee el header del protocolo para obtener el size del reporte
    int getStats(char *token,int leido);

#endif
