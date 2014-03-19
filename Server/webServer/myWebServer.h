#ifndef MYWEBSERVER_H_
    #define MYWEBSERVER_H_

	int config (char *cfgfile, char *port, char *droot);
	int request (char *buffer, char *droot, int csd);
	int response_header(int fd, char *ext, int csd);
	int webServer(char *droot, int csd);

#endif
