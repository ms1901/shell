#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <errno.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


//gcc loop.c -o loop

int external_commands(char **args)
{
	
	char path[]="/home/manasvi/Documents/myshell/";
	char str[strlen(args[0])];
	strcpy(str,args[0]);
	args[0][strcspn(args[0],"\n")] =0;
	strcat(path,args[0]);
	args[0]=str;	
	pid_t pid;
  	int status;
	pid = fork();
  	if (pid == 0) {
	  
	    if (execvp(path, args) == -1) {
	    printf("Command not found\n");}
    	exit(EXIT_FAILURE);
  } 
  else if (pid < 0) 
  {
   
    perror("lsh");
  } else {
    // Parent process
     //printf("parent");
   wait(NULL);
  }

  return 1;
}
char **lsh_split_line(char *line)
{
  int bufsize = 64, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line," \r\t");
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += 64;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
   // printf("%d\n", position);
    token = strtok(NULL, " \r\t");
  }
  tokens[position] = NULL;
  //positions=position;
  return tokens;
}
char *readlinetillnewline(void)
{
  char *line = NULL;
  ssize_t bufsize = 0; // getline allocates a buffer

  if(getline(&line, &bufsize, stdin) == -1){
    if (feof(stdin)) {
    	//printf("eof");
      exit(EXIT_SUCCESS);  // We recieved an EOF
    } else  {
      perror("readline");
      exit(EXIT_FAILURE);
    }
    

  }
  //printf("%s\n",line );
  return line;
}
void cd(char **args)
{
			if( !strcmp(args[1],"~\n"))
			{
				int b=chdir("/home/manasvi");	
				if(!b){}
				else 
				{perror("cd Error");}
			}
			else if(args[1]!=NULL)
			{
				//follows symbolic links
				if(!strcmp(args[1],"-L"))
				{
					
					args[2][strcspn(args[2], "\n")] = 0;
					if( !strcmp(args[2],"~"))
					{
						int b=chdir("/home/manasvi");	
						if(!b){}
						else 
						{perror("cd Error");}
					}
					else
					{
						int b=chdir(args[2]);
						if(!b)
						{}
						else 
						{
							
							perror("cd Error");
							
						}
					}
					
					
				}
				else if(!strcmp(args[1],"-L\n"))
				{
					chdir("/home/manasvi");
					
				}
				else
				{
						args[1][strcspn(args[1], "\n")] = 0;
						if(!strcmp(args[1],"--help"))
						{
							printf("%s\n","Change the shell working directory.Change the current directory to DIR.The default DIR is the value of the HOME shell variable." );
						}
						else
						{
							int a=chdir(args[1]);
							if(!a)
							{
								
							}
							else
							{
								perror("cd Error");
							}
						}
						
				}
				
				
			}
}

void history(char **args)
{
	if(!strcmp(args[0],"history\n"))
			{
				FILE *fp1=fopen("/home/manasvi/Documents/myshell/history.txt", "r");
				char line[1024];
				if(fp1==NULL)
				{
					printf("%s\n","history file does not exist" );
				}
				else
				{
					while(fgets(line,sizeof(line),fp1))
					{
						printf("%s", line);
					}
					
				}
				fclose(fp1);
			}
			else if(!strcmp(args[0],"history"))
			{
				if(!strcmp(args[1],"-c\n"))
				{
					FILE *fp2=fopen("/home/manasvi/Documents/myshell/history.txt", "w");
					if(fp2==NULL)
					{
						printf("%s\n","history file does not exist" );
					}
					fclose(fp2);

				}
				else if(!strcmp(args[1],"--help\n"))
				{
					printf("Display or manipulate the history list.\n");
				}
			}

}
void loop(void)
{
	char **args;
	FILE *fptr;
	//fptr=fopen("home/manasvi/Documnets/myshell","+a");
	char *cmd=NULL;
	
	char *hist;
	int max=100;
	char commandhist[1024];
	char s[100];
	do
	{
		printf("manasvi@manasvi-shell:");
		printf("%s %s", getcwd(s, 100),"$"); 
		cmd=readlinetillnewline();
		
		
		strcpy(commandhist,cmd);
		
		args=lsh_split_line(cmd);
		fptr=fopen("/home/manasvi/Documents/myshell/history.txt","a+");
		if(fptr==NULL)
		{
			printf("cannot open history file");
		}
		fputs(commandhist, fptr) ;  
		fclose(fptr); 
		
		//fputs("\n", fptr) ; 
		if(strcmp(args[0],"exit\n")==0||strcmp(args[0],"EXIT\n")==0)
		{
			break;
		}
		else if(!strcmp(args[0],"exit"))
		{
			if(!strcmp(args[1],"--help\n"))
			{
				printf("%s\n","exit command exits the shell." );
			}
		}
		else if(strcmp(args[0],"cd")==0 )
		{
			cd(args);				
		}
		else if(strcmp(args[0],"cd\n")==0 )
		{
			chdir("/home/manasvi"); 
		}
		else if(!strcmp(args[0],"pwd") || !strcmp(args[0],"pwd\n") )
		{
			if(!strcmp(args[0],"pwd\n"))
			{
				//printf("%s\n", "in");
				if(!getcwd(s, 200))
				{
					perror("pwd Error ");
				}
				else
				{
					printf("%s\n", getcwd(s, 200)); 

				}
			}
			else if(!strcmp(args[1],"--help\n"))
			{
				printf(" Print the name of the current working directory.\n");
			}
			else if(!strcmp(args[1],"-P\n"))
			{
				//printf("%s\n", "in");
				if(!getcwd(s, 200))
				{
					perror("pwd Error: ");
				}
				else
				{
					printf("%s\n", getcwd(s, 200)); 

				}
			}
			else
			{
				if(!getcwd(s, 200))
				{
					perror("pwd Error: ");
				}
				else
				{
					printf("%s\n", getcwd(s, 200)); 

				}
			}
			
			
			
		}
		else if(!strcmp(args[0],"echo\n") || !strcmp(args[0],"echo"))
		{
			int size=1;
			if(!strcmp(args[0],"echo\n") )
			{
				printf("\n");
			}
			else if(!strcmp(args[0],"echo"))
			{
				if(!strcmp(args[1],"-n"))
				{
					for(size=2;args[size]!=NULL;size++)
					{
						args[size][strcspn(args[size], "\n")] = 0;
					
						printf("%s ",args[size]);
					}
					
				}
				else if(!strcmp(args[1],"-E"))
				{
					int starti=2;
					for(int i=2;args[i]!=NULL;i++)
					{
					
							printf("%s\n",args[i] );
						
						
					}
				}
				else if(!strcmp(args[1],"--help\n"))
				{
					printf("%s\n","echo - display a line of text" );
				}
				else
				{
					
					for(size=1;args[size]!=NULL;size++)
					{
						args[size][strcspn(args[size], "\n")] = 0;
					
						printf("%s ",args[size]);
					}
					printf("\n");
				}
			}
			
		}
		else if(!strcmp(args[0],"history\n") || !strcmp(args[0],"history"))
		{
			history(args);
		}
		else if(strcmp(args[0],"\n"))
		{
			
			external_commands(args);
		}
		
		

	}while(1);
	//fclose(fptr);


}
int main(int argc, char const *argv[])
{
	loop();
	return EXIT_SUCCESS; //returning exit failure in some cases so for symmetry returning exit_success
}
