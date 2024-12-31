#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(void)
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> vis(n, 0);
    int count = 0;
    vector<pair<int, int>> ans;
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            count++;
            if (i != 0)
                ans.push_back({i - 1, i});
            vis[i] = 1;
            q.push(i);

            while (!q.empty())
            {
                int node = q.front();
                q.pop();
                for (auto neighbor : adj[node])
                {
                    if (!vis[neighbor])
                    {
                        vis[neighbor] = 1;
                        q.push(neighbor);
                    }
                }
            }
        }
    }

    cout << count - 1 << endl;
    for (auto pair : ans)
        cout << pair.first + 1 << " " << pair.second + 1 << endl;
}