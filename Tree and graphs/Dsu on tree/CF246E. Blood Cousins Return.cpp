/**
 * Codeforces Round 151 (Div. 2)
 *
 * => E. Blood Cousins Return ( @c 2400 )
 *
 * -> https://codeforces.com/contest/246/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/246/submission/256092119 By huanhuanonly
 *
 * @b Dsu-on-tree
 *
 * ----April 11, 2024 [17h:04m:07s]----
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
    const std::vector<std::hash<std::string>::result_type>& v;

    struct node
    {
        int size, depth, wson;
    };

    std::vector<node> tree;

    std::vector<std::map<std::hash<std::string>::result_type, int>> cnt;

    DsuOnTree(const std::vector<std::vector<int>>& __e
        , const std::vector<std::hash<std::string>::result_type>& __v)
        : e(__e), v(__v), tree(__e.size()), cnt(__e.size())
    {
        build(1, 1);
    }

    void build(int p, int fa)
    {
        tree[p].size = 1;
        tree[p].depth = tree[fa].depth + 1;

        for (const auto& i : e[p])
        {
            build(i, p);

            tree[p].size += tree[i].size;
            if (tree[i].size > tree[tree[p].wson].size)
                tree[p].wson = i;
        }
    }

    void count(int p, int wson)
    {
        ++cnt[tree[p].depth][v[p]];

        for (const auto& i : e[p])
        {
            if (i == wson)
                continue;

            count(i, wson);
        }
    }

    void clear(int p)
    {
        if (--cnt[tree[p].depth][v[p]] == 0)
        {
            cnt[tree[p].depth].erase(v[p]);
        }

        for (const auto& i : e[p])
        {
            clear(i);
        }
    }

    template<typename _FillFunc>
    void dfs(int p, bool flag, _FillFunc fill)
    {
        for (const auto& i : e[p])
        {
            if (i == tree[p].wson)
                continue;

            dfs(i, false, fill);
        }

        if (tree[p].wson)
            dfs(tree[p].wson, true, fill);

        count(p, tree[p].wson);
        fill(p, cnt);

        if (not flag)
            clear(p);
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

    std::string s;
    int r;

    std::vector<std::vector<int>> e(n + 2);

    std::vector<std::hash<std::string>::result_type> v(n + 2);

    /**
     * @note This tree may have multiple root nodes,
     * so connect multiple root nodes to a new unified root node.
     *
     * Here we add one to the numbers of all nodes
     * and let node number 1 serve as the unified root node.
    */

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> s >> r;

        e[r + 1].push_back(i + 1);
        v[i + 1] = std::hash<std::string>()(s);
    }

    DsuOnTree tree(e, v);

    int m;
    std::cin >> m;

    struct query
    {
        int v, k, i;
        int ans;
    };

    std::vector<query> qv(m);

    for (int i = 0; i < m; ++i)
    {
        std::cin >> qv[i].v >> qv[i].k;
        ++qv[i].v;
        qv[i].i = i;
    }

    std::sort(qv.begin(), qv.end(), [](const query& lv, const query& rv) -> bool
    {
        return lv.v < rv.v;
    });

    tree.dfs(1, true, [&](int p, const std::vector<std::map<std::hash<std::string>::result_type, int>>& cnt) -> void
    {
        int i = std::lower_bound(qv.begin(), qv.end(), query{p}, [](const query& lv, const query& rv) -> bool
        {
            return lv.v < rv.v;
        }) - qv.begin();

        for (; i < qv.size() and qv[i].v == p; ++i)
        {
            if (tree.tree[p].depth + qv[i].k < cnt.size())
            {
                qv[i].ans = cnt[tree.tree[p].depth + qv[i].k].size();
            }
        }
    });

    std::sort(qv.begin(), qv.end(), [](const query& lv, const query& rv) -> bool
    {
        return lv.i < rv.i;
    });

    for (int i = 0; i < m; ++i)
        std::cout << qv[i].ans << '\n';

    return 0;
}