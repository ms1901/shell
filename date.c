#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <errno.h>
#include <unistd.h>
#include<time.h>
int main(int argc, char const *argv[])
{
	if(!strcmp(argv[0],"date\n"))
	{
		time_t currenttime;

		time(&currenttime);
		struct tm lt;
		if(!localtime_r(&currenttime,&lt))
		{
			perror("localtime error");
		}
		else
		{
			localtime_r(&currenttime,&lt);
			printf("%s time: %s ",lt.tm_zone,ctime(&currenttime));
		}
	
	
	}
	else if(!strcmp(argv[0],"date"))
	{
		if(!strcmp(argv[1],"--help\n"))
		{
			printf("Display the current time in the given FORMAT, or set the system date.\n");
		}
		else if(!strcmp(argv[1],"-u\n") || !(strcmp(argv[1],"--utc\n")))
		{	struct tm *utc;
			time_t utctime;
			time(&utctime);
			if(!gmtime(&utctime))
			{
				perror("gmtime error");
			}
			else
			{
				utc=gmtime(&utctime);
				printf("UTC time: %s",asctime(utc) );
			}
			
		}

	}

	
	return 0;
}