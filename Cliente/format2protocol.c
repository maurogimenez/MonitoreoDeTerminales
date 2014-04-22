/*
 * format2protocol.c
 * Adecua los datos contenidos en la estructura thisPC
 * al formato preestablecido por el protocolo,
 * dejando todo listo para ser enviado por el socket

********************Protocol***********************

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
#include "macros.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define debug 0

//Revisar para modificar el protocolo por uno mas versatil tipo XML

int format2protocol (pcInfo *thisPc){

    char *aux;
    if ( 0 > Malloc(&aux,LARGEST_BUFFER) ) { return -1; } 

    //Nombre
    strncpy(aux,thisPc->name,strlen(thisPc->name));
    aux[strlen(aux) -1]='\0';
    if (0 > snprintf(thisPc->name, strlen(thisPc->name)+8, "@CLI@%s@@",(char *)aux) )  {goto error;} 
    if(debug) printf("%s\n\n",thisPc->name);

    //MEM
    strncpy(aux,thisPc->mem,strlen(thisPc->mem));
    aux[strlen(aux) -1]='\0';
    if (0 > snprintf(thisPc->mem, strlen(thisPc->mem)+8, "@MEM@%s@@",(char *)aux) )    {goto error;} 
    if(debug) printf("%s\n\n",thisPc->mem);
    
    //CPU
    memset(aux,'\0',LARGEST_BUFFER);
    strncpy(aux,thisPc->cpu,strlen(thisPc->cpu));
    aux[strlen(aux) -1]='\0';
    if (0 > snprintf(thisPc->cpu, strlen(thisPc->cpu)+8, "@CPU@%s@@",(char *)aux) )    {goto error;} 
    if(debug) printf("%s\n\n",thisPc->cpu);
    
    //HDD
    memset(aux,'\0',LARGEST_BUFFER);
    strncpy(aux,thisPc->hdd,strlen(thisPc->hdd));
    aux[strlen(aux) -1]='\0';
    if (0 > snprintf(thisPc->hdd, strlen(thisPc->hdd)+8, "@HDD@%s@@",(char *)aux) )    {goto error;} 
    if(debug) printf("%s\n\n",thisPc->hdd);
    

    //UPTIME
    memset(aux,'\0',LARGEST_BUFFER);
    strncpy(aux,thisPc->uptime,strlen(thisPc->uptime));
    aux[strlen(aux) -1]='\0';
    if (0 > snprintf(thisPc->uptime, strlen(thisPc->uptime)+8, "@UPT@%s@@",(char *)aux) )     {goto error;}
    if(debug) printf("%s\n\n",thisPc->uptime);
 
    //ISSUE
    memset(aux,'\0',LARGEST_BUFFER);
    strncpy(aux,thisPc->issue,strlen(thisPc->issue));
    aux[strlen(aux) -1]='\0';
    if (0 > snprintf(thisPc->issue, strlen(thisPc->issue)+8, "@ISS@%s@@",(char *)aux) )     {goto error;}
    if(debug) printf("%s\n\n",thisPc->issue);
 

    //VERSION
    memset(aux,'\0',LARGEST_BUFFER);
    strncpy(aux,thisPc->version,strlen(thisPc->version));
    aux[strlen(aux) -1]='\0';
    if (0 > snprintf(thisPc->version, strlen(thisPc->version)+8, "@VER@%s@@",(char *)aux) )     {goto error;}
    if(debug) printf("%s\n\n",thisPc->version);

    
    //Header
    memset(thisPc->header,'X',HEADER_SIZE);
    if (0 > snprintf(thisPc->header, HEADER_SIZE, "@MDT@ rep_size %ld@@",(long)(strlen(thisPc->mem)+ strlen(thisPc->hdd)+strlen(thisPc->cpu)+strlen(thisPc->uptime)+strlen(thisPc->version)+strlen(thisPc->issue))) )     {goto error;}
    if(debug) printf("%s\n\n",thisPc->header);
   
    //Time
    strncpy(aux,thisPc->time,strlen(thisPc->time));
    memset(thisPc->header,'X',HEADER_SIZE);
    if (0 > snprintf(thisPc->time, strlen(thisPc->time)+8, "@TIM@%s@@",(char *)aux) )     {goto error;}
    if(debug) printf("%s\n\n",thisPc->time);

    //Final
    if (0 > snprintf(thisPc->end, END_SIZE, "@/MDT@") )     {goto error;}
    if(debug) printf("%s\n\n",thisPc->end);
    
    return 0;

    error:
        free(aux);
        perror("format2protocol:snprintf");
        return -1;
}
