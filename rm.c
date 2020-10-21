#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <errno.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int argc, char  *argv[])
{
	int size=1;
	//printf("%ld\n",sizeof(ar) );
	if(!strcmp(argv[0],"rm\n"))
	{
		printf("%s\n","rm: missing operand" );
	}
	else
	{
		if(!strcmp(argv[1],"-f") || !strcmp(argv[1],"--force"))
		{
			for(size=2;argv[size]!=NULL;size++)
			{
				argv[size][strcspn(argv[size], "\n")] = 0;
				unlink(argv[size]);
				
			}
		}
		else if(!strcmp(argv[1],"-v"))
		{
			//printf("%s\n","in here" );
			for(size=2;argv[size]!=NULL;size++)
			{
				argv[size][strcspn(argv[size], "\n")] = 0;
				int a=unlink(argv[size]);
				if(a)
				{
					//perror("rm error");
					printf("rm: cannot remove ");
					printf("%s, No such file or directory\n",argv[size]);
				}
				else
				{
					printf("removed %s \n",argv[size] );
				}

				
			}
		}
		else if(!strcmp(argv[1],"--") || !strcmp(argv[1],"--\n"))
		{
			
				if(argv[2]!=NULL)
				{
					for(size=2;argv[size]!=NULL;size++)
					{
						argv[size][strcspn(argv[size], "\n")] = 0;
						if(!strcmp(argv[size],"."))
						{
							printf("rm: cannot remove '.': Is a directory");
						}
						else if(!strcmp(argv[size],".."))
						{
							printf("rm: cannot remove '..': Is a directory");
						}
						else
						{
							int a=unlink(argv[size]);
							if(a)
							{
								printf("rm: cannot remove ");
								printf("%s, No such file or directory\n",argv[size]);
							}
						}
						
					}

				}
				else
				{
					printf("rm: missing operand");
				}
				
		}
		else{

			for(size=1;argv[size]!=NULL;size++)
			{
				argv[size][strcspn(argv[size], "\n")] = 0;
				if(!strcmp(argv[size],"."))
				{
					printf("rm: cannot remove '.': Is a directory");
				}
				else if(!strcmp(argv[size],".."))
				{
					printf("rm: cannot remove '..': Is a directory");
				}
				else
				{
					int a=unlink(argv[size]);
					if(a)
					{
						perror("rm error");
					}
				}
				
			}

		}
		
	}
	return 0;
}