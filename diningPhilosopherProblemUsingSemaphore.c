#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
#define LEFT (i + 4) % N
#define RIGHT (i + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2
sem_t spoon;
sem_t S[N];
int state[N]; // state of a philosopher

int i;
int num;

void *philosopher(void *arg);
void take_spoon(int i);
void put_spoon(int i);
void test(int i);

void *philosopher(void *arg)
{
    int i = *((int *)arg);
    while (1)
    {
        sleep(1);
        take_spoon(i);
        sleep(2);
        put_spoon(i);
        sleep(1);
    }
}

void take_spoon(int i)
{
    sem_wait(&spoon);
    state[i] = HUNGRY;
    printf("philosopher %d is hungry\n", i + 1);
    test(i);
    sem_post(&spoon);
    sem_wait(&S[i]);
}
void put_spoon(int i)
{
    sem_wait(&spoon);
    state[i] = THINKING;
    printf("philosopher % d puts down spoon % d and % d \n", i + 1, LEFT + 1, i + 1);
    printf("philosopher %d thinks\n", i + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&spoon);
}
void test(int i)
{
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[i] = EATING;
        printf("philosopher % d takes spoon % d and % d\n", i + 1, LEFT + 1, i + 1);
        printf("philosopher % d eats\n", i + 1);
        sem_post(&S[i]);
    }
}

int main(void)
{
    sem_init(&spoon, 0, 1);
    for (int i = 0; i < N; i++)
    {
        sem_init(&S[i], 0, 1);
    }
    pthread_t phil[N];
    int a[N] = {0, 1, 2, 3, 4}; // For numbering of philosophers
    for (int i = 0; i < N; i++)
    {
        pthread_create(&phil[i], NULL, philosopher, (void *)&a[i]);
    }
    for (int i = 0; i < N; i++)
    {
        pthread_join(phil[i], NULL);
    }
    return 0;
}