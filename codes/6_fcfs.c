#include <stdio.h>

int main()
{
    int n, i;
    printf("Enter no. of process: ");
    scanf("%d", &n);

    int bt[n], wt[n], tat[n];
    printf("Enter burst times: ");
    for(int i = 0; i < n; i++) scanf("%d", &bt[i]);

    wt[0] = 0;
    for(int i = 1; i < n; i++)
        wt[i] = wt[i-1] + bt[i-1];

    for(int i = 0; i < n; i++)
        tat[i] = wt[i] + bt[i];

    printf("Process\tBT\tWT\tTAT\n");
    for(int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\n", i+1, bt[i], wt[i], tat[i]);
}