#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(void)
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int start, end, cost;
        cin >> start >> end >> cost;
        adj[start].push_back({end, cost});
    }

    vector<int> cost(n + 1, LLONG_MAX);
    cost[1] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 1});

    while (!pq.empty())
    {
        int weight = pq.top().first;
        int city = pq.top().second;
        pq.pop();

        if (weight > cost[city])
            continue;

        for (auto neighbor : adj[city])
        {
            int neighbor_city = neighbor.first;
            int neighbor_cost = neighbor.second;
            if (neighbor_cost + weight < cost[neighbor_city])
            {
                cost[neighbor_city] = neighbor_cost + weight;
                pq.push({neighbor_cost + weight, neighbor_city});
            }
        }
    }

    for (int i = 1; i <= n; i++)
        cout << (cost[i] == LLONG_MAX ? -1 : cost[i]) << ' ';
}