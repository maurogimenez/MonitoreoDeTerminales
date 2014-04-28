/*
 *getStatsController.c
Esta funcion arma las rutas del /proc/'algo',
y pasa el control a getStats() quien lee del archivo
y lo guarda en la estructura thisPC.
Se itera este proceso hasta que se hayan leido todos
los /proc/'algo'.
Por otro lado, tambien llena la estructura thisPC con
el nombre de la PC y la hora actual.
*
*/

#include "monitor.h"
#include "macros.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define debug 0

int getStatsController(pcInfo* thisPc){
    
    char *dataPath;
    char *nombre;

    time_t rawtime;
    struct tm* timeinfo;

    if ( 0 > Malloc(&dataPath,100) )        { return -1; }
    if ( 0 > Malloc(&nombre,NAME_SIZE) )    { return -1; }
    
    //NOMBRE_PC*******
    memset(thisPc->name,'\0', NAME_SIZE);
    if (0 > gethostname(nombre,NAME_SIZE))  {perror("gethostname"); goto error;}
    if (0 > snprintf(thisPc->name, strlen(nombre)+1, "%s", (char *)nombre))    {perror("snprintf");goto error;} 
    if (debug)  printf("NOMBRE\n%s\n",thisPc->name);

    //CLI_S
    memset(thisPc->name_size,'\0',DEFAULT_LENGTH);
    snprintf(thisPc->name_size,strlen(thisPc->name),"%d",(int)strlen(thisPc->name));

    
    //TIME********
    memset(thisPc->time,'\0', TIME_SIZE);
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if (0 > snprintf(thisPc->time, TIME_SIZE, "%s", asctime(timeinfo)))    {perror("snprintf");goto error;} 
    if (debug)  printf("TIME\n%s\n",thisPc->time);

    
    //MEM_INFO**********
    memset(dataPath,'\0', 100);
    memset(thisPc->mem,'\0', MEM_SIZE);
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(MEM_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)MEM_INFO)){perror("snprintf");goto error;}
    if (0 > getStats (dataPath,&thisPc->mem, BUFF_SIZE))  {goto error;}
    if (debug)  printf("MEMINFO\n%s\n",thisPc->mem);
    
    //MEM_S
    memset(thisPc->mem_size,'\0',DEFAULT_LENGTH);
    snprintf(thisPc->mem_size,strlen(thisPc->mem),"%d",(int)strlen(thisPc->mem));
  
    
    //CPU_INFO************
    memset(dataPath,'\0', 100);
    memset(thisPc->cpu,'\0', CPU_SIZE);
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(CPU_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)CPU_INFO)){perror("snprintf");goto error;}
    if ( 0 > getStats (dataPath,&thisPc->cpu, BUFF_SIZE))  {goto error;}
    if (debug)  printf("CPUINFO\n%s\n",thisPc->cpu);

    //CPU_S  
    memset(thisPc->cpu_size,'\0',DEFAULT_LENGTH);
    snprintf(thisPc->cpu_size,strlen(thisPc->cpu),"%d",(int)strlen(thisPc->cpu));
   
    
    //HDD_INFO***********
    memset(dataPath,'\0', 100);
    memset(thisPc->hdd,'\0', HDD_SIZE);
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(HDD_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)HDD_INFO)){perror("snprintf");goto error;}
    if (0 > getStats (dataPath, &thisPc->hdd, BUFF_SIZE))  {goto error;}
    if (debug)  printf("HDDINFO\n%s\n",thisPc->hdd);

    //HDD_S
    memset(thisPc->hdd_size,'\0',DEFAULT_LENGTH);
    snprintf(thisPc->hdd_size,strlen(thisPc->hdd),"%d",(int)strlen(thisPc->hdd));
 
    
    //UPTIME_INFO**********
    memset(dataPath,'\0', 100);
    memset(thisPc->uptime,'\0', UPTIME_SIZE);
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(UPTIME_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)UPTIME_INFO)){perror("snprintf");goto error;}
    if (0 > getStats (dataPath, &thisPc->uptime, BUFF_SIZE))  {goto error;}
    if (debug)  printf("UPTIMEINFO\n%s\n",thisPc->uptime);
    
    //UPTIME_S
    memset(thisPc->uptime_size,'\0',DEFAULT_LENGTH);
    snprintf(thisPc->uptime_size,strlen(thisPc->uptime),"%d",(int)strlen(thisPc->uptime));


    //VERSION_INFO************
    memset(dataPath, '\0', 100);
    memset(thisPc->version,'\0', VERSION_SIZE);
    if (0 > snprintf(dataPath, strlen(PROC_PATH)+strlen(VERSION_INFO)+2, "%s/%s", (char *)PROC_PATH, (char *)VERSION_INFO)){perror("snprintf");goto error;}
    if (0 > getStats (dataPath, &thisPc->version, BUFF_SIZE))  {goto error;}
    if (debug)  printf("VERSIONINFO\n%s\n",thisPc->version);
    
    //VERSION_S
    memset(thisPc->version_size,'\0',DEFAULT_LENGTH);
    snprintf(thisPc->version_size,strlen(thisPc->version),"%d",(int)strlen(thisPc->version));

       
    //OS_INFO*************
    memset(dataPath, '\0', 100);
    memset(thisPc->issue,'\0', ISSUE_SIZE);
    if (0 > snprintf(dataPath, strlen(ETC_PATH)+strlen(OS_INFO)+2, "%s/%s", (char *)ETC_PATH, (char *)OS_INFO)){perror("snprintf");goto error;}
    if (0 > getStats (dataPath, &thisPc->issue, BUFF_SIZE))  {goto error;}
    if (debug)  printf("ISUUEINFO\n%s\n",thisPc->issue);
    
    //ISSUE_S
    memset(thisPc->issue_size,'\0',DEFAULT_LENGTH);
    snprintf(thisPc->issue_size,strlen(thisPc->issue),"%d",(int)strlen(thisPc->issue));


    free(nombre);
    free(dataPath);
    return 0;

    error:
        puts("getStatsController.c");
        free(nombre);
        free(dataPath);
        return -1;
}
