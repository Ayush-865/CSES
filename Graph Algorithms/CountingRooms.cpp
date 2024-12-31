#include <bits/stdc++.h>
using namespace std;

#define int long long

void dfs(int row, int col, int n, int m, vector<vector<int>> &vis, vector<vector<char>> &a)
{
    vis[row][col] = 1;
    int drow[4] = {0, -1, 0, 1};
    int dcol[4] = {-1, 0, 1, 0};

    for (int i = 0; i < 4; i++)
    {
        int nrow = row + drow[i];
        int ncol = col + dcol[i];

        if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && a[nrow][ncol] == '.' && vis[nrow][ncol] == 0)
        {
            dfs(nrow, ncol, n, m, vis, a);
        }
    }
}

int32_t main(void)
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n, vector<char>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];

    vector<vector<int>> vis(n, vector<int>(m, 0));

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (vis[i][j] == 0 && a[i][j] == '.')
            {
                count++;
                dfs(i, j, n, m, vis, a);
            }
        }
    }
    cout << count << endl;
}