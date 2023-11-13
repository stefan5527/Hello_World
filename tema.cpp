#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <cstdlib>
#include <stdio.h>
#include <ctime>

using namespace std;

int main() {
    int fd = shm_open("/mem_partajata", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(int));
    int* mem_ptr = (int*)mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    sem_t* sem = sem_open("/semafor", O_CREAT, 0666, 1);

    srand(time(nullptr));

    while (true) {
        sem_wait(sem);

        int random_value = rand() % 2;

        if (*mem_ptr < 1000) {
            if (random_value == 1) {
                *mem_ptr += 1;
                cout << *mem_ptr << endl;
            }
        }

        sem_post(sem);

        if (*mem_ptr >= 1000) {
            break;
        }
    }

    sem_close(sem);
    sem_unlink("/semafor");
    shm_unlink("/mem_partajata");

    return 0;
}