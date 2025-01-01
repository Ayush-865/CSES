#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(void)
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, LLONG_MAX));
    for (int i = 1; i <= n; i++)
        dist[i][i] = 0;
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (dist[i][k] != LLONG_MAX && dist[k][j] != LLONG_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++)
        cin >> queries[i].first >> queries[i].second;

    for (auto query : queries)
    {
        int a, b;
        tie(a, b) = query;
        cout << (dist[a][b] == LLONG_MAX ? -1 : dist[a][b]) << endl;
    }
}