#ifndef MACROS_H_
    #define MACROS_H_

    /************TAMAÑOS****************/
    #define HEADER_SIZE 40
    #define TIME_SIZE 25
    #define NAME_SIZE 30
    #define MEM_SIZE 3000
    #define CPU_SIZE 3000
    #define HDD_SIZE 4500
    #define UPTIME_SIZE 100
    #define VERSION_SIZE 200
    #define ISSUE_SIZE 35
    #define END_SIZE 7

    /******LONGITUDdelTAMAÑO********
     * Por cada sección del reporte, se enviará el
     * tamaño de lo que mide para que el server
     * pueda reservar memoria de manera adecuada
     * y sepa cuanto es lo que tiene que escribir
    * */
    #define DEFAULT_LENGTH 8 

    /**************RUTAS****************/
    #define PROC_PATH "/proc"
    #define ETC_PATH "/etc"
    #define MEM_INFO "meminfo"
    #define CPU_INFO "cpuinfo"
    #define HDD_INFO "diskstats"
    #define UPTIME_INFO "uptime"
    #define VERSION_INFO "version"
    #define OS_INFO "issue"

    /******MONITOR SERVER DEFAULTS******/
    #define DEFAULT_SERVERIP "127.0.0.1"
    #define DEFAULT_SERVERPORT "12185"

    /**********BUFFER*SIZE**************/
    #define BUFF_SIZE 2000
    #define LARGEST_BUFFER 4500  //Se usa para almacenar TODA la informacion de una determinada seccion del reporte. Por lo tanto tiene que tener correspondencia con el maximo tamaño de las macro declaradas en TAMAÑO

#endif
