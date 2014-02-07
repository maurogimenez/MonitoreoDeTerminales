#include "monitor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROC_PATH "/proc"
#define MEM_INFO "meminfo"
#define CPU_INFO "cpuinfo"
#define HDD_INFO "diskstats"
#define UPTIME_INFO "uptime"
#define VERSION_INFO "version"
#define NET_INFO "net/..."

#define BUFF_SIZE 1000

#define debug 0  //Para que funcionen algunas cosas, debe activar debug en monitorClient.c

int getStatsController(pcInfo* thisPc){
    
            if (1 == debug)    printf("CPU: %s\n%s-->size=%d\n", thisPc->cpu,PROC_PATH,(int)strlen(PROC_PATH));
    
    char *dataPath;
    if ( NULL == ( dataPath = (char*) malloc (100) ))    { free(thisPc); return -1; } 

 
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(MEM_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)MEM_INFO) ){ 
        free(thisPc);
        perror("GetStatsController: snprintf");
        return -1; 
    }
    
            if (1 == debug) printf ("%s",dataPath);
    
    if ( 0 > getStats (dataPath, thisPc, BUFF_SIZE))  { free(thisPc); return -1; }
    //sleep(300);
    return 0;
}
