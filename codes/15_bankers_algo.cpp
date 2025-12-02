#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, r;

    cout << "Enter no. of processes: ";
    cin >> n;

    cout << "Enter no. of resources: ";
    cin >> r;

    vector<vector<int>> alloc(n, vector<int>(r));
    vector<vector<int>> max(n, vector<int>(r));
    vector<int> avail(r);

    vector<int> f(n, 0);      // finished flag
    vector<int> ans(n);       // safe sequence
    int ind = 0;

    vector<vector<int>> need(n, vector<int>(r));

    // ---------------- INPUT ----------------
    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            cin >> alloc[i][j];

    cout << "\nEnter Max Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            cin >> max[i][j];

    cout << "\nEnter Available Resources:\n";
    for (int j = 0; j < r; j++)
        cin >> avail[j];

    // ---------------- CALCULATE NEED MATRIX ----------------
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // ---------------- SAFETY ALGORITHM ----------------
    int completed = 0;  // count how many processes finished

    for (int k = 0; k < n; k++) {

        bool allocated_in_this_round = false; // detect unsafeness

        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {  // process not finished
                bool can_allocate = true;

                // check if need <= available
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    // add to safe sequence
                    ans[ind++] = i;

                    // release allocated resources
                    for (int j = 0; j < r; j++)
                        avail[j] += alloc[i][j];

                    f[i] = 1; // mark finished
                    completed++;
                    allocated_in_this_round = true;
                }
            }
        }

        // If no process was allocated in this loop : UNSAFE
        if (!allocated_in_this_round) {
            break;
        }
    }

    // ---------------- CHECK SAFE OR UNSAFE ----------------
    if (completed == n) {
        cout << "\nSystem is in a SAFE state.\n";
        cout << "Safe Sequence: ";

        for (int i = 0; i < n - 1; i++)
            cout << "P" << ans[i] << " -> ";

        cout << "P" << ans[n - 1] << endl;
    }
    else {
        cout << "\nSystem is NOT in a safe state.\n";
        cout << "No safe sequence exists!" << endl;
    }

    return 0;
}
