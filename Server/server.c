#include "socket/mySocket.h"
#include "utils/myUtils.h"
#include "webServer/myWebServer.h"
#include "monitor/monitor.h"

#include <inttypes.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFF_SIZE 1024
#define MON_PORT "12185" //Numero primo descubierto por Dubner
#define debug 0

int main (int argc, char * const argv[]){

    if (debug) printf("DEBUG ENABLED\nMonitorPort:%s\n",MON_PORT);

    signal(SIGCHLD, SIG_IGN);

    //WebServer variables
    char *ws_port=NULL;
    char *ws_droot=NULL;
    int ws_sd=0;
    int ws_csd=0;

    //Monitor variables
    struct sockaddr_in cliente;
    int long_cli=0;
    int mon_sd=0;
    int mon_csd=0;

    //SharedMemory & Semaphores variables
    shared *shMemory;

    //Aux variables
    char buffer[BUFF_SIZE];
    int opcion=0;
    int protocolo=0;
    int erno=0;

    if( Malloc(&ws_port,6) )   {return -1;}
    if( Malloc(&ws_droot,15) ) {return -1;}
    memset(buffer,'\0',BUFF_SIZE);

    //Manejo argumentos
    while ((opcion = getopt(argc, argv, "c:46h")) >= 0 ){  //-c webServerconfig.file | -4 ipv4 | -6 ipv6 | -h help
        switch (opcion){
            case 'c':
                if ( config(optarg,ws_port,ws_droot) < 0 ) //Configuracion del documentRoot y del puerto a partir de un archivo indicado por linea de comando
                    return -1;
                break;
            case '4':
                protocolo = (protocolo == 0) ? 4 : -1;
                break;
            case '6':
                protocolo = (protocolo == 0) ? 6 : -1;
                break;
            case 'h':
                printf("Forma de ejecucion: %s -[args]\nArgumentos:\nc\tArchivo de configuracion (default configuration.cfg)\n4\tForzar ipv4\n6\tForzar ipv6\nl\tidioma (ejemplo -l es)\nh\tAyuda(Estas aqui ahora)\n",argv[0]);
                return 0;
            default: 
                printf("Sintaxis ambigua. Ejecuta: %s -h para obtener ayuda\n",argv[0]);
                return 0;
        }
    }



    if (debug)   printf("Protocolo: %d\n",protocolo);
    if(protocolo == -1){    //Protocolo invalido
        puts("Protocolo invalido");
        printf("Sintaxis ambigua. Ejecuta: %s -h para obtener ayuda\n",argv[0]);
        return -1;
    }

    if(strlen(ws_port) < 1){ //No ingreso en la opcion -c
        if ( config("configuration.cfg",ws_port,ws_droot) ){
                return -1;
        }
    }


    if (debug)   printf("strlen(puerto): %d\n",(int)strlen(ws_port));
    if(strlen(ws_port) < 1){   //Puerto invalido
        write(STDERR_FILENO,"Puerto invalido\n",16);
        return -1;
    }


    //Protocolo
    if ( 0 > protocol_handler(protocolo,&mon_sd,MON_PORT) ) { return -1; }  //MonitorSocket
    if ( 0 > protocol_handler(protocolo,&ws_sd,ws_port) )   { return -1; }  //WebServerSocket
    
    if (debug) printf("Web\tSocket: %d\tPort: %s\nMonitor\tSocket: %d\tPort: %s",ws_sd,ws_port,mon_sd,MON_PORT);
    //-----------------------------------------------------------------------------------------


    //Creo la memoria compartida
    Mmap(&shMemory,sizeof(shared));
    
    //Inicio el semaforo
    //m=(sem_t *) memoria; //Mi semaforo estara en memoria compartida en la posicion a la que apunta la variable puntero
    //if ( 0 > sem_init(shMemory->sem1,1,1) )  { perror("sem"); return -1; }  //Si el segundo argumento es 0, el semaforo sera para THREADS, de lo contrario, PROCESSES   

    switch( (erno=fork()) ){

        case 0:  //WebServer
            listen(ws_sd,15);
            printf("\n\tWebServer->OK\tPuerto %s\n",ws_port);
            while( (ws_csd = accept(ws_sd,NULL,NULL)) > 0 ){
                switch( (erno=fork()) ){
                    case 0:  //httpRequest
                        webServer(ws_droot,ws_csd);
                        return 0;
                    default:
                        close(ws_csd);
                        if (-1==erno)  { perror("ws:fork"); return -1; }
                        printf("Conexion establecida al puerto:%s\n",ws_port);
                }
            }
        
        default: //Padre -> Monitor Server
            listen(mon_sd,5);
            printf("\n\tMonitorServer->OK\tPuerto %s\n",MON_PORT);
            long_cli=sizeof (cliente);
            while( 0 < (mon_csd = accept(mon_sd,(struct sockaddr *)&cliente,(socklen_t *)&long_cli)) ){
                switch( (erno=fork()) ){
                    case 0:
                        statsController(mon_csd);
                        _exit(EXIT_SUCCESS);
                    default:
                        close(mon_csd);
                        printf("\t%s ---> Conexion establecida al puerto: %s\n\n",inet_ntoa(cliente.sin_addr),MON_PORT);
                        //wait(NULL);

                //free(ws_port);
                //free(ws_droot);
                /*if ( munmap(shMemory,sizeof(shared)) < 0){//Cerrar la memoria compartida
                    perror("munmap");
                    return -1;
                }*/
                //wait(0);
                }
            }
      }

    return 0;
}
