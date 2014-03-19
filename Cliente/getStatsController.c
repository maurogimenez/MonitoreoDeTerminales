#include "monitor.h"
#include "macros.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define debug 0

int getStatsController(pcInfo* thisPc){
    
    if (debug)  puts("getStatsController.c");
    
    char *dataPath;
    char *nombre;
    if ( 0 > Malloc(&dataPath,100) )        { return -1; }
    if ( 0 > Malloc(&nombre,NAME_SIZE) )    { return -1; }
    
    //NOMBRE_PC********
    memset(thisPc->name,'\0', NAME_SIZE);
    if (0 > gethostname(nombre,NAME_SIZE))  {perror("gethostname"); goto error;}
    if (0 > snprintf(thisPc->name, strlen(nombre)+3, "%s\r\n", (char *)nombre))    {perror("snprintf");goto error;} 
    if (debug)  printf("NOMBRE\n%s\n",thisPc->name);

    //MEM_INFO**********
    memset(dataPath,'\0', 100);
    memset(thisPc->mem,'\0', MEM_SIZE);
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(MEM_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)MEM_INFO)){perror("snprintf");goto error;}
    if (0 > getStats (dataPath,&thisPc->mem, BUFF_SIZE))  {goto error;}
    if (debug)  printf("MEMINFO\n%s\n",thisPc->mem);
  
    //CPU_INFO************
    memset(dataPath,'\0', 100);
    memset(thisPc->cpu,'\0', CPU_SIZE);
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(CPU_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)CPU_INFO)){perror("snprintf");goto error;}
    if ( 0 > getStats (dataPath,&thisPc->cpu, BUFF_SIZE))  {goto error;}
    if (debug)  printf("CPUINFO\n%s\n",thisPc->cpu);
    
    //HDD_INFO***********
    memset(dataPath,'\0', 100);
    memset(thisPc->hdd,'\0', HDD_SIZE);
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(HDD_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)HDD_INFO)){perror("snprintf");goto error;}
    if (0 > getStats (dataPath, &thisPc->hdd, BUFF_SIZE))  {goto error;}
    if (debug)  printf("HDDINFO\n%s\n",thisPc->hdd);

    //UPTIME_INFO**********
    memset(dataPath,'\0', 100);
    memset(thisPc->uptime,'\0', UPTIME_SIZE);
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(UPTIME_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)UPTIME_INFO)){perror("snprintf");goto error;}
    if (0 > getStats (dataPath, &thisPc->uptime, BUFF_SIZE))  {goto error;}
    if (debug)  printf("UPTIMEINFO\n%s\n",thisPc->uptime);

    //VERSION_INFO************
    memset(dataPath, '\0', 100);
    memset(thisPc->version,'\0', VERSION_SIZE);
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(VERSION_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)VERSION_INFO)){perror("snprintf");goto error;}
    if (0 > getStats (dataPath, &thisPc->version, BUFF_SIZE))  {goto error;}
    if (debug)  printf("VERSIONINFO\n%s\n",thisPc->version);
        
    //OS_INFO*************
    memset(dataPath, '\0', 100);
    memset(thisPc->issue,'\0', ISSUE_SIZE);
    if (0 > snprintf(dataPath, strlen(ETC_PATH)+strlen(OS_INFO)+2, "%s/%s", (char *)ETC_PATH, (char *)OS_INFO)){perror("snprintf");goto error;}
    if (0 > getStats (dataPath, &thisPc->issue, BUFF_SIZE))  {goto error;}
    if (debug)  printf("ISUUEINFO\n%s\n",thisPc->issue);

    free(nombre);
    free(dataPath);
    return 0;

    error:
        puts("getStatsController");
        free(nombre);
        free(dataPath);
        return -1;
}
