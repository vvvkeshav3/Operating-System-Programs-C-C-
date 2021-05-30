#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define BufferSize 3 // Size of the buffer
sem_t empty; // Counting Semaphore
sem_t full; // Counting semaphore
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex; // Binary Semaphore

void *producer(void *pno)
{
    //Entry Section
    int item = rand(); 
    sem_wait(&empty); 
    pthread_mutex_lock(&mutex);

        //Critical Section
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in);
        in = (in + 1) % BufferSize;
        // End of Critical Section
    
    // Exit Section
    pthread_mutex_unlock(&mutex);
    sem_post(&full);

}

void *consumer(void *cno)
{
    // Entry Section
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

        // Critical Section
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n", *((int *)cno), item, out);
        out = (out + 1) % BufferSize;
        // End of Critical Section

    // Exit Section    
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);

}
int main()
{
    pthread_t pro[5], con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);

    int a[5] = {1, 2, 3, 4, 5}; //used for numbering the producer and consumer

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&pro[i], NULL, producer, (void *)&a[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&con[i], NULL, consumer, (void *)&a[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(pro[i], NULL);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(con[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}