/**
 * Codeforces Round 383 (Div. 1)
 *
 * => D. Arpa’s letter-marked tree and Mehrdad’s Dokhtar-kosh paths ( @c 2900 )
 *
 * -> https://codeforces.com/contest/741/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/741/submission/257163166 By huanhuanonly
 *
 * @b Dsu-on-tree
 *
 * ----April 18, 2024 [19h:42m:34s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class DsuOnTree
{
public:

    std::vector<std::vector<std::pair<int, char>>>& e;

    struct node
    {
        int size, wson, depth, value;
    };

    std::vector<node> tree;

    std::vector<int> log;

    std::vector<int> ans;

    DsuOnTree(std::vector<std::vector<std::pair<int, char>>>& __e)
        : e(__e), tree(__e.size()), ans(__e.size()), log(1 << 22) { build(1, 1); }

    void build(int u, int fa)
    {
        tree[u].size = 1;
        tree[u].depth = tree[fa].depth + 1;

        for (const auto& [i, j] : e[u])
        {
            if (i == fa)
                continue;

            tree[i].value = tree[u].value ^ (1 << (j - 'a'));

            build(i, u);

            tree[u].size += tree[i].size;

            if (tree[i].size > tree[tree[u].wson].size)
                tree[u].wson = i;
        }
    }

    void add(int u, int fa)
    {
        if (log[tree[u].value])
            if (tree[u].depth > tree[log[tree[u].value]].depth)
                log[tree[u].value] = u;
            else;
        else
            log[tree[u].value] = u;

        for (const auto& [i, c] : e[u])
        {
            if (i == fa)
                continue;

            add(i, u);
        }
    }

    void count(int u, int fa, int lca)
    {
        for (int i = 0; i <= (1 << 21); i ? i <<= 1 : ++i)
            if (log[tree[u].value ^ i])
                ans[lca] = std::max(ans[lca], tree[u].depth + tree[log[tree[u].value ^ i]].depth - tree[lca].depth * 2);

        for (const auto& [i, c] : e[u])
        {
            if (i == fa or i == tree[lca].wson)
                continue;

            count(i, u, lca);

            if (u == lca)
                add(i, u);
        }
    }

    void clear(int u, int fa)
    {
        log[tree[u].value] = 0;

        for (const auto& [i, c] : e[u])
        {
            if (i == fa)
                continue;

            clear(i, u);
        }
    }

    void dfs(int u, int fa, bool flag)
    {
        for (const auto& [i, c] : e[u])
        {
            if (i == fa or i == tree[u].wson)
                continue;

            dfs(i, u, false);
            ans[u] = std::max(ans[u], ans[i]);
        }

        if (tree[u].wson)
            dfs(tree[u].wson, u, true),
            ans[u] = std::max(ans[u], ans[tree[u].wson]);

        for (int i = 0; i <= (1 << 21); i ? i <<= 1 : ++i)
            if (log[tree[u].value ^ i])
                ans[u] = std::max(ans[u], tree[u].depth + tree[log[tree[u].value ^ i]].depth - tree[u].depth * 2);

        if (log[tree[u].value])
            if (tree[u].depth > tree[log[tree[u].value]].depth)
                log[tree[u].value] = u;
            else;
        else
            log[tree[u].value] = u;

        count(u, fa, u);

        if (not flag)
            clear(u, fa);
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

    std::vector<std::vector<std::pair<int, char>>> e(n + 1);

    for (int i = 2; i <= n; ++i)
    {
        int u;
        char c;

        std::cin >> u >> c;

        e[u].push_back({i, c});
        e[i].push_back({u, c});
    }

    DsuOnTree tree(e);

    tree.dfs(1, 1, true);

    for (int i = 1; i <= n; ++i)
        std::cout << tree.ans[i] << ' ';

    return 0;
}