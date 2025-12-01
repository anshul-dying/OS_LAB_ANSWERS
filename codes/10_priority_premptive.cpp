#include <bits/stdc++.h>
using namespace std;

void priority_preemptive() {

    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> at(n), bt(n), rt(n), pr(n); 
    vector<int> ct(n), tat(n), wt(n);

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
        rt[i] = bt[i];  // remaining time
    }

    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;

    sort(order.begin(), order.end(),
         [&](int a, int b) { return at[a] < at[b]; });

    function<bool(pair<int,int>, pair<int,int>)> cmp;

    if (ppr == 1) {
        // MINHEAP
        cmp = [](pair<int,int> a, pair<int,int> b) {
            return a > b;
        };
    } else {
        // MAXHEAP
        cmp = [](pair<int,int> a, pair<int,int> b) {
            return a < b;
        };
    }

    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);

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

        rt[pid]--;
        time++;

        while (i < n && at[order[i]] <= time) {
            pq.push({pr[order[i]], order[i]});
            i++;
        }

        if (rt[pid] > 0) {
            pq.push({pr[pid], pid});
        } else {
            ct[pid] = time;
            completed++;
        }
    }

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i]  = tat[i] - bt[i];
    }

    cout << "\n\n--- Priority Scheduling (Preemptive) ---\n";
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
    cout << "\nAverage WT : " << accumulate(wt.begin(), wt.end(), 0.0) / n;
    cout << "\nAverage TAT: " << accumulate(tat.begin(), tat.end(), 0.0) / n << endl;
}

int main() {
    priority_preemptive();
    return 0;
}
