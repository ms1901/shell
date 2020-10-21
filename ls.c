#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
void printing(int cur,int parent,char arr[])
{
   struct dirent **list;
   int n;
   
   n = scandir(arr, &list, NULL,alphasort);
   if (n == -1) {
   perror("scandir");
   exit(EXIT_FAILURE);
           }
    int a=0;
   while (a<n) {
    if(parent || strcmp("..",list[a]->d_name)  )
    {
     if(cur|| strcmp(".",list[a]->d_name))
     {
      printf("%s\n",list[a]->d_name);
      free(list[n]);
     }
    
    }
    a++;
               
   }
  free(list);
  
}
void main(int argc,char *argv[])
 { 
   
   char a[100];
   if(!strcmp(argv[0],"ls\n"))
    { 
      strcpy(a,".");
      printing(0,0,a);
    }

   else if(!((strcmp(argv[0],"ls") || strcmp(argv[1],"-a\n"))))
   {
    strcpy(a,".");
    printing(1,1,a);
   }
   else if(!((strcmp(argv[0],"ls") || strcmp(argv[1],"-A\n"))))
   {
    //printf("in A");
    strcpy(a,".");
    printing(0,0,a);
   }
   else if(!((strcmp(argv[0],"ls") || strcmp(argv[1],"-a"))))
   {
    argv[2][strcspn(argv[2],"\n")] =0;
   
    strcpy(a,argv[2]);
    printing(1,1,a);

   }
   else if(!((strcmp(argv[0],"ls") || strcmp(argv[1],"-A"))))
   {
    argv[2][strcspn(argv[2],"\n")] =0;
    strcpy(a,argv[2]);
    printing(0,0,a);
   }
   else 
   {
      //printf("%s\n","yes" );
     if(strcmp(argv[1],"-A")&& strcmp(argv[1],"-a"))
     {
     
        if(argv[2]!=NULL)
        {
           if(!strcmp(argv[2],"-a\n"))
            {
            // printf("%s\n","in a" );
             strcpy(a,".");
             printing(1,1,a);
            }
            else if(!strcmp(argv[2],"-A\n"))
            {
             //printf("in A");
             strcpy(a,".");
             printing(0,0,a);
            }   

        }
         else
         {
         
            argv[1][strcspn(argv[1],"\n")] =0;
           strcpy(a,argv[1]);
           printing(0,0,a);

         }
      
     }
     

   }
   
   
    exit(EXIT_SUCCESS);

 }