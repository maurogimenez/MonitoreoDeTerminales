#include "monitor.h"
#include "../utils/myUtils.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 10

unsigned long getSize(int mon_csd){

    int leido=0;
    char cabecera[40];
    char aux[23];
    
    memset(cabecera,'\0',40);
    memset(aux,'\0',23);

    //Leo la cabecera
    if (-1 == (leido=read(mon_csd,cabecera,40)) ) { perror("statsController:read"); return -1; }

    if ( -1 == parse("MDT rep_size [0-9]{1,22}",cabecera,13,aux) ){  //Obtengo el tamanio del reporte
        perror("getSize:parse");
        return -2;
    }

    return atol(aux);
}
