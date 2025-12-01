#include <stdio.h>

int main() {
    int n, f, i, j, k, pageFaults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter reference string: ");
    for(i=0;i<n;i++) scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frames[f], counter = 0, time[f];
    for(i=0;i<f;i++) frames[i] = -1;

    for(i=0;i<n;i++) {
        int found = 0;
        for(j=0;j<f;j++)
            if(frames[j] == pages[i]) {
                found = 1;
                time[j] = counter++;
            }

        if(!found) {
            int lru = 0;
            for(j=1;j<f;j++)
                if(time[j] < time[lru])
                    lru = j;

            frames[lru] = pages[i];
            time[lru] = counter++;
            pageFaults++;
        }
    }

    printf("Total Page Faults = %d\n", pageFaults);
}
