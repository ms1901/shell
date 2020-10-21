#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include<string.h>
int main(int argc,char *argv[])
{
	//check if main's second argumnet is right
	//printf("in");
	argv[0][strcspn(argv[0],"\n")] =0;
	char a[100];
	int size;
	int start=1;
	
	if(argv[1]==NULL)
	{
		printf("mkdir: missing operand");
	}

	 else if(!strcmp(argv[1],"-v"))
	{
		start=2;
		for (size = start; argv[size]!= NULL; size++)
		{
			argv[size][strcspn(argv[size], "\n")] = 0;
			int check=mkdir(argv[size],0777);
			
			if(!check)
			{
				printf("mkdir :Created directory %s\n",argv[size] );
			}
			else
			{
				perror("mkdir error");		
			}
		}

	}
	else if(!strcmp(argv[1],"--help\n"))
	{
		printf("%s\n","mkdir - make directories\n ");
	}

	
	else
	{
		
		for (size = 1; argv[size]!= NULL; size++)
		{
			argv[size][strcspn(argv[size], "\n")] = 0;
			int a=mkdir(argv[size],0777);
			//printf("%d\n",a );
			if(a)
			{
				perror("mkdir error");	
			}

		}
	}
	

	
	return 0;
}