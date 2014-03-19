#include "monitor.h"
#include "macros.h"

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#define REFRESH_TIME refresh
#define debug 0

int main (int argc, char **argv){

    struct pcInfo *thisPc;  //Estructura que contendra los datos de la pc (ver monitor.h)
    
    int opcion;
    int refresh = 180;

    int sockDesc;
    struct sockaddr_in serverSock = {};
    char *serverIp=DEFAULT_SERVERIP;
    char *port=DEFAULT_SERVERPORT;

    signal(SIGALRM, refreshWait);

    if (NULL == (thisPc=(pcInfo *) malloc(sizeof(pcInfo))) ) { perror("malloc"); return -1; }
    if (0 > Malloc(&(thisPc->header),40))           { return -1; }
    if (0 > Malloc(&(thisPc->name),NAME_SIZE))      { return -1; }
    if (0 > Malloc(&(thisPc->mem),MEM_SIZE))        { return -1; }
    if (0 > Malloc(&(thisPc->cpu),CPU_SIZE))        { return -1; }
    if (0 > Malloc(&(thisPc->hdd),HDD_SIZE))        { return -1; }
    if (0 > Malloc(&(thisPc->uptime),UPTIME_SIZE))  { return -1; }
    if (0 > Malloc(&(thisPc->version),VERSION_SIZE)){ return -1; }
    if (0 > Malloc(&(thisPc->issue),ISSUE_SIZE))    { return -1; }
    if (0 > Malloc(&(thisPc->end),END_SIZE))        { return -1; }

    //Manejo argumentos
	while ((opcion = getopt(argc, argv, "p:s:t:h")) >= 0 ){   //s->server ip  t->refresh time
		switch (opcion){
			case 't':
				REFRESH_TIME = atoi(optarg);
				break;
            case 's':
                serverIp = optarg;
                break;
            case 'p':
                port = optarg;
                break;
            case 'h':
                printf("Uso: %s -[args]\nArgumentos:\ns\tSe indica la ip del servidor\np\tSetear el puerto\nt\tIntervalos de reporte al servidor (en segundos); En caso de no ingresar valor por defecto reporta cada 180 sg (3 minutos).\nh\tHelp! (Tu estas aqui ahora)\n",argv[0]);
                return 0;
			default: 
					printf("No se reconoce el comando, por favor ejecuta ./clientMon -h por ayuda\n");
					return 0;
		}
	}

    if (1==debug)   printf("strlen(puerto): %d\n",(int)strlen(port));
    if( (strlen(port) < 1) || (65536 < atoi(port)) ){   //Puerto invalido
        write(STDERR_FILENO,"Puerto invalido\n",16);
        return -1;
    }

    //Protocolo
    serverSock.sin_addr.s_addr=inet_addr(serverIp);
    serverSock.sin_family=AF_INET;
    serverSock.sin_port=htons(atoi(port));
    if ( 0 > (sockDesc=socket(AF_INET,SOCK_STREAM,0)) ) { perror("socket"); return -1; }
    
    if ( 0 != connect(sockDesc,(struct sockaddr *)&serverSock,sizeof serverSock) ){  //CONNECT Con el servidor
            perror ("connect");
            return -1;
    }else{   //Conexion exitosa
            while (refresh != 0){       //Hago que reporte a REFRESH_TIME
                getStatsController(thisPc);
                format2protocol(thisPc);
                send2server(thisPc,sockDesc);
                alarm(refresh);
                pause();
            }
    return 0;
    }
}
