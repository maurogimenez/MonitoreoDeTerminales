#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h> //Estructura ipv4 para sockets
#include <netinet/in.h>  //Estructura ipv6 para sockets y para hacerlo generico
#include <arpa/inet.h>

#include "socket/mysocket.h"
#include "monitor.h"

#define REFRESH_TIME refresh
#define debug 0
#define BUFF_SIZE 1000

int main (int argc, char **argv){

    struct pcInfo *thisPc;  //Estructura que contendra los datos de la pc (ver monitor.h)
    
    int opcion;
    char *buffer[BUFF_SIZE];
    int refresh = 300;

    int sockDesc;
    struct sockaddr_in clientSock = {};
    char *serverIp="192.168.1.10";
    int port=5939;
    int protocolo;
    

    //if (1 == debug)  printf("Directories\n%s\n%s\n%s\n%s\n%s\n%s\n\n",MEM_INFO, CPU_INFO,HDD_INFO,UPTIME_INFO,VERSION_INFO,NET_INFO);

    if ( NULL == (thisPc = (pcInfo *) malloc (sizeof (pcInfo)*1000)) )  { perror("malloc"); return -1; }
    
    memset(buffer,'\0',sizeof buffer);
    memset(thisPc,'\0',sizeof thisPc);
    
    //Manejo argumentos
	while ((opcion = getopt(argc, argv, "p:s:t:46h")) >= 0 ){   //s->server ip  t->refresh time
		switch (opcion){
			case 't':
				REFRESH_TIME = atoi(optarg);
				break;
            case 's':
                break;
            case 'h':
                printf("Uso: %s -[args]\nArgumentos:\ns\tSe indica la ip del servidor\np\tSetear el puerto\nt\tIntervalos de reporte al servidor (en segundos)\n4\tUsar ipv4\n6\tUsar ipv6\nh\tHelp! (Tu estas aqui ahora)\n",argv[0]);
                return 0;
			case '4':
				if (protocolo == 0){
					protocolo=4;
				}else{
					protocolo=-1;
				}
				break;
			case '6':
				if (protocolo == 0){
					protocolo=6;
				}else{
					protocolo=-1;
				}
				break;
			default: 
					printf("No se reconoce el comando, por favor ejecuta ./clientMon -h por ayuda\n");
					return 0;
		}
	}

	if(protocolo == -1){    //Protocolo invalido
		puts("Protocolo invalido");
		printf("Forma de ejecucion: %s -t X (opcional)-> -4 o -6\n",argv[0]);
        return -1;
	}

	/*if(strlen(arg.port) < 1){ //No ingreso en la opcion -f
		if ( config("tp5.conf",arg.port,arg.droot) ){
				return -1;
		}
	}*/


    clientSock.sin_family=AF_INET;
    clientSock.sin_port = htons(port);

    if ( 0 == inet_aton(serverIp,&clientSock.sin_addr) ) { perror("inet_aton"); return 0; }
    
    if ( -1 == (sockDesc=socket(AF_INET,SOCK_STREAM,0)) )     { perror("socket"); return 0; }
    
    printf("\nIntentando conectar con el servidor %s:%d...",serverIp,port);
    
    if ( 0 > connect(sockDesc,(struct sockaddr *)&clientSock,sizeof clientSock) ){  //CONNECT
            free(thisPc);
            printf("FALLO CONEXION\n");
            perror ("connect");
            return -1;
    }else{
        printf("Conectado!");
        
    //getStatsController(thisPc);
    //write(sockDesc,thisPc->mem,strlen(thisPc->mem)):
        //while((leido = read(csd,buffer,sizeof buffer)) > 0){
                /*switch  (request(buffer,droot,csd)){
                    case -10: //Archivo no encontrado
                        if ( write(csd,nf404,strlen(nf404)) < 0){
                            close(csd);
                            return -1;
                        }
                        close(csd);
                        _exit(EXIT_FAILURE);
                    case -1: //Problemas del server
                        if ( write(csd,sie500,strlen(sie500)) < 0){
                            close(csd);
                            return -1;
                        }
                        close(csd);
                        _exit(EXIT_FAILURE);
                    default: //Termina exitosamente
                        close(csd);        
                        _exit(EXIT_SUCCESS);
                }*/
            //}
    }

    return 0;
}
