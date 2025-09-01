#include <stdio.h>          // Для функций ввода/вывода (printf)
#include <unistd.h>         // Для getpid() и sleep()
#include <pthread.h>        // Для работы с потоками (pthread_t, 
//pthread_create, pthread_join)
#include <sys/syscall.h> // Для системного вызова syscall

static void *thread_fn(void *arg) { // Код, выполняемый в отдельном потоке
// Выводит информацию о PID (getpid(), одинаковый для каждого потока) 
// и TID (syscall(SYS_gettid), уникальный для каждого потока).
// Затем засыпает на 10 секунд, выводит сообщение о завершении потока
// и возвращает NULL
    printf("Запущен новый поток, PID %d TID %d\n", getpid(), 
            (pid_t)syscall(SYS_gettid));
    sleep(10);
    printf("Новый поток завершается\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t t;    // Переменная для хранения идентификатора потока
    printf("Главный поток, PID %d TID %d\n", getpid(),  // Вывод информации о
    // главном потоке (в котором выполняется main)
            (pid_t)syscall(SYS_gettid));
    
    pthread_create(&t, NULL, thread_fn, NULL);  // Создаем новый поток
    // &t -- указатель на идентификатор потока
    // NULL -- атрибуты потока по умолчанию
    // thread_fn -- функция, которую будет выполнять поток
    // NULL -- аргумент для передачи в функцию потока
    pthread_join(t, NULL);  // Ждем пока не завершится новый поток.
    // Главный поток здесь блокируется до завершения дочернего

    return 0;
}