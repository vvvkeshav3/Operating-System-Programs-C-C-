#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t db;
pthread_mutex_t mutex;
int value = 1;
int rc = 0;

void *writer(void *wno)
{
    sem_wait(&db); // down(db)
    value = value * 2;
    printf("Writer %d modified value to %d\n", (*((int *)wno)), value);
    sleep(0.1);
    sem_post(&db); // up(db)
}
void *reader(void *rno)
{

    pthread_mutex_lock(&mutex); // down(mutex)
    rc = rc + 1;
    if (rc == 1)
    {
        sem_wait(&db); // down(db)
        // when first reader came now writer can't come
    }
    pthread_mutex_unlock(&mutex); // up(mutex)

    // Reading Section
    printf("Reader %d: read value as %d\n", *((int *)rno), value);
    sleep(0.2);

    pthread_mutex_lock(&mutex); // down(mutex)
    rc--;
    if (rc == 0)
    {
        sem_post(&db); // up(db)
        // after this there is no reader, so now writer can come
    }
    pthread_mutex_unlock(&mutex); // up(mutex)
}

int main()
{

    pthread_t read[10], write[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&db, 0, 1);

    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++)
    {
        pthread_create(&read[i], NULL, reader, (void *)&a[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&write[i], NULL, writer, (void *)&a[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_join(read[i], NULL);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&db);

    return 0;
}