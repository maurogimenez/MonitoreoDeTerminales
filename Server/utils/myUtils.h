#include "../monitor/monitor.h"

#ifndef MYUTILS_H_
    #define MYUTILS_H_

	int parse (char *patron, char *buff, int offset, char *resultado);
	int Mmap (shared **memoria, size_t size);
    int Malloc (char **varaible, long size);

#endif
