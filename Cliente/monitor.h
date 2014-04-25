#ifndef MONITOR_H_
    #define MONITOR_H_
    
    typedef struct pcInfo{
        char *header;
        char *time;
        char *name_size;
        char *name;
        char *mem_size;
        char *mem;
        char *cpu_size;
        char *cpu;
        char *hdd_size;
        char *hdd;
        char *uptime_size;
        char *uptime;
        char *version_size;
        char *version;
        char *issue_size;
        char *issue;
        char *end;
    }pcInfo;

    int getStats (char *path, char **structMember, int buffsize);
    int getStatsController (pcInfo *pc);
    int parse (char *patron, char *buff, int offset, char *resultado);
    int Malloc (char **varaible, long size);
    int format2protocol (pcInfo *pc);
    int send2server (pcInfo *pc, int socketDescriptor);
    int Write (int socket, char *data, long size);
    void refreshWait (int signal);
#endif
