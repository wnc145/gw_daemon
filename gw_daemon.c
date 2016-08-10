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


int GetTargetProccesState(char *proc)
{
	FILE    *read_fp;  
	char    buffer[50], _cmd[128];
	size_t  len;
	memset( (void*)buffer, 0, 50 ); 

	sprintf(_cmd, "ps | grep %s | grep -v grep", proc);

	read_fp = popen(_cmd, "r");
	if (read_fp != NULL)
	{
		len = fread((void*)buffer, sizeof(char), 50, read_fp);  
		if (strlen(buffer) == 0)
		{
			printf("%s restart .\n", proc);
			sprintf(_cmd,"%s &", proc);
			system(_cmd);
		}
		pclose(read_fp);
	}

	return 1;
}





int main(int argc, char **argv) 
{
	struct stat tst;
	char target_proc[32] = {0};

	if(argc < 2)
	{
		printf("please input target process \n");
		return 0;
	}
	
	strcpy(target_proc, argv[1]);

 	while(1)
	{
		GetTargetProccesState(target_proc);
		sleep(3);
	}

    return 0;
}
