#include "monitor.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define debug 0

int getStats (char *path, char **fichero, int buffsize){

    int fd,leido=1;
    char *aux=*fichero;
    
    if (debug){ printf("Ruta:%s\n",path); printf("Buffsize:%d\n",buffsize);}
                           
    if ( (fd=open(path,O_RDONLY)) < 0){  perror("getStats:open"); return -1;}
    
    while ( 0 < (leido=read(fd,*fichero,buffsize)) ){
        if ( -1 == leido){
            perror("getStats:read");
            close (fd);
            return -1;
        }
        *fichero=&((*fichero)[leido]);
    }
    close(fd);
    *fichero=aux;

    if (debug){ printf("****************************************Buffer********************\n%s\n**************************************\n",*fichero); sleep(4);}
    
    return 0;
}
