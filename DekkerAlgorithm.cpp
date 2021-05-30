#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <atomic>
using namespace std;
#define count 5 //Number of times each process wants to access the critical section

bool flag1, flag2;
int turn;
void *fun1(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        flag1 = true; //wants to be in the critical section
        while (flag2 == true)
        {
            if (turn == 2)
            {
                flag1 = false;
                while (turn == 2)
                {
                    cout << "T1 is waiting \n";
                    sleep(0.5);
                }
            }
            flag1 = true;
        }

        //entered the critical section

        cout << "T1 is in the critical section\n";

        flag1 = 0;
        turn = 2;
    }
}
void *fun2(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        flag2 = true;
        while (flag1 == true)
        {
            if (turn == 1)
            {
                flag2 = false;
                while (turn == 1)
                {
                    cout << "T2 is waiting \n";
                    sleep(0.5);
                }
            }
            flag2 = true;
        }

        cout << "T2 is in the critical section\n";

        flag2 = 0;
        turn = 1;
    }
}

int main()
{
    flag1 = flag2 = false;
    turn = 1;

    pthread_t t1, t2;
    pthread_create(&t1, NULL, fun1, NULL);
    pthread_create(&t2, NULL, fun2, NULL);

    pthread_exit(NULL);
}
