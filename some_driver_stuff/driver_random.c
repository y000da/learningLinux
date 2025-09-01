#include <stdio.h>      // Стандартная библиотека ввода-вывода
#include <sys/types.h>  // Определяет основные типы данных, 
                        // используемых в системных вызовах
#include <sys/stat.h>   // Содержит определения для работы с метаданными файлов
#include <fcntl.h>      // Самый важный заголовочный файл для открытия файлов,
                        // содержит определение open и константы флагов доступа
#include <unistd.h>     // Предоставляет доступ к POSIX-API ОС, содержит самые
                        // важные системные вызовы

int main(void) {      
        int f; 
        f = open("/dev/urandom", O_RDONLY);
        if (f < 0) {
                perror("Ошибка при открытии urandom");
                return 1;
        }

        int n;
        unsigned int rnd; 
        n = read(f, &rnd, sizeof(rnd));
        if (n != sizeof(rnd)) {
                perror("Ошибка при чтении urandom");
                return 1;
        }

        printf("Случайное число = 0x%x\n", rnd);
        close(f);
        
        return 0;
}