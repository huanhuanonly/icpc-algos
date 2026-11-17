/**
 * Educational Codeforces Round 47 (Rated for Div. 2)
 *
 * => F. Dominant Indices ( @c 2300 )
 *
 * -> https://codeforces.com/contest/1009/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/1009/submission/257176759 By huanhuanonly
 *
 * @b Dsu-on-tree
 *
 * ----April 18, 2024 [21h:25m:34s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class DsuOnTree
{
public:

    const std::vector<std::vector<int>>& e;

    struct node
    {
        int size, depth, wson;
    };

    std::vector<node> tree;

    std::vector<int> cnt, ans;

    int mx = 0;

    DsuOnTree(const std::vector<std::vector<int>>& __e)
        : e(__e), tree(__e.size()), cnt(__e.size()), ans(__e.size()) { build(1, 1); }

    void build(int u, int fa)
    {
        tree[u].size = 1;
        tree[u].depth = tree[fa].depth + 1;

        for (const auto& i : e[u])
        {
            if (i == fa)
                continue;

            build(i, u);

            tree[u].size += tree[i].size;

            if (tree[i].size > tree[tree[u].wson].size)
                tree[u].wson = i;
        }
    }

    void count(int u, int fa, int wson)
    {
        ++cnt[tree[u].depth];

        if (cnt[tree[u].depth] > cnt[mx])
            mx = tree[u].depth;
        else if (cnt[tree[u].depth] == cnt[mx])
            mx = std::min(mx, tree[u].depth);

        for (const auto& i : e[u])
        {
            if (i == fa or i == wson)
                continue;

            count(i, u, wson);
        }
    }

    void clear(int u, int fa)
    {
        --cnt[tree[u].depth];

        for (const auto& i : e[u])
        {
            if (i == fa)
                continue;

            clear(i, u);
        }
    }

    void dfs(int u, int fa, bool flag)
    {
        for (const auto& i : e[u])
        {
            if (i == fa or i == tree[u].wson)
                continue;

            dfs(i, u, false);
        }

        if (tree[u].wson)
            dfs(tree[u].wson, u, true);

        count(u, fa, tree[u].wson);

        ans[u] = mx - tree[u].depth;

        if (not flag)
        {
            mx = 0;
            clear(u, fa);
        }
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("Input.txt", "r", stdin);
    ::freopen("Output.txt", "w", stdout);
#endif

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    DsuOnTree tree(e);

    tree.dfs(1, 1, true);

    for (int i = 1; i <= n; ++i)
        std::cout << tree.ans[i] << '\n';

    return 0;
}