#define LOGFILE "output.log" // Where should we save our data

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef linux
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <dirent.h>
#endif

int main()
{
	#ifdef linux
	// Setup stuff for uname later
	struct utsname unamedata;
	uname(&unamedata);
	#endif

	// Setup File logging stuff
	FILE *log = fopen(LOGFILE,"w");
	if(log == NULL)
	{
		printf("ERROR : UNABLE TO CREATE LOG FILE\n");
		exit(1);
	}

	// Begin Logging
	printf("====== Logging To File : %s =======\n",LOGFILE);
	#ifdef linux
	printf("Current Username : %s\n",getlogin());
	fprintf(log,"Current Username : %s\n",getlogin());

	printf("OS Type: %s\n", unamedata.sysname);
	fprintf(log,"OS Type: %s\n", unamedata.sysname);

	printf("Node/Host name: %s\n", unamedata.nodename);
	fprintf(log,"Node/Host name: %s\n", unamedata.nodename);

	printf("Kernel Information: %s %s\n", unamedata.release,unamedata.version);
	fprintf(log,"Kernel Information: %s %s\n", unamedata.release,unamedata.version);

	printf("Architecure: %s\n", unamedata.machine);
	fprintf(log,"Architecure: %s\n", unamedata.machine);

	// Get network interfaces
  printf("Network Interfaces - Currently this is not logged to file");
	DIR *lsd;
	char buffer[1024];
	struct dirent *ep;
	lsd = opendir ("/sys/class/net");
	if (lsd != NULL)
	{
		while(ep = readdir (lsd))
		puts(ep->d_name);
		printf("%s\n",buffer);
		(void) closedir (lsd);
	}
	else
	{
	perror ("Couldn't Find /sys/class/net");
	}
	#endif
}
