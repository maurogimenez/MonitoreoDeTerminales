#include "socket/mysocket.h"
#include "server.h"
#include "webServer/myWebServer.h"

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFF_SIZE 1024
#define MON_PORT 13000
#define debug 0

int main (int argc, char * const argv[]){

    if (1 == debug) printf("DEBUG ENABLED\nMonitorPort:%d\n",MON_PORT);

    signal(SIGCHLD, SIG_IGN);

    char *const mon_port = (char *)MON_PORT;

	char buffer[BUFF_SIZE];
	char *port=(char *) malloc (10);
    char *droot=(char *) malloc (512);

	int loop=0; //Iterador para crear los hijos
    int leido=0;
    int opcion=0;
    int protocolo=0;   

    int sockDesc=0;
    int csd=0;

    memset(buffer,'\0',sizeof(buffer));
    memset(port,'\0',sizeof port);
    memset(droot,'\0',sizeof droot);	

    port="13000";
	//Manejo argumentos
	while ((opcion = getopt(argc, argv, "c:46")) >= 0 ){
		switch (opcion){
			case 'c':
				if ( config(optarg,port,droot) < 0 ) //Configuracion del documentRoot y del puerto a partir de un archivo indicado por linea de comando
					return -1;
				break;
			case '4':
				protocolo = (protocolo == 0) ? 4 : -1;
				break;
			case '6':
				protocolo = (protocolo == 0) ? 6 : -1;
				break;
			default: 
					printf("Forma de ejecucion: %s -f arch.conf (opcional)-> -4 o -6\n",argv[0]);
					return 0;
		}
	}



    if (1==debug)   printf("Protocolo: %d\n",protocolo);
	if(protocolo == -1){    //Protocolo invalido
		puts("Protocolo invalido");
		printf("Forma de ejecucion: %s -f arch.conf (opcional)-> -4 o -6\n",argv[0]);
	}

	if(strlen(port) < 1){ //No ingreso en la opcion -f
		if ( config("config.cfg",port,droot) ){
				return -1;
		}
	}


    if (1==debug)   printf("strlen(puerto): %d\n",(int)strlen(port));
	if(strlen(port) < 1){   //Puerto invalido
		write(STDERR_FILENO,"Puerto invalido\n",16);
		return -1;
	}


    printf("%d,%s",sockDesc,port);
	//Protocolo
	switch(protocolo){
	 	case 0:
			if(unspec(&sockDesc,port) < 0)
				return -1;
			break;
		case 4:
			if(ipv4(&sockDesc,port) < 0)
				return -1;
			break;
		case 6:
			if (ipv6(&sockDesc,port) < 0)
				return -1;
			break;
	}
	//-----------------------------------------------------------------------------------------

    puts("HOLAAAAAAA");
	listen(sockDesc,5);
    printf("\n\tServidor Iniciado, esperando conexiones en el puerto %s \tGimenez Mauro - Risma Franco\n",mon_port);
    while( (csd = accept(sockDesc,NULL,NULL)) > 0 ){
            switch(fork()){
                    case 0:
                            while((leido = read(csd,buffer,sizeof buffer)) > 0){
                                write(STDOUT_FILENO,buffer,leido);
                               /* switch  (request(buffer,droot,csd)){
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
                                        }
                               */ }
                        default:
                                close(csd);
                                printf("Conexion establecida al puerto:%s\n",port);
                                break;

                }
        }	
	
	/*
	//Creo la memoria compartida
		if ( (memoria=mmap(NULL,width*height*3+sizeof(sem_t),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0)) == (void *)-1){
			perror("mmap");
			return -1;
		}
	
	if ( munmap(memoria,width*height*3+sizeof(unsigned char)) < 0){//Cerrar la memoria compartida
			ouch="munmap";
			goto err;
		}

		
		
		
	switch ( fork() ){
			case 0: //Hijo
				_exit(EXIT_SUCCESS);
			
			case -1:
				puts("fork");
				return -1;
			
			default: //Padre
	}*/

    return 0;
}
