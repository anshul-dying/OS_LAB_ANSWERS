#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
using namespace std;

void calculate_fcfs_AT() 
{
    int n;
    cout << "Enter no. of process: ";
    cin >> n;
    vector<int> at(n), bt(n);
    for(int i = 0; i < n; i++)
    {
        cout << "P" << i+1 << " AT: ";
        cin >> at[i];
        cout << "P" << i+1 << " BT: ";
        cin >> bt[i];
    }    

    vector<int> ct(n), tat(n), wt(n);
    vector<int> order(n);

    for(int i = 0; i < n; i++)
    {
        order[i] = i;
    }

    sort(order.begin(), order.end(), [&](int a, int b){return at[a] < at[b];});

    int time = 0;
    int idx = order[0];
    if(time < at[idx])
        time = at[idx];
    
    ct[idx] = time + bt[idx];
    tat[idx] = ct[idx] - at[idx];
    wt[idx] = tat[idx] - bt[idx];

    time = ct[idx];

    for(int i = 1; i < n; i++)
    {
        idx = order[i];
        if(time < at[idx])
            time = at[idx];
        
        ct[idx] = time + bt[idx];
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];

        time = ct[idx];
    }


    double total_wt = accumulate(wt.begin(), wt.end(), 0.0);

    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "-----------------------------------------------------\n";
    for(int i = 0; i < n; i++)
    {
        cout << "P" << i+1 << '\t' << at[i] << '\t' << bt[i] << '\t' << tat[i] << '\t' << wt[i] << '\n';
    }

    cout << endl;
    cout << "Avg WT: " << total_wt/n << endl;
}

int main() {
    calculate_fcfs_AT();
    return 0;
}
