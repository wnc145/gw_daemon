#include <stdio.h>    // for printf()  
#include <string.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <stdarg.h>
#include <signal.h>   // for signal()  
#include <fcntl.h>				/* low-level i/o */   

#include <sys/socket.h>
#include <arpa/inet.h>

#include <linux/sockios.h>  
#include <sys/ioctl.h>  
#include <linux/if.h>  

#define  TargetProcName	"gw7688"


int GetTargetProccesState(void)
{
	FILE    *read_fp;  
	char    buffer[50], _cmd[128];
	size_t  len;
	memset( (void*)buffer, 0, 50 ); 

	sprintf(_cmd, "ps | grep %s | grep -v grep", TargetProcName);
	read_fp = popen(_cmd, "r");
	if (read_fp != NULL)
	{
		len = fread(buffer, sizeof(char), 50, read_fp);  
		if (strlen(buffer) == 0)
		{
			printf("%s restart .\n", TargetProcName);
			sprintf(_cmd,"%s &", TargetProcName);
			system(_cmd);
		}
		pclose(read_fp);
	}

	return 1;
}





int main(int argc, char **argv) 
{
	struct stat tst;

 	while(1)
	{
		GetTargetProccesState();
		sleep(3);
	}

    return 0;
}
