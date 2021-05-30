#include <stdio.h>
#include <process.h>

void main()
{
    int allocation[10][5], max[10][5], need[10][5], available[3], flag[10], sq[10];
    int n, r, i, j, k, count, count1 = 0;
    printf("Input the number of processes running ( <10 ) : ");
    scanf("%d", &n);
    for (i = 0; i < 10; i++)
        flag[i] = 0;
    printf("Input the number of resources ( <5 ) : ");
    scanf("%d", &r);
    printf("Input the allocation matrix for the processes in row major order..\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < r; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("Input the no. of resources that a process can maximum have..\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < r; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Input the no. of available instances of each resource..\n");
    for (i = 0; i < r; i++)
    {
        scanf("%d", &available[i]);
    }
    printf("\nThe need matrix is as follows : \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < r; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    int anyDone;
    do
    {
        anyDone = 0;
        for (i = 0; i < n; i++)
        {
            if (flag[i] == 0)
            {
                count = 0;
                for (j = 0; j < r; j++)
                {
                    if (available[j] >= need[i][j])
                        count++;
                }
                if (count == r)
                {
                    anyDone = 1;
                    count1++;
                    flag[i] = 1;
                    sq[count1 - 1] = i;
                    for (j = 0; j < r; j++)
                    {
                        available[j] = available[j] + allocation[i][j];
                    }
                }
            }
        }
        if (anyDone == 0)
            break;
        if (count1 == n)
            break;
    } while (1);
    if (count1 != n)
    {
        printf("\n---------------IT'S AN UNSAFE STATE---------------");
    }
    else
    {
        printf("\n *******************IT'S A SAFE STATE*******************");
        printf("\n The safe sequence is....\n");
        for (i = 0; i < n; i++)
            printf("\t P%d", sq[i]);
        printf("\n");
        printf("\n The available matrix is now : ");
        for (i = 0; i < r; i++)
            printf("\t %d", available[i]);
    }
}