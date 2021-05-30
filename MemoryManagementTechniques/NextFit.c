#include <stdio.h>

int main()
{
    int p, m;
    printf("Enter number of partitions in memory : ");
    scanf("%d", &m);
    printf("Partitions in Memory :\n");
    int marr[m];
    for (int i = 0; i < m; i++)
        scanf("%d", &marr[i]);
    printf("Enter number of processes :");
    scanf("%d", &p);
    int parr[p];
    for (int i = 0; i < p; i++)
        scanf("%d", &parr[i]);
    printf("\nPartitions in Memory :\n");
    for (int k = 0; k < m; k++)
    {
        printf("memory[%d] : %d\n", k, marr[k]);
    }
    int j = 0;
    int c = 0;
    for (int i = 0; i < p; i++)
    {
        printf("\nFor Process %d (%d)\n", i + 1, parr[i]);
        for (c = 0; c < m; j = (j + 1) % m, c++)
        {
            printf("\tmemory[%d] : ", j);
            if (marr[j] >= parr[i])
            {
                marr[j] -= parr[i];
                printf("YES\n");
                break;
            }
            printf("NO\n");
        }
        if (c == m)
        {
            printf("Not enough memory for Process %d", i);
            break;
        }
        else
        {
            printf("\tNow Partitions in Memory :\n");
            for (int k = 0; k < m; k++)
            {
                printf("\tmemory[%d] : %d\n", k, marr[k]);
            }
        }
    }
}