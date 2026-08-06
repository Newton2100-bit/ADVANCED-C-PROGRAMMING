#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

int main() {
    // Create shared memory
    int fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, 1024);
    char *ptr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Create semaphore
    // sem_open(name, O_CREAT, permissions, initial_value)
    // initial value 1 = unlocked, 0 = locked
    sem_t *sem = sem_open("/mysem", O_CREAT, 0666, 1);

    // Lock → Write → Unlock
    sem_wait(sem);                        // lock (value 1→0)
    strcpy(ptr, "Hello from writer!");
    printf("Writer wrote: %s\n", ptr);
    sem_post(sem);                        // unlock (value 0→1)

    munmap(ptr, 1024);
    close(fd);
    sem_close(sem);
    return 0;
}
