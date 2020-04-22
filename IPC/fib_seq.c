#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

//function to compute first n fibonacci numbers
void fibonacci(int n)
{  int sum=1, i, j;
   i = j =0;
   for(int k=0;k<n;k++)
        {
                i = j;
                j= sum;
                sum = i + j;
                printf("%d ",sum);
        }
   printf("\n");
}

int main(int argc,char *argv[])
{
    int num;
    pid_t pid;

    // Check if 2 arguments were supplied.
    if (argc != 2)
    {
        printf ("Please enter a number to fibonacci sequence\n");
	return 0;
    }
	 num =atoi(argv[1]);
   //check for non-negative number
	 if(num < 0)
	{ printf("Enter a non-negative number.\n");
	 return 0;
	}
   //Fork child process
    pid = fork();
    // If the current executing process is a child process
    if (pid == 0)
    {  printf("Child Process. \n")
      //call fibonacci function to print the first num fibonacci numbers
       fibonacci(num);
   }
   // If the current executing process is a child process
    else if (pid > 0)
   {
    printf ("Parent is waiting for child\n");
    wait(NULL);
   }
   // If there was an errorforking a child process
   else
   {
     printf("Error forking child process. %s\n", strerror(errno));
     exit(1);
   }
   return 0;
}
