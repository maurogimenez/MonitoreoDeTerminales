#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include "funciones.h"

int main(int argc, char *const *argv){
	
	extern char *optarg;
	int opcion;

	signal(SIGCHLD, SIG_IGN);
	int sd=0,leido=0,csd=0,protocolo=0;
	char buffer[128];
	memset(buffer,'\0',sizeof buffer);

	char *port=(char *) malloc (10);
	char *droot=(char *) malloc (512);
	memset(port,'\0',sizeof port);
	memset(droot,'\0',sizeof droot);

	char *nf404="HTTP/1.0 404 NOT FOUND\r\nContent-Type: text/html\n\n<html>\n<body>\n404 Not Found\n</body>\n</html>";
	char *sie500="HTTP/1.0 500 Server Internal Error\r\nContent-Type: text/html\n\n<html>\n<body>\n500 Server Internal Error\n</body>\n</html>";

	//Manejo argumentos
	while ((opcion = getopt(argc, argv, "f:46")) >= 0 ){
		switch (opcion){
			case 'f':
				if ( config(optarg,port,droot) < 0 )
					return -1;
				break;
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
					printf("Forma de ejecucion: %s -f arch.conf (opcional)-> -4 o -6\n",argv[0]);
					return 0;
		}
		break;
	}

	if(protocolo==-1){    //Protocolo invalido
		puts("Protocolo invalido");
		printf("Forma de ejecucion: %s -f arch.conf (opcional)-> -4 o -6\n",argv[0]);
	}

	if(strlen(port) < 1){ //No ingreso en la opcion -f
		if ( config("tp3.conf",port,droot) ){
				return -1;
		}
	}

	if(strlen(port) < 1){   //Puerto invalido
		write(STDERR_FILENO,"Puerto invalido\n",16);
		return -1;
	}
	//-----------------

	//Protocolo
	switch(protocolo){
	 	case 0:
			if(unspec(&sd,port) < 0)
				return -1;
			break;
		case 4:
			if(ipv4(&sd,port) < 0)
				return -1;
			break;
		case 6:
			if (ipv6(&sd,port) < 0)
				return -1;
			break;
	}
	listen(sd,5);
	printf("\n\tServidor Iniciado, esperando conexiones en el puerto %s \tGrupo 8: Gimenez Mauro - Risma Franco\n",port);
	while( (csd = accept(sd,NULL,NULL)) > 0 ){
		switch(fork()){
			case 0:
				while((leido = read(csd,buffer,sizeof buffer)) > 0){
					switch  (request(buffer,droot,csd)){
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
				}
			default:
				close(csd);
				printf("Conexion establecida al puerto:%s\n",port);
				break;

		}
	}
	free(port);
	free(droot);
	return 0;
}
