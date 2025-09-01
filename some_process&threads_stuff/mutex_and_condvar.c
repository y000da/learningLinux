// Кусок кода для иллюстрации реализации между потребителем и производителем

pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutx = PTHREAD_MUTEX_INITIALIZER;


void *consumer(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutx);  // Захват мьютекса
        while (buffer_empty(data)) { pthread_cond_wait(&cv, &mutx); } //
        // Пока буффер пуст, блокируем поток. При этом pthread_cond_wait(),
        // если она заблокированна по переменной condvar (cv), освобождает
        // мьютекс во избежание взаимоблокировки, и снова захватывает его,
        // перед тем как пробудить поток и вернуть его из состояния ожидания.
        pthread_mutex_unlock(&mutx); // Освобождение мьютекса
    }

    return NULL;
}

void *producer(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutx);  // Захват мьютекса
        add_data(data); // Условная работа с данными
        pthread_mutex_unlock(&mutx);    // Освобождение мьютекса
        pthread_cond_signal(&cv);   // Посылка сигнала об изменении условий
    }

    return NULL;
}