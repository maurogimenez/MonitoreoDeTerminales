#include "monitor.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define debug 0

int getStats (char *path, pcInfo *thisPc, int buffsize){

    int fd,leido=1;

    if ( NULL == ( thisPc->mem = (pcInfo*) malloc (10000)) )    { free(thisPc); return -1; }
            
            if (1 == debug) printf("%s\n",path);
    
    if ( (fd=open(path,O_RDONLY)) < 0){  perror("GetStats:open"); return -1;}
    
    while ( leido != 0 ){
        if ( 0 > (leido=read(fd,thisPc->mem,buffsize)) ){
            perror("GetStats:read");
            close (fd);
            return -1;
        }
    printf("%s",thisPc->mem);
    //thisPc->mem = thisPc->mem + leido;
    }
    close(fd);

    return 0;
}
