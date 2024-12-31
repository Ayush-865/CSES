#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(void)
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> cost(n + 1, INT_MAX);
    vector<int> parent(n + 1, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({1, 1});
    cost[1] = 1;

    while (!pq.empty())
    {
        int weight = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (node == n)
            break;

        for (auto neighbor : adj[node])
        {
            if (weight + 1 < cost[neighbor])
            {
                cost[neighbor] = weight + 1;
                parent[neighbor] = node;
                pq.push({cost[neighbor], neighbor});
            }
        }
    }

    if (cost[n] == INT_MAX)
        cout << "IMPOSSIBLE" << endl;
    else
    {
        cout << cost[n] << endl;
        vector<int> ans;
        int curr = n;
        while (curr != -1)
        {
            ans.push_back(curr);
            curr = parent[curr];
        }
        reverse(ans.begin(), ans.end());
        for (auto num : ans)
            cout << num << " ";
        cout << endl;
    }
}