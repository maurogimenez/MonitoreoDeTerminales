#include "../monitor/monitor.h"

#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

int Mmap (shared **memoria, size_t size){

	if ( (void*)-1 == (*memoria=mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0)) ){
			perror("mmap");
			return -1;
	}

	return 0;
}
