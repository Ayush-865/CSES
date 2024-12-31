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

    vector<int> ans(n + 1, -1);
    queue<int> q;
    q.push(1);

    bool possible = true;
    for (int i = 1; i <= n; i++)
    {
        if (ans[i] == -1)
        {
            q.push(i);
            ans[i] = 1;
            while (!q.empty())
            {
                int node = q.front();
                q.pop();
                for (auto neighbor : adj[node])
                {
                    if (ans[neighbor] == -1)
                    {
                        ans[neighbor] = ans[node] == 1 ? 2 : 1;
                        q.push(neighbor);
                    }
                    else if (ans[neighbor] == ans[node])
                    {
                        possible = false;
                        break;
                    }
                }
                if (!possible)
                    break;
            }
        }
        if (!possible)
            break;
    }

    if (possible)
        for (int i = 1; i <= n; i++)
            cout << ans[i] << " ";
    else
        cout << "IMPOSSIBLE" << endl;
}