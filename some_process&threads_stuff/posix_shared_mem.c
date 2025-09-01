#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <semaphore.h>

#define SHM_SEGMENT_SIZE 65536
#define SHM_SEGMENT_NAME "/demo-shm"
#define SEMA_NAME "/demo-sem"

static sem_t *demo_sem; // Глобальная переменная-семафор, которую за счет
// static можно использовать только в этом файле

static void *get_shared_memory(void) {  // Функция для получения разделяемой
// памяти, возвращает указатель на эту память.
    struct shared_data *shm_p;  // Указатель на структуру, описывающую 
    // разделяемую память
    int shm_fd = shm_open(SHM_SEGMENT_NAME, O_CREAT | O_EXCL | O_RDWR, 0666); //
    // Попытка создания сегмента разделяемой памяти
    if (shm_fd > 0) { // Если удачно -- вывод сообщения
        printf("Создается разделяемая память размером = %d\n", SHM_SEGMENT_SIZE);
        if (ftruncate(shm_fd, SHM_SEGMENT_SIZE) < 0) { // и resize сегмента
            perror("ftruncate");
            exit(1);
        }

        demo_sem = sem_open(SEMA_NAME, O_RDWR | O_CREAT, 0666, 1); //
        // Создание семафора
        if (demo_sem == SEM_FAILED) { perror("ошибка sem_open\n"); }
    } else if (shm_fd == -1 && errno == EEXIST) { // Если сегмент уже существует
        shm_fd = shm_open(SHM_SEGMENT_NAME, O_RDWR, 0); //
        // Просто открывает существующий сегмент

        demo_sem = sem_open(SEMA_NAME, O_RDWR); // Значит и семафор уже создан,
        // поэтому просто открывает его
        if (demo_sem == SEM_FAILED) { perror("ошибка sem_open\n"); }
    }

    if (shm_fd == -1) { perror("shm_open " SHM_SEGMENT_NAME); exit(1); } //
    // Если не получается создать сегмент и он не существует, то ошибка

    shm_p = mmap(NULL, SHM_SEGMENT_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
                shm_fd, 0); // Отображение разделяемой памяти
    if (shm_p == NULL) { perror("mmap"); exit(1); }

    return shm_p;   // Возвращаем указатель на разделяемый сегмент памяти
}


int main(int argc, char *argv[]) {
    printf("%s PID=%d\n", argv[0], getpid());

    char *shm_p = get_shared_memory();

    while (1) {
        printf("Нажмите Enter для просмотра текущего содержимого shm\n");
        getchar();
        sem_wait(demo_sem);
        printf("%s\n", shm_p);
        sprintf(shm_p, "Привет от процесса %d\n", getpid());
        sem_post(demo_sem);
    }

    return 0;
}