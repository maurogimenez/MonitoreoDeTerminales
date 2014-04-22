/********************Protocol***********************/
/*
@MDT@ rep_size 123123123123@@  //El tamanio siempre es 40
@TIM@hh:mm:ss@@
@CLI_S@123123@@
@CLI@FRisma-Lenovo@@
@CPU_S@123123@@
@CPU@XXXXXXXXXXXXXXXXXXXXXXXXXXX@@
@MEM_S@123123@@
@MEM@XXXXXXXXXXXXXXXXXXXXXXXXXXX@@
@HDD_S@123123@@
@HDD@XXXXXXXXXXXXXXXXXXXXXXXXXXX@@
@/MDT@
*/
#include "monitor.h"
#include "../utils/myUtils.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define debug 0

int statsController (int mon_csd){
   
    int leido=0;
    unsigned long size=0;
    char *data;

    while(1) {
        //Leo la cabecera y obtengo el tamanio del reporte
        if ( 0 >= (size=getSize(mon_csd)) ){
            size=REP_SIZE;
            printf("Error en la lectura del protocolo, se ignorará este reporte");
            return -1;  //En realidad no deberia salir, sino descartar el reporte y esperar a uno nuevo
        }
        if (debug)   printf("Size en int: %ld\n",size);
   
        if ( Malloc(&data,size) ) { return -1; }
        if (0 < (leido=read(mon_csd,data,size)) )
        getStats(data,leido);
        //semaforo decremento
        //  Escribir en la sh_mem
        //semaforo incremento
    }
    return 0;
}
