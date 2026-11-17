/**
 * Codeforces Round 909 (Div. 3)
 * 
 * => G. Unusual Entertainment ( @c 1900 )
 * 
 * -> https://codeforces.com/contest/1899/problem/G
 * 
 * Submissions ~> https://codeforces.com/contest/1899/submission/234032338 By huanhuanonly
 * 
 * @b Merge-sort-tree
 * 
 * ----November 24, 2023 [15h:16m:51s]----
*/

#include <bits/stdc++.h>

using uint = unsigned;
using llong = long long;
using ullong = unsigned long long;

class MergeSortTree
{
public:
    std::vector<std::vector<int>> tree;

    std::vector<int> arr;

    explicit MergeSortTree(std::size_t n)
        : tree(n << 2), arr(n + 1) { }

    static constexpr inline std::size_t ls(std::size_t p) { return p << 1; }
    static constexpr inline std::size_t rs(std::size_t p) { return p << 1 | 1; }

    void build(int p, int l, int r)
    {
        if (l == r)
        {
            tree[p] = { arr[l] };
            return;
        }

        int mid = l + r >> 1;
        build(ls(p), l, mid);
        build(rs(p), mid + 1, r);

        std::merge(tree[ls(p)].begin(), tree[ls(p)].end(),
                   tree[rs(p)].begin(), tree[rs(p)].end(),
                   std::back_inserter(tree[p]));
        return;
    }

    bool count(int p, int l, int r, int x, int y, std::pair<int, int> value)
    {
        if (x <= l and r <= y)
        {
            return std::lower_bound(tree[p].begin(), tree[p].end(), value.second)
                 - std::lower_bound(tree[p].begin(), tree[p].end(), value.first);
        }

        int mid = l + r >> 1;
        bool sum = false;
        if (x <= mid)
            sum |= count(ls(p), l, mid, x, y, value);
        if (y > mid)
            sum |= count(rs(p), mid + 1, r, x, y, value);

        return sum;
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, q;
        std::cin >> n >> q;

        MergeSortTree tree(n);

        std::vector<int> e[n + 1];

        int u, v;
        for (int i = 1; i < n; ++i)
        {
            std::cin >> u >> v;
            e[u].push_back(v);
            e[v].push_back(u);
        }

        std::vector<int> tin(n + 1), tout(n + 1);
        int ctime = 1;

        std::vector<bool> vis(n + 1);
        std::function<void(int)> dfs = [&](int x) -> void
        {
            tin[x] = ctime++;
            for (const auto& i : e[x])
            {
                if (vis[i]) continue;

                vis[i] = true;
                tin[i] = ctime;

                dfs(i);
            }
            tout[x] = ctime;
            return;
        };

        vis[1] = true;
        dfs(1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> tree.arr[i];
            tree.arr[i] = tin[tree.arr[i]];
        }

        tree.build(1, 1, n);

        while (q--)
        {
            int l, r, x;
            std::cin >> l >> r >> x;

            if (tree.count(1, 1, n, l, r, std::make_pair(tin[x], tout[x])))
                std::cout << "YES\n";
            else
                std::cout << "NO\n";
        }
        std::cout << '\n';
    }

    return 0;
}