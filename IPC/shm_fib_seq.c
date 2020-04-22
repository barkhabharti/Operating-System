#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define MAX_SEQUENCE 10

//structure for the shared data
typedef struct {
long fib_sequence[MAX_SEQUENCE];
int sequence_size;
} shared_data;

//storing the fibonacci numbers in the array fib_sequence contained in
//shared_data struct
void fibonacci(shared_data *sd)
{  sd->fib_sequence[0] = 0;
   sd->fib_sequence[1] = 1;
   for(int k=2;k<sd->sequence_size;k++)
        {
          sd->fib_sequence[k] = sd->fib_sequence[k-1] + sd->fib_sequence[k-2];
        }
}

int main(int argc,char *argv[])
{
	int num, shmid;
	pid_t pid;
	shared_data *sd;
  // Check if 2 arguments were supplied.
	if (argc != 2)
	{
  	printf ("Please enter a number to fibonacci sequence\n");
  	return 0;
	}
	num =atoi(argv[1]);
  // Check if supplied argument is non negative.
	if(num < 0)
	{
    printf("Enter a non-negative number.\n");
	  return 0;
	}
// Check if supplied argument is not greater than the MAX_SEQUENCE.
  else if(num > MAX_SEQUENCE)
	{
    printf("Entered number cannot be greater than %d\n", MAX_SEQUENCE);
	  return 0;
	}
   //Create the segment.
	shmid= shmget(IPC_PRIVATE, sizeof(shared_data), 0777|IPC_CREAT);
    //attach the segment to memory
  sd = (shared_data *)shmat(shmid,0, 0);
  if (! sd) {
   printf("*** shmat error (server) ***\n");
   exit(1);
  }
  sd->sequence_size = num;
  //Fork child process
	pid = fork();
 // If the current executing process is a child process
 //it writes the contents of the Fibonacci sequence to the shared memory segment
	if (pid == 0)
	{

  	fibonacci(sd);
    //detach the child process from shared memory segment
    shmdt(sd);
	}
  // If the current executing process is a process process
  //output the sequence when the child completes
	else if(pid > 0)
	{
  printf ("parent is waiting for child to complete\n");
	wait(NULL);
	printf("printing fibonacci sequence:\n");

  //printing the fibonacci sequence
	for(int i=0; i<sd->sequence_size; i++)
	{
	printf("%ld ", sd->fib_sequence[i]);
	}
  printf("\n");
  //detach the parent process from shared memory segment
	shmdt(sd);
  //destroy the shared memory segment
	shmctl(shmid, IPC_RMID, 0);
	}
	return 0;
	}
