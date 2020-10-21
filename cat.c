#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <errno.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int argc, char *argv[])
{
	//cannot do cat newline 

	if(!strcmp(argv[0],"cat") && strcmp(argv[1],"-n") && strcmp(argv[1],"-b") )
	{
		//printf("%s\n", "in first loop");
		FILE *fopenb;
		int size=1;
		for(size=1;argv[size]!=NULL;size++)
		{
			argv[size][strcspn(argv[size],"\n")] =0;
			fopenb=fopen(argv[size],"r");
			if(fopenb==NULL)
			{
				printf("%s : No such file or directory\n",argv[size]);
			}
			else
			{	char line[1024];
				while(fgets(line,sizeof(line),fopenb))
				{
					printf("%s", line);
				}
			}
		}
	}
	if(!strcmp(argv[0],"cat"))
	{
		//printf("in right");
		FILE *fopenb;
		int size=2;
		argv[size][strcspn(argv[size],"\n")] =0;
		fopenb=fopen(argv[size],"r");
		int count=1;
		if(!strcmp(argv[1],"-n"))
		{
			if(fopenb==NULL)
			{
				printf("%s : No such file or directory\n",argv[size]);
				
			}
			else
			{	char line[1024];
				while(fgets(line,sizeof(line),fopenb))
				{
					printf(" %d %s", count,line);
					count++;
				}
			}
		}
		else if(!strcmp(argv[1],"-b"))
		{
			if(fopenb==NULL)
			{
				printf("%s : No such file or directory\n",argv[size]);
			}
			else
			{	char line[1024];
				while(fgets(line,sizeof(line),fopenb))
				{	if(strcmp(line, "\n") != 0)
					{
						printf(" %d %s", count,line);
						count++;
					}
					else
					{
						printf(" %s",line);	
					}
					
				}
			}
		}	
		for(size=3;argv[size]!=NULL;size++)
		{
			argv[size][strcspn(argv[size],"\n")] =0;
			fopenb=fopen(argv[size],"r");
			if(fopenb==NULL)
			{

				printf("%s : No such file or directory\n",argv[size]);
				
			}
			else
			{	char line[1024];
				while(fgets(line,sizeof(line),fopenb))
				{
					printf("%s", line);
				}
			}
		}
	}
	
	return 0;
}