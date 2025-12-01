#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
#include <iomanip>
using namespace std;

void sjf_non_preemptive() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> at(n), bt(n), ct(n), tat(n), wt(n);

    cout << "\nEnter Arrival Time (AT) and Burst Time (BT):\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << " AT: ";
        cin >> at[i];
        cout << "P" << i+1 << " BT: ";
        cin >> bt[i];
    }

    // Sort processes by arrival time
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;

    sort(order.begin(), order.end(), [&](int a, int b){return at[a] < at[b];});

    priority_queue<pair<int,int>, 
                    vector<pair<int,int>>, 
                    greater<pair<int,int>>
                > pq;

    int time = 0, i = 0, completed = 0;

    while(completed < n)
    {
        while(i < n && at[order[i]] <= time)
        {
            int pid = order[i];
            pq.push({bt[pid], pid});
            i++;
        }

        if(pq.empty())
        {
            time++;
            continue;
        }

        pair<int,int> top = pq.top();
        pq.pop();

        int burst = top.first;
        int pid = top.second;
        
        time += burst;
        ct[pid] = time;
        tat[pid] = ct[pid]-at[pid];
        wt[pid] = tat[pid]-bt[pid];

        completed++;
    }



    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "-----------------------------------------------------------------\n";

    for(int i = 0; i < n; i++)
    {
        cout << "P" << i+1 << '\t'
             << at[i] << '\t'
             << bt[i] << '\t'
             << ct[i] << '\t'
             << tat[i] << '\t'
             << wt[i] << '\n';
    }
}

int main() {
    sjf_non_preemptive();
    return 0;
}
