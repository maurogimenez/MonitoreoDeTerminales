#include "monitor.h"
#include "macros.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define debug 0  //Para que funcionen algunas cosas, debe activar debug en monitorClient.c

int getStatsController(pcInfo* thisPc){
    
    char *dataPath;
    char *nombre;
    if ( 0 > Malloc(&dataPath,100) )        { return -1; }
    if ( 0 > Malloc(&nombre,NAME_SIZE) )    { return -1; }
    
    //NOMBRE
    if (0 > gethostname(nombre,NAME_SIZE))  {perror("gethostname"); return -1;}
    if (0 > snprintf(thisPc->name, strlen(nombre)+3, "%s\r\n", (char *)nombre) ){ 
        perror("getStatsController: snprintf");
        return -1; 
    }   

    //MEM_INFO
    memset(dataPath,'\0', 100);
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(MEM_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)MEM_INFO) ){ 
        perror("getStatsController: snprintf");
        return -1; 
    }   
    if ( 0 > getStats (dataPath,&thisPc->mem, BUFF_SIZE))  { return -1; }
  
    //CPU_INFO
    memset(dataPath,'\0', 100);
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(CPU_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)CPU_INFO) ){
         perror("getStatsController: snprintf");
         return -1;
    }
    if ( 0 > getStats (dataPath,&thisPc->cpu, BUFF_SIZE))  { return -1; }
    
    //HDD_INFO
    memset(dataPath,'\0', 100);
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(HDD_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)HDD_INFO) ){
          perror("getStatsController: snprintf");
          return -1;
    }
    if ( 0 > getStats (dataPath, &thisPc->hdd, BUFF_SIZE))  { return -1; }

    //UPTIME_INFO
    memset(dataPath,'\0', 100);
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(UPTIME_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)UPTIME_INFO) ){
          perror("getStatsController: snprintf");
          return -1;
    } 
    if ( 0 > getStats (dataPath, &thisPc->uptime, BUFF_SIZE))  { return -1; }

    //VERSION_INFO
    memset(dataPath, '\0', 100);
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(VERSION_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)VERSION_INFO) ){
          perror("getStatsController: snprintf");
          return -1;
    }
    if ( 0 > getStats (dataPath, &thisPc->version, BUFF_SIZE))  { return -1; }
        
    //OS_INFO
    memset(dataPath, '\0', 100);
    if (0 > snprintf(dataPath, strlen(ETC_PATH)+strlen(OS_INFO)+2, "%s/%s", (char *)ETC_PATH, (char *)OS_INFO) ){
          perror("getStatsController: snprintf");
          return -1;
    }
    if ( 0 > getStats (dataPath, &thisPc->issue, BUFF_SIZE))  { return     -1; }


    if (debug){   
       puts ("Estoy en getStatsController.c");
       printf("HOSTNAME: %s\n", thisPc->name);
       printf("MEMINFO: %s\n", thisPc->mem);
       printf("CPUINFO: %s\n", thisPc->cpu);
       printf("HDDINFO: %s\n", thisPc->hdd);
       printf("UPTIMEINFO: %s\n", thisPc->uptime);
       printf("VERSIONINFO: %s\n", thisPc->version);
       printf("OSINFO: %s\n", thisPc->issue);
    }
    return 0;
}
