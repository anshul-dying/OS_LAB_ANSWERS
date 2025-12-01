#include <bits/stdc++.h>
using namespace std;

void round_robin() {
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter Time Quantum: ";
    cin >> tq;

    vector<int> at(n), bt(n), rt(n), ct(n), tat(n), wt(n);

    cout << "\nEnter Arrival Time (AT) and Burst Time (BT):\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << " AT: ";
        cin >> at[i];
        cout << "P" << i+1 << " BT: ";
        cin >> bt[i];
        rt[i] = bt[i];
    }

    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;

    sort(order.begin(), order.end(),
         [&](int a, int b) { return at[a] < at[b]; });

    queue<int> q;
    int time = 0, i = 0, completed = 0;

    while (i < n && at[order[i]] <= time) {
        q.push(order[i]);
        i++;
    }

    while (completed < n) {
        if (q.empty()) {
            time++;
            while (i < n && at[order[i]] <= time) {
                q.push(order[i]);
                i++;
            }
            continue;
        }

        int pid = q.front();
        q.pop();

        int exec = min(tq, rt[pid]);
        rt[pid] -= exec;
        time += exec;

        while (i < n && at[order[i]] <= time) {
            q.push(order[i]);
            i++;
        }

        if (rt[pid] > 0) {
            q.push(pid);
        } else {
            ct[pid] = time;
            completed++;
        }
    }

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i]  = tat[i] - bt[i];
    }

    cout << "\n\n--- Round Robin Scheduling ---\n";
    cout << "P\tAT\tBT\tCT\tWT\tTAT\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage WT : " 
         << accumulate(wt.begin(), wt.end(), 0.0)/n;
    cout << "\nAverage TAT: " 
         << accumulate(tat.begin(), tat.end(), 0.0)/n << endl;
}

int main() {
    round_robin();
    return 0;
}
