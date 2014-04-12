#include "monitor.h"
#include "../utils/myUtils.h"

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define debug 0

int getStats(char *buffer, int leido){

    if (debug)  printf("Token: %s",buffer);
    char aux[5000];

    parse("CLI:.*[\r\n]",buffer,0,aux);
    if (strstr(aux,"CLI:")){
        puts("CLI");
    }

    parse("MEM:.*[\r\n]",buffer,0,aux);
    if (strstr(aux,"MEM:")){
        puts("MEM");
    }
    
    parse("CPU:.*[\r\n]",buffer,0,aux);
    if (strstr(aux,"CPU:")){
        puts("CPU");
    }
    
    parse("HDD:.*[\r\n]",buffer,0,aux);
    if (strstr(aux,"HDD:")){
        puts("HDD");
    }
    
    parse("UPT:.*[\r\n]",buffer,0,aux);
    if(strstr(aux,"UPT:")){
        puts("UPT");
    }
    
    parse("VER:.*[\r\n]",buffer,0,aux);
    if(strstr(aux,"VER:")){
        puts("VER");
    }
    
    parse("ISS:.*[\r\n]",buffer,0,aux);
    if(strstr(aux,"ISS:")){
        puts("ISS");
    }
    
    parse("/MDT:.*[\r\n]",buffer,0,aux);
    if(strstr(aux,"/MDT")){
        puts("/MDT");
    }

    return 0;

}
