#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(void)
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n, vector<char>(m));
    pair<int, int> start;
    pair<int, int> end;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> a[i][j];
            if (a[i][j] == 'A')
                start = {i, j};
            else if (a[i][j] == 'B')
                end = {i, j};
        }
    }
    vector<vector<int>> weight(n, vector<int>(m, INT_MAX));
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
    weight[start.first][start.second] = 0;

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    pq.push({0, {start.first, start.second}});

    int drow[4] = {0, -1, 0, 1};
    int dcol[4] = {-1, 0, 1, 0};
    char directions[4] = {'L', 'U', 'R', 'D'};

    while (!pq.empty())
    {
        int w = pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        if (a[x][y] == 'B')
            break;

        for (int i = 0; i < 4; i++)
        {
            int nrow = x + drow[i];
            int ncol = y + dcol[i];

            if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && (a[nrow][ncol] == '.' || a[nrow][ncol] == 'B') && w + 1 < weight[nrow][ncol])
            {
                weight[nrow][ncol] = w + 1;
                parent[nrow][ncol] = {x, y};
                pq.push({w + 1, {nrow, ncol}});
            }
        }
    }

    if (weight[end.first][end.second] != INT_MAX)
    {
        cout << "YES" << endl;
        cout << weight[end.first][end.second] << endl;

        pair<int, int> curr = end;
        vector<char> ans;
        while (curr != start)
        {
            pair<int, int> papa = parent[curr.first][curr.second];
            for (int i = 0; i < 4; i++)
            {
                if (papa.first + drow[i] == curr.first && papa.second + dcol[i] == curr.second)
                {
                    ans.push_back(directions[i]);
                }
            }
            curr = papa;
        }
        reverse(ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); i++)
            cout << ans[i];
    }
    else
        cout << "NO" << endl;
}