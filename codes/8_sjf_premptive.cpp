#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
#include <iomanip>
using namespace std;

void srtf() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> at(n), bt(n), rt(n);  // rt = remaining time
    vector<int> ct(n), tat(n), wt(n);

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

    sort(order.begin(), order.end(), [&](int a, int b){ return at[a] < at[b]; });

    priority_queue< pair<int, int>,
                    vector<pair<int,int>>,
                    greater<pair<int,int>>
                    > pq;

    int time = 0, completed = 0, i = 0;

    while(completed < n)
    {
        while(i < n && at[order[i]] <= time)
        {
            pq.push({rt[order[i]], order[i]});
            i++;
        }

        pair<int,int> top = pq.top();
        pq.pop();

        int rem = top.first;
        int pid = top.second;

        time++;
        rem--;

        while(i < n && at[order[i]] <= time)
        {
            pq.push({rt[order[i]], order[i]});
            i++;
        }

        if(rem > 0)
        {
            pq.push({rem, pid});
        }
        else
        {
            ct[pid] = time;
            completed++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    cout << "\n\n--- SJF Preemptive (SRTF) Scheduling Results ---\n";
    cout << "P\tAT\tBT\tCT\tWT\tTAT\n";
    cout << "----------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage WT: "
         << accumulate(wt.begin(), wt.end(), 0.0) / n;
    cout << "\nAverage TAT: "
         << accumulate(tat.begin(), tat.end(), 0.0) / n << endl;
}

int main() {
    srtf();
    return 0;
}
