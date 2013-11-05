#include <regex.h>
#include <string.h>
#include "funciones.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse (char *buff, char *addresses){
	
	regex_t retmp;
	regmatch_t mtmp;
	char *patron="DST=[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]";

	if (buff == NULL){
		write(STDERR_FILENO,"buffer vacio",12);
	}

	if (addresses == NULL){
		if  ( (addresses=(char *) malloc (16)) < 0 ){
			perror("malloc()");
			return -1;
		}
	}

	if ( (regcomp(&retmp,patron,REG_EXTENDED) != 0)){
		perror("regcomp()");
		return -1;
	}

	if ( !(regexec(&retmp, buff ,(size_t) 1 , &mtmp, 0)) ){	
		memset(addresses,'\0',strlen(addresses));
		strncpy(addresses,buff+(mtmp.rm_so+4),mtmp.rm_eo-(mtmp.rm_so+4));
		return 1;
	}
	return 0;
}
