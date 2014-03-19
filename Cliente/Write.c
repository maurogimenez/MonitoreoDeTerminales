#include "monitor.h"

#include <unistd.h>
#include <stdio.h>

int Write (int descriptor, char *data, long size){
    
    if (0 >=  write(descriptor,data,size) ) { perror("write"); return -1; }
    return 0;

}
