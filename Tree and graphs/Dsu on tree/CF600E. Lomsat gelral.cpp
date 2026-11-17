/**
 * Educational Codeforces Round 2
 *
 * => E. Lomsat gelral ( @c 2300 )
 *
 * -> https://codeforces.com/contest/600/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/600/submission/256024109 By huanhuanonly
 *
 * @b Dsu-on-tree
 *
 * ----April 11, 2024 [00h:24m:54s]----
*/

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class DsuOnTree
{
public:

    std::vector<std::vector<int>>& e;
    const std::vector<int>& c;

    struct node
    {
        int size, wson;
    };

    std::vector<node> tree;

    std::vector<ullong> cnt, ans;

    ullong sum = 0, mx = 0;

    explicit DsuOnTree(std::vector<std::vector<int>>& __e, const std::vector<int>& __c)
        : e(__e), c(__c), tree(__e.size()), cnt(__e.size()), ans(__e.size())
    {
        build(1, 1);
    }

    void build(int p, int fa)
    {
        tree[p].size = 1;

        for (const auto& i : e[p])
        {
            if (i == fa)
                continue;

            build(i, p);

            tree[p].size += tree[i].size;

            if (tree[i].size > tree[tree[p].wson].size)
                tree[p].wson = i;
        }
    }

    void count(int p, int fa, int wson)
    {
        ++cnt[c[p]];

        if (cnt[c[p]] > mx)
            sum = c[p];
        else if (cnt[c[p]] == mx)
            sum += c[p];

        mx = std::max(mx, cnt[c[p]]);

        for (const auto& i : e[p])
        {
            if (i == fa or i == wson)
                continue;

            count(i, p, wson);
        }
    };

    void clear(int p, int fa)
    {
        --cnt[c[p]];
        for (const auto& i : e[p])
        {
            if (i == fa)
                continue;

            clear(i, p);
        }
    };

    void dfs(int p, int fa, bool flag)
    {
        for (const auto& i : e[p])
        {
            if (i == fa or i == tree[p].wson)
                continue;

            dfs(i, p, false);
        }

        if (tree[p].wson)
            dfs(tree[p].wson, p, true);

        count(p, fa, tree[p].wson);
        ans[p] = sum;

        if (flag == false)
        {
            sum = 0;
            mx = 0;
            clear(p, fa);
        }
    };
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

    std::vector<int> c(n + 1);

    for (int i = 1; i <= n; ++i)
        std::cin >> c[i];

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    DsuOnTree tree(e, c);

    tree.dfs(1, 1, true);

    for (int i = 1; i <= n; ++i)
        std::cout << tree.ans[i] << ' ';

    return 0;
}