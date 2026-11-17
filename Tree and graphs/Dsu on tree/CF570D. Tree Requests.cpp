/**
 * Codeforces Round 316 (Div. 2)
 *
 * => D. Tree Requests ( @c 2200 )
 *
 * -> https://codeforces.com/contest/570/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/570/submission/256078708 By huanhuanonly
 *
 * @b Dsu-on-tree
 *
 * ----April 11, 2024 [14h:59m:11s]----
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
    std::string_view s;

    struct node
    {
        int size, depth, wson;
    };

    std::vector<node> tree;

    // fix each depth information
    std::vector<int> log;

    DsuOnTree(const std::vector<std::vector<int>>& __e, std::string_view __s)
        : e(__e), s(__s), tree(__e.size()), log(__e.size())
    {
        build(1, 1);
    }

    void build(int p, int fa)
    {
        tree[p].size = 1;
        tree[p].depth = tree[fa].depth + 1;

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

    std::function<void(int, const std::vector<int>&)> fill;

    void fill_answer(const std::function<void(int, const std::vector<int>&)>& ptr)
    {
        fill = ptr;
        dfs(1, 1, true);
    }

    void count(int p, int fa, int wson)
    {
        log[tree[p].depth] ^= (1 << s[p] - 'a');

        for (const auto& i : e[p])
        {
            if (i == fa or i == wson)
                continue;

            count(i, p, wson);
        }
    }

    void clear(int p, int fa)
    {
        log[tree[p].depth] ^= (1 << s[p] - 'a');

        for (const auto& i : e[p])
        {
            if (i == fa)
                continue;

            clear(i, p);
        }
    }

    void dfs(int p, int fa, bool flag = true)
    {
        for (const auto& i : e[p])
        {
            if (i == fa or i == tree[p].wson)
                continue;

            dfs(i, p, false);
        }

        if (tree[p].wson)
        {
            dfs(tree[p].wson, p, true);
        }

        count(p, fa, tree[p].wson);
        fill(p, log);

        if (not flag)
        {
            clear(p, fa);
        }
    }
};

constexpr inline int lowbit(int x)
{
    return x & -x;
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("Input.txt", "r", stdin);
    ::freopen("Output.txt", "w", stdout);
#endif

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 2; i <= n; ++i)
    {
        int x;
        std::cin >> x;

        e[std::min(i, x)].push_back(std::max(i, x));
    }

    std::string s;
    std::cin >> s;

    DsuOnTree tree(e, std::string_view(s.c_str() - 1, s.size() + 1));

    struct query
    {
        int v, h, i;
        bool ans;
    };
    std::vector<query> v(m);

    for (int i = 0; i < m; ++i)
    {
        std::cin >> v[i].v >> v[i].h;
        v[i].i = i;
    }

    std::sort(v.begin(), v.end(), [](const query& lv, const query& rv) -> bool
    {
        if (lv.v != rv.v)
            return lv.v < rv.v;
        else
            return lv.h < rv.h;
    });

    tree.fill_answer([&](int p, const std::vector<int>& ans) -> void
    {
        int i = std::lower_bound(v.begin(), v.end(), query{p}, [](const query& lv, const query& rv) -> bool
        {
            return lv.v < rv.v;
        }) - v.begin();

        for (; i < v.size() and v[i].v == p; ++i)
        {
            v[i].ans = (ans[v[i].h] == lowbit(ans[v[i].h]));
        }
    });

    std::sort(v.begin(), v.end(), [](const query& lv, const query& rv) -> bool
    {
        return lv.i < rv.i;
    });

    for (int i = 0; i < m; ++i)
        std::cout << (v[i].ans ? "Yes\n" : "No\n");

    return 0;
}