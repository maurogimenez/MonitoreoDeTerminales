#ifndef MONITOR_H_
    #define MONITOR_H_
    
    typedef struct pcInfo{
        char *header;
        char *name;
        char *mem;
        char *cpu;
        char *hdd;
        char *uptime;
        char *version;
        char *issue;
        char *net;
        char *extra;
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
