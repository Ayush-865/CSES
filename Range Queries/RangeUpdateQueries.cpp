#include <bits/stdc++.h>
using namespace std;

#define int long long

class ST
{
private:
    vector<int> st, lazy;

    void build(int node, int start, int end, vector<int> &nums)
    {
        if (start == end)
        {
            st[node] = nums[start];
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid, nums);
        build(2 * node + 1, mid + 1, end, nums);
        st[node] = st[2 * node] + st[2 * node + 1];
    }

    void propogate(int node, int start, int end)
    {
        if (lazy[node] == 0)
            return;
        st[node] += (end - start + 1) * lazy[node];
        if (start != end)
        {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

public:
    void rangeUpdate(int node, int start, int end, int l, int r, int value)
    {
        propogate(node, start, end);
        if (start > r || end < l)
            return;
        if (start >= l && end <= r)
        {
            st[node] += (end - start + 1) * value;
            if (start != end)
            {
                lazy[2 * node] += value;
                lazy[2 * node + 1] += value;
            }
            return;
        }
        int mid = (start + end) / 2;
        rangeUpdate(2 * node, start, mid, l, r, value);
        rangeUpdate(2 * node + 1, mid + 1, end, l, r, value);
        st[node] = st[2 * node] + st[2 * node + 1];
    }

    int query(int node, int start, int end, int index)
    {
        propogate(node, start, end);
        if (start == end)
            return st[node];
        int mid = (start + end) / 2;
        if (index <= mid)
            return query(2 * node, start, mid, index);
        return query(2 * node + 1, mid + 1, end, index);
    }

    ST(vector<int> &nums)
    {
        int n = nums.size();
        st.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(1, 0, n - 1, nums);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> nums(n);
    vector<vector<int>> queries(q, vector<int>(4));
    for (int i = 0; i < n; i++)
        cin >> nums[i];
    for (int i = 0; i < q; i++)
    {
        cin >> queries[i][0];
        if (queries[i][0] == 1)
            cin >> queries[i][1] >> queries[i][2] >> queries[i][3];
        else
            cin >> queries[i][1];
    }

    ST st(nums);

    for (auto query : queries)
    {
        if (query[0] == 1)
            st.rangeUpdate(1, 0, n - 1, query[1] - 1, query[2] - 1, query[3]);
        else
            cout << st.query(1, 0, n - 1, query[1] - 1) << endl;
    }
}

int32_t main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
