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

    for(i=0;i<n;i++) {
        int found = 0;
        for(j=0;j<f;j++)
            if(frames[j] == pages[i])
                found = 1;

        if(!found) {
            int replace = -1, farthest = -1;
            for(j=0;j<f;j++) {
                int next_use = -1;
                for(k=i+1;k<n;k++)
                    if(frames[j] == pages[k]) {
                        next_use = k;
                        break;
                    }
                if(next_use == -1) {
                    replace = j;
                    break;
                }
                if(next_use > farthest) {
                    farthest = next_use;
                    replace = j;
                }
            }
            frames[replace] = pages[i];
            pageFaults++;
        }
    }

    printf("Total Page Faults = %d\n", pageFaults);
}
