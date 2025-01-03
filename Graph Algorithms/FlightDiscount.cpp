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
        int from, to, cost;
        cin >> from >> to >> cost;
        adj[from].push_back({to, cost});
    }

    vector<vector<int>> cost(n + 1, vector<int>(2, LLONG_MAX));
    cost[1][0] = 0;
    cost[1][1] = 0;

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    pq.push({0, 1, 1});

    while (!pq.empty())
    {
        int wt, city, has_coupon;
        tie(wt, city, has_coupon) = pq.top();
        pq.pop();

        if (wt > cost[city][has_coupon])
            continue;

        for (auto neighbor : adj[city])
        {
            int neighbor_city = neighbor.first;
            int neighbor_cost = neighbor.second;
            if (wt + neighbor_cost < cost[neighbor_city][has_coupon])
            {
                cost[neighbor_city][has_coupon] = wt + neighbor_cost;
                pq.push({cost[neighbor_city][has_coupon], neighbor_city, has_coupon});
            }
            if (has_coupon && wt + neighbor_cost / 2 < cost[neighbor_city][0])
            {
                cost[neighbor_city][0] = wt + neighbor_cost / 2;
                pq.push({cost[neighbor_city][0], neighbor_city, 0});
            }
        }
    }
    cout << min(cost[n][0], cost[n][1]) << endl;
    return 0;
}