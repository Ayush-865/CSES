#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
class ST
{
private:
    vector<int> st;
 
    void build(int node, int start, int end, vector<int> &nums)
    {
        if (start == end)
        {
            st[node] = nums[start];
            return;
        }
        int mid = (start + end) / 2;
        build(node * 2 + 1, start, mid, nums);
        build(node * 2 + 2, mid + 1, end, nums);
        st[node] = min(st[node * 2 + 1], st[node * 2 + 2]);
    }
 
public:
    int query(int node, int start, int end, int l, int r)
    {
        if (start > r || end < l)
            return LLONG_MAX;
        if (l <= start && end <= r)
            return st[node];
        int mid = (start + end) / 2;
        return min(query(node * 2 + 1, start, mid, l, r), query(node * 2 + 2, mid + 1, end, l, r));
    }
 
    ST(vector<int> &nums)
    {
        int n = nums.size();
        st.resize(4 * n, LLONG_MAX);
        build(0, 0, n - 1, nums);
    }
};
 
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> nums(n);
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < n; i++)
        cin >> nums[i];
 
    for (int i = 0; i < q; i++)
        cin >> queries[i].first >> queries[i].second;
 
    ST st(nums);
 
    for (auto query : queries)
    {
        int l = query.first - 1;
        int r = query.second - 1;
        cout << st.query(0, 0, n - 1, l, r) << endl;
    }
}
 
int32_t main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
