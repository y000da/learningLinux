// Работа программы на примере вызова /bin/ls
// 1. Вводим /bin/ls в ответ на приглащение оболочки
// 2. Оболочка разветвляется и порождает свою копию
// 3. Потомок вызывает exec, чтобы выполнить /bin/ls
// 4. Программа ls работает, мы видим содержимое
// 5. Программа ls завершается, оболочке возвращается управление,
// дочерний процесс также завершается.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
        char command_str[128];
        int pid;
        int child_status;
        int wait_for = 1;

        while (1) {     // В бесконечном цикле выводим приглашение ко вводу
        // и читаем написанное. После чтения создаем новый процесс.
                printf("sh> ");
                scanf("%s", command_str);
                pid = fork();
                
                if (pid == 0) { // Для потомка
                        printf("cmd '%s'\n", command_str);      // Дублируем
                        // введенную команду
                        execl(command_str, command_str, (char *)NULL); //
                        // Переключаем выполнение на введенную команду.
                        // После этого выполняется введенная команда и сюда
                        // мы уже не должны вернуться.
                        perror("exec"); // Поэтому, если все таки вернулись,
                        // то это ошибка и аварийное завершение.
                        exit(1);      
                }

                if (wait_for) { // Ждем код завершения в родителе
                        waitpid(pid, &child_status, 0); // Считываем код в 
                        // child_status и выводим сообщение
                        printf("Готово, код возврата %d\n", child_status);
                }
        }
        return 0;
}