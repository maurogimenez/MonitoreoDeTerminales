#ifndef MONITOR_H_
    #define MONITOR_H_
    
    typedef struct pcInfo{
        char *mem;
        char *cpu;
        char *hdd;
        char *net;
        char *extra;
    }pcInfo;

    int getStats (char *path, pcInfo *pcData, int buffsize);
    int getStatsController(pcInfo *pc);
    int parse (char *patron, char *buff, int offset, char *resultado);

#endif
