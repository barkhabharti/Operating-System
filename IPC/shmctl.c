
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main( int argc, char* argv[])
{
   //to store the structure data of the passed shmid
   struct shmid_ds *buf;
   //check if 2 arguments were supplied
   if(argc != 2)
   {
     printf("Please pass an identifier for a shared memory segment.\n")
   }

   int shmid = argv[1];
   //allocating memory for the variable of type struct shmid_ds
   buf = (struct shmid_ds *)malloc(sizeof(struct shmid_ds));

    // destroy the shared memory and store the shmid_ds data into the buf
    shmctl(shmid,IPC_STAT,buf);
    printf("Segment ID: %d\n", shmid);
    printf("Key: %d\n", buf->shm_perm.__key);
    printf("Mode: %hu\n", buf->shm_perm.mode);
    printf("Owner UID: %hu\n", buf->shm_perm.uid);
    printf("Size: %zu\n", buf->shm_segsz);
    printf("Number of attaches: %lu\n", buf->shm_nattch);

    return 0;
}
