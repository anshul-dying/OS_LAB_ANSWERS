#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m], need[n][m], finish[n], safe[n];

    printf("Enter Allocation Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for(i=0;i<m;i++)
        scanf("%d", &avail[i]);

    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            need[i][j] = max[i][j] - alloc[i][j];

    for(i=0;i<n;i++) finish[i] = 0;
    int count = 0;

    while(count < n) {
        int found = 0;
        for(i=0;i<n;i++) {
            if(finish[i] == 0) {
                for(j=0;j<m;j++)
                    if(need[i][j] > avail[j])
                        break;

                if(j == m) {
                    for(k=0;k<m;k++) avail[k] += alloc[i][k];
                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if(!found) {
            printf("System is Not Safe\n");
            return 0;
        }
    }

    printf("Safe Sequence: ");
    for(i=0;i<n;i++) printf("P%d ", safe[i]);
}
