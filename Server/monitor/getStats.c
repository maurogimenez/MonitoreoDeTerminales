#include "monitor.h"

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define debug 0

int getStats(char *token, int leido){

    if (debug)  printf("Token: %s",token);
    
    if (strstr(token,"CLI:")){
        puts("CLI");
        return 0;
    }else if (strstr(token,"MEM:")){
        puts("MEM");
        return 0;
    }else if (strstr(token,"CPU:")){
        puts("HDD");
        return 0;
    }else if (strstr(token,"HDD:")){
        puts("ISS");
        return 0;
    }else if(strstr(token,"UPT:")){
        puts("VER");
        return 0;
    }else if(strstr(token,"VER:")){
        puts("CPU");
        return 0;
    }else if(strstr(token,"ISS:")){
        puts("UPT");
        return 0;
    }else if(strstr(token,"/MDT")){
        puts("/MDT");
        return 0;
    }else
        return -1;   

}
