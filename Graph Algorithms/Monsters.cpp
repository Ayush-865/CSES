#include <bits/stdc++.h>
using namespace std;

int32_t main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> path(n, vector<char>(m));
    vector<pair<int, int>> monsters;
    pair<int, int> start;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> path[i][j];
            if (path[i][j] == 'M')
                monsters.push_back({i, j});
            else if (path[i][j] == 'A')
                start = {i, j};
        }
    }

    vector<vector<int>> mosters_time(n, vector<int>(m, INT_MAX));
    queue<tuple<int, int, int>> q;
    for (auto monster : monsters)
    {
        int x = monster.first;
        int y = monster.second;
        mosters_time[x][y] = 0;
        q.push({0, x, y});
    }

    int drow[4] = {0, -1, 0, 1};
    int dcol[4] = {-1, 0, 1, 0};
    char dir[4] = {'L', 'U', 'R', 'D'};

    while (!q.empty())
    {
        int time, row, col;
        tie(time, row, col) = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nrow = row + drow[i];
            int ncol = col + dcol[i];
            if (nrow < 0 || nrow > n - 1 || ncol < 0 || ncol > m - 1 || time + 1 >= mosters_time[nrow][ncol] || path[nrow][ncol] == '#')
                continue;
            mosters_time[nrow][ncol] = time + 1;
            q.push({mosters_time[nrow][ncol], nrow, ncol});
        }
    }

    vector<vector<int>> time(n, vector<int>(m, INT_MAX));
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
    time[start.first][start.second] = 0;
    q.push({0, start.first, start.second});

    bool possible = false;
    pair<int, int> end_node;
    while (!q.empty())
    {
        int weight, row, col;
        tie(weight, row, col) = q.front();
        q.pop();

        if (row == 0 || row == n - 1 || col == 0 || col == m - 1)
        {
            possible = true;
            end_node = {row, col};
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int nrow = row + drow[i];
            int ncol = col + dcol[i];
            if (nrow < 0 || nrow > n - 1 || ncol < 0 || ncol > m - 1 || weight + 1 > time[nrow][ncol] || weight + 1 >= mosters_time[nrow][ncol] || path[nrow][ncol] == '#')
                continue;
            time[nrow][ncol] = weight + 1;
            parent[nrow][ncol] = {row, col};
            q.push({time[nrow][ncol], nrow, ncol});
        }
    }

    if (possible)
    {
        stack<char> s;
        while (parent[end_node.first][end_node.second].first != -1 && parent[end_node.first][end_node.second].second != -1)
        {
            int par_row = parent[end_node.first][end_node.second].first;
            int par_col = parent[end_node.first][end_node.second].second;
            for (int i = 0; i < 4; i++)
            {
                if (par_row + drow[i] == end_node.first && par_col + dcol[i] == end_node.second)
                {
                    s.push(dir[i]);
                    break;
                }
            }
            end_node = {par_row, par_col};
        }
        cout << "YES" << endl;
        cout << s.size() << endl;
        while (!s.empty())
        {
            cout << s.top();
            s.pop();
        }
    }
    else
        cout << "NO" << endl;
}