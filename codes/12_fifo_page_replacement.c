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

    int frames[f];
    for(i=0;i<f;i++) frames[i] = -1;

    j = 0;

    for(i=0;i<n;i++) {
        int found = 0;
        for(k=0;k<f;k++)
            if(frames[k] == pages[i])
                found = 1;

        if(!found) {
            frames[j] = pages[i];
            j = (j + 1) % f;
            pageFaults++;
        }
    }

    printf("Total Page Faults = %d\n", pageFaults);
}
