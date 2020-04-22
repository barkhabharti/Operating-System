

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> // read the number of the last error
#include <fcntl.h> // file descriptor CONSTANT mode values

int main (int argc, char *argv[]) {

    /*
     * File descriptor array.
     * When we create our pipe, we give pipe() this array and it will
     * put the reading[0] and writing[1] file descriptors for the pipe into it.
     */

    int fd[2];
    int fileBytesLength;
    char buffer[100];
    char childBuffer[100];
    pid_t pid;
    // Check if 3 arguments were supplied.
    if (argc != 3)
    {
      printf("Please enter the input file and the output file. \n");
      exit(1);
    }

    char* srcFile = argv[1];
    char* dstFile = argv[2];

    // Attempt to create a pipe.
    if (pipe(fd) < 0)
    {
      printf("Something went wrong creating the pipe! %s\n", strerror(errno));
      return 1;
    }

    // Fork child process
    pid = fork();
    // If there was an errorforking a child process
    if(pid < 0)
    {
      printf("Error forking child process. %s\n", strerror(errno));
      return 1;
    }
    // If the current executing process is a child process
    // Read the file from upstream parent process and write it to a new file.
    else if(pid == 0)
    {
      close(fd[1]);                                                        // Close writing end of pipe upstream.
      ssize_t num_bytes_child = read(fd[0], childBuffer, sizeof(childBuffer));   // Read file contents from upstream pipe into childBuffer
      close(fd[0]);                                                        // close reading upstream pipe when we're done with it

      int targetDesc = open(dstFile, O_CREAT | O_WRONLY);                                  // Open a file for writing, create file descriptor.
      write(targetDesc, childBuffer, num_bytes_child);                            // Write contents of buffer to new file descriptor.

    }
    // If the current process is the parent process.
    // Read the file and send it down to the child process to write.

    else
    {
      close(fd[0]);                                              // close reading end of pipe downstream.
      int fileInDesc = open(srcFile, O_RDONLY);                       // Read file into file descriptor
      ssize_t num_bytes = read(fileInDesc, buffer, sizeof(buffer));   // Get number bytes to read
      write(fd[1], buffer, num_bytes);                           // Write bytes to child process.
      close(fd[1]);                                              // Close writing downstream pipe when we're done with it.

    }

    return 0;
  }
