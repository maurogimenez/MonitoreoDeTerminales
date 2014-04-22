/*
 * send2server.c
 * Escribe en el socket, la estructura thisPc
*/
#include "monitor.h"

#include <string.h>

int send2server (pcInfo *thisPc, int sd){

    if ( 0 != Write(sd,thisPc->header,40) )                         { return -1; }
    if ( 0 != Write(sd,thisPc->time,strlen(thisPc->time)) )         { return -1; }
    if ( 0 != Write(sd,thisPc->name,strlen(thisPc->name)) )         { return -1; }
    if ( 0 != Write(sd,thisPc->mem,strlen(thisPc->mem)) )           { return -1; }
    if ( 0 != Write(sd,thisPc->cpu,strlen(thisPc->cpu)) )           { return -1; }
    if ( 0 != Write(sd,thisPc->hdd,strlen(thisPc->hdd)) )           { return -1; }
    if ( 0 != Write(sd,thisPc->uptime,strlen(thisPc->uptime)) )     { return -1; }
    if ( 0 != Write(sd,thisPc->version,strlen(thisPc->version)) )   { return -1; }
    if ( 0 != Write(sd,thisPc->issue,strlen(thisPc->issue)) )       { return -1; }
    if ( 0 != Write(sd,thisPc->end,6) )                             { return -1; }
    return 0;
}
