#include <bits/stdc++.h>
using namespace std;

void priority_non_preemptive() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> at(n), bt(n), pr(n), ct(n), tat(n), wt(n);

    int ppr;
    cout << "Lower = higher priority: 1\nHigher = higher priority: 2 ---> ";
    cin >> ppr;

    cout << "\nEnter AT, BT, Priority:\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << " AT: ";
        cin >> at[i];
        cout << "P" << i+1 << " BT: ";
        cin >> bt[i];
        cout << "P" << i+1 << " Priority: ";
        cin >> pr[i];
    }

    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;

    sort(order.begin(), order.end(),
        [&](int a, int b){ return at[a] < at[b]; });

    // Choose comparator lambda BEFORE creating PQ
    function<bool(pair<int,int>, pair<int,int>)> cmp;

    if (ppr == 1) {
        // MIN-HEAP
        cmp = [](pair<int,int> a, pair<int,int> b) {
            return a > b; 
        };
    } else {
        // MAX-HEAP
        cmp = [](pair<int,int> a, pair<int,int> b) {
            return a < b;
        };
    }

    priority_queue<pair<int,int>,
                   vector<pair<int,int>>,
                   decltype(cmp)> pq(cmp);

    int time = 0, i = 0, completed = 0;

    while (completed < n) {

        while (i < n && at[order[i]] <= time) {
            int pid = order[i];
            pq.push({pr[pid], pid});
            i++;
        }

        if (pq.empty()) {
            time++;
            continue;
        }

        auto top = pq.top();
        pq.pop();

        int pid = top.second;

        time += bt[pid];
        ct[pid] = time;
        tat[pid] = ct[pid] - at[pid];
        wt[pid]  = tat[pid] - bt[pid];

        completed++;
    }

    cout << "\n\n--- Priority Scheduling (Non-Preemptive) ---\n";
    cout << "P\tAT\tBT\tPR\tCT\tWT\tTAT\n";
    cout << "------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << pr[i] << "\t"
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
    priority_non_preemptive();
    return 0;
}
