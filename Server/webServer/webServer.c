#include "myWebServer.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int webServer (char *droot, int csd){

    int leido=0;
    char buffer[1000];
    
	char *nf404="HTTP/1.0 404 NOT FOUND\r\nContent-Type: text/html\n\n<html>\n<body>\n404 Not Found\n</body>\n</html>";
	char *sie500="HTTP/1.0 500 Server Internal Error\r\nContent-Type: text/html\n\n<html>\n<body>\n500 Server Internal Error\n</body>\n</html>";
    
    while((leido = read(csd,buffer,sizeof buffer)) > 0){
		switch ( request(buffer,droot,csd) ){
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
    return 0;
}
