#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

int main() {
    // Open same shared memory
    int fd = shm_open("/myshm", O_RDONLY, 0666);
    char *ptr = mmap(NULL, 1024, PROT_READ, MAP_SHARED, fd, 0);

    // Open same semaphore
    sem_t *sem = sem_open("/mysem", 0);

    // Lock → Read → Unlock
    sem_wait(sem);                        // lock
    printf("Reader read: %s\n", ptr);
    sem_post(sem);                        // unlock

    munmap(ptr, 1024);
    close(fd);
    sem_close(sem);

    // Cleanup — only do this once when fully done
    shm_unlink("/myshm");
    sem_unlink("/mysem");
    return 0;
}
