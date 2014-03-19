#include "monitor.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define debug 0

int format2protocol (pcInfo *thisPc){

    char *aux;
    if ( 0 > Malloc(&aux,4000) ) { return -1; } 

    //Nombre
    strncpy(aux,thisPc->name,strlen(thisPc->name));
    aux[strlen(aux) -1]='\0';
    if (0 > snprintf(thisPc->name, strlen(thisPc->name)+7, "CLI:%s\r\n",(char *)aux) ){ 
        perror("format2protocol:snprintf");
        return -1; 
    }
    if(debug) printf("%s\n\n",thisPc->name);

    //modificar MEM
    strncpy(aux,thisPc->mem,strlen(thisPc->mem));
    aux[strlen(aux) -1]='\0';
    if (0 > snprintf(thisPc->mem, strlen(thisPc->mem)+7, "MEM:%s\r\n",(char *)aux) ){ 
        perror("format2protocol:snprintf");
        return -1; 
    }
    if(debug) printf("%s\n\n",thisPc->mem);
    
    //modificar CPU
    memset(aux,'\0',4000);
    strncpy(aux,thisPc->cpu,strlen(thisPc->cpu));
    aux[strlen(aux) -1]='\0';
    if (0 > snprintf(thisPc->cpu, strlen(thisPc->cpu)+7, "CPU:%s\r\n",(char *)aux) ){ 
        perror("format2protocol:snprintf");
        return -1; 
    }
    if(debug) printf("%s\n\n",thisPc->cpu);
    
    //modificar HDD
    memset(aux,'\0',4000);
    strncpy(aux,thisPc->hdd,strlen(thisPc->hdd));
    aux[strlen(aux) -1]='\0';
    if (0 > snprintf(thisPc->hdd, strlen(thisPc->hdd)+7, "HDD:%s\r\n",(char *)aux) ){ 
        perror("format2protocol:snprintf");
        return -1; 
    }
    if(debug) printf("%s\n\n",thisPc->hdd);
    

    //modificar UPTIME
    memset(aux,'\0',4000);
    strncpy(aux,thisPc->uptime,strlen(thisPc->uptime));
    aux[strlen(aux) -1]='\0';
    if (0 > snprintf(thisPc->uptime, strlen(thisPc->uptime)+7, "UPT:%s\r\n",(char *)aux) ){ 
        perror("format2protocol:snprintf");
        return -1; 
    }
    if(debug) printf("%s\n\n",thisPc->uptime);
 
    //modificar ISSUE
    memset(aux,'\0',4000);
    strncpy(aux,thisPc->issue,strlen(thisPc->issue));
    aux[strlen(aux) -1]='\0';
    if (0 > snprintf(thisPc->issue, strlen(thisPc->issue)+7, "ISS:%s\r\n",(char *)aux) ){ 
        perror("format2protocol:snprintf");
        return -1; 
    }
    if(debug) printf("%s\n\n",thisPc->issue);
 

    //modificar VERSION
    memset(aux,'\0',4000);
    strncpy(aux,thisPc->version,strlen(thisPc->version));
    aux[strlen(aux) -1]='\0';
    if (0 > snprintf(thisPc->version, strlen(thisPc->version)+7, "VER:%s\r\n",(char *)aux) ){ 
        perror("format2protocol:snprintf");
        return -1; 
    }
    if(debug) printf("%s\n\n",thisPc->version);

    
    //Header
    memset(thisPc->header,'X',40);
    if (0 > snprintf(thisPc->header, 40, "MDT rep_size %ld\r\n",(long)(strlen(thisPc->mem)+ strlen(thisPc->hdd)+strlen(thisPc->cpu)+strlen(thisPc->uptime)+strlen(thisPc->version)+strlen(thisPc->issue))) ){ 
        perror("format2protocol:snprintf");
        return -1; 
    }
    if(debug) printf("%s\n\n",thisPc->header);
   
    //Final
    if (0 > snprintf(thisPc->end, 5, "/MDT%c",4) ){ 
        perror("format2protocol:snprintf");
        return -1; 
    }
    if(debug) printf("%s\n\n",thisPc->end);
    
    return 0;

}
