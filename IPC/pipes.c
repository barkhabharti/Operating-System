#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include<string.h>
#include<ctype.h>
#define MAX 100

int main()
{
  /*
   * File descriptor array fd1 and fd2.
   * create two pipes, we give pipe() these arrays
   */
  char arr[MAX];
  int fd1[2], fd2[2], i;
  int pipe_w = pipe(fd1);
  int pipe_r = pipe(fd2);
  if (pipe_w ==-1 || pipe_r ==-1)
  {
      fprintf(stderr, "Pipe Failed" );
      return 1;
  }
  pid_t pid = fork();
  if(pid == 0)
  {
      //closing the writing end of pipe 2
      close(fd2[0]);
      close(fd1[1]);
      char arr[MAX];
      // Read  from file descriptor into arr
      read(fd1[0], arr, sizeof(arr));
      //changing cases
      printf("childprocess: %s\n", arr);
      for ( i = 0; i < strlen(arr); i++)
      {
        if(islower(arr[i]))
            arr[i] = toupper(arr[i]);
        else
            arr[i] = tolower(arr[i]);
      }
  //Write the updated arr into file descriptor
   write(fd2[1], arr, strlen(arr));
 }
  else if( pid > 0 )
  {
    printf("parent process\n");
    printf("enter the string :\n");
    scanf("%s", arr);
    // no need to use the write end of pipe2 and read end of pipe1 here so close it
    close(fd1[0]);
    close(fd2[1]);
      //Write bytes from array arr to file descriptor.
    write(fd1[1], arr, strlen(arr));
    wait(NULL);
    printf("parent process: ");
    read(fd2[0], arr, strlen(arr));
    printf("%s\n",arr);
  }
  else {
      perror("error\n"); //fork()
      return 1;
  }
  return 0;
}
