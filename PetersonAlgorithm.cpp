#include <iostream>
#include <pthread.h>
#include <atomic>
#include <unistd.h>
using namespace std;
#define count 5 //Number of times each process wants to access the critical section

bool flag1, flag2;
int turn;
void *fun1(void *arg)
{
    for (int i = 0; i < count; i++)
    {
        flag1 = true; //wants to be in the critical section
        turn = 2;     //allow other process to enter
        while (flag2 == true && turn == 2)
        {
            cout << "T1 is waiting \n";
            sleep(0.2);
        }

        //entered the critical section

        cout << "T1 is in the critical section\n";

        flag1 = 0;
    }
}
void *fun2(void *arg)
{
    for (int i = 0; i < count; i++)
    {
        flag2 = true; //wants to be in the critical section
        turn = 1;     //allow other process to enter
        while (flag1 == true && turn == 2)
        {
            cout << "T2 is waiting \n";
            sleep(0.2);
        }

        //entered the critical section

        cout << "T2 is in the critical section\n";

        flag2 = 0;
    }
}

int main()
{

    flag1 = flag2 = false;
    turn = 1;

    pthread_t t1, t2;
    pthread_create(&t1, NULL, &fun1, NULL);
    pthread_create(&t2, NULL, &fun2, NULL);

    pthread_exit(NULL);
}