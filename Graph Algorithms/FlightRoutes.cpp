#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(void)
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;
        adj[from].push_back({to, cost});
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 1});

    vector<int> vis(n + 1, 0);

    while (!pq.empty() && vis[n] < k)
    {
        int cost = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        vis[node]++;

        if (node == n)
        {
            cout << cost << " ";
        }

        if (vis[node] > k)
            continue;

        for (auto neighbor : adj[node])
        {
            int neighbor_node = neighbor.first;
            int neighbor_cost = neighbor.second;
            pq.push({cost + neighbor_cost, neighbor_node});
        }
    }
}