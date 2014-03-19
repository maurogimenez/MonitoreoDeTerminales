/*
********************Protocol***********************
MDT rep_size XXXXXXXXXXXXXXXXX\r\n  //El tamanio siempre es 40
CLI:FRisma-Lenovo\r\n
CPU:XXXXXXXXXXXXXXXXXXXXXXXXXXX\r\n
MEM:XXXXXXXXXXXXXXXXXXXXXXXXXXX\r\n
HDD:XXXXXXXXXXXXXXXXXXXXXXXXXXX\r\n
/MDT'EOT'
*/
#include "monitor.h"
#include "../utils/myUtils.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define REP_SIZE 5600  //Default report size en caso de que no se pueda leer la cabecera

#define debug 0

int statsController (int mon_csd){
   
    int leido=0;
    unsigned long size=0;
    char *aux;
    char data[2000];
    char *buffer;

    memset(data,'\0',2000);
    if ( Malloc(&aux,5000) ) { return -1; }
    
    //Leo la cabecera y obtengo el tamanio del reporte
    if ( 0 >= (size=getSize(mon_csd)) ){
        size=REP_SIZE;
        printf("No se pudo establecer el tamanio del reporte. Se asume %d por defecto",REP_SIZE);
    }
    if(debug)   printf("Size en int: %ld\n",size);
   
    if ( Malloc(&buffer,size) ) { return -1; }
    
    //Leo el socket en busca de la informacion
    while((leido = read(mon_csd,buffer,size)) > 0){
        //puts("PASADA");
        write(STDOUT_FILENO,buffer,leido);
        memset(aux,'\0',5000);
        //parse(".*[\r\n]$",buffer,0,aux);
        //getStats(aux,leido);
        //semaforo decremento
        //  Escribir en la sh_mem
        //semaforo incremento

    }
    return 0;
}
