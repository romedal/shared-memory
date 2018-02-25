/*
 ============================================================================
 Name        : shared_memory.c
 Author      : romedal
 Version     :
 Copyright   : Your copyright notice
 Description : SHARED MEMORY IN C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>
#include <error.h>
#include <errno.h>


int main(void) {
	int segment_id;
	char shared_memory;
	struct shmid_ds shmbuffer;
	int segment_size;
	const int shared_segment_size = 0x6400;
	segment_id = shmget(IPC_PRIVATE, shared_segment_size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

	shared_memory = (char *) shmat(segment_id, 0, 0);
	if (-1 == shared_memory)
	{
		printf("shmat errno - %s\n",strerror(errno));
	}
	else
	{
		printf("shared memory attached at address %p\n", shared_memory);
	}
	if (-1 == shmdt(shared_memory))
	{
		printf("shmdt errno - %s\n",strerror(errno));
	}
	shmctl(segment_id, IPC_RMID, 0);

	puts("");
	return EXIT_SUCCESS;
}
