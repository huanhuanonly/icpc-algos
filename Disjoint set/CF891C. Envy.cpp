/**
 * Codeforces Round 446 (Div. 1)
 *
 * => C. Envy ( @c 2300 )
 *
 * -> https://codeforces.com/contest/891/problem/C
 *
 * Submissions ~> https://codeforces.com/contest/891/submission/263213556 By huanhuanonly
 *
 * @b Disjoint-set ( @a with-undo )
 *
 * ----May 30, 2024 [11h:46m:56s]----
 *
 * @see https://zhuanlan.zhihu.com/p/538166784
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class DisjointSet
{
public:
    struct node
    {
        int fa;
        int rank;
    };

    std::vector<node> tree;

    std::stack<std::pair<int&, int>, std::vector<std::pair<int&, int>>> ver_fa, ver_rank;

    explicit DisjointSet(std::size_t n)
        : tree(n)
    {
        for (int i = 0; i < n; ++i)
        {
            tree[i].fa = i;
            tree[i].rank = 1;
        }
    }

    int find(int u) const
    {
        return is_root(u) ? u : find(tree[u].fa);
    }

    void merge(int u, int v)
    {
        int fu = find(u), fv = find(v);

        if (tree[fu].rank > tree[fv].rank)
        {
            ver_fa.push({tree[fv].fa, tree[fv].fa});
            tree[fv].fa = fu;
        }
        else
        {
            ver_fa.push({tree[fu].fa, tree[fu].fa});
            tree[fu].fa = fv;
        }

        ver_rank.push({tree[fv].rank, tree[fv].rank});
        if (tree[fu].rank == tree[fv].rank)
        {
            ++tree[fv].rank;
        }
    }

    bool is_root(int u) const
    {
        return tree[u].fa == u;
    }

    bool is_same_root(int u, int v) const
    {
        return find(u) == find(v);
    }

    void undo()
    {
        if (not ver_fa.empty())
        {
            ver_fa.top().first = ver_fa.top().second;
            ver_rank.top().first = ver_rank.top().second;

            ver_fa.pop();
            ver_rank.pop();
        }
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m;
    std::cin >> n >> m;

    struct edge
    {
        int u, v, w;
    };

    std::vector<edge> e(m + 1);

    for (int i = 1; i <= m; ++i)
    {
        auto& [u, v, w] = e[i];
        std::cin >> u >> v >> w;
    }

    struct Data
    {
        int id;
        edge e;
    };
    std::vector<Data> data;

    int q;
    std::cin >> q;

    std::vector<bool> ans(q + 1);

    for (int i = 1; i <= q; ++i)
    {
        int k;
        std::cin >> k;

        for (int j = 1, v; j <= k; ++j)
        {
            std::cin >> v;
            data.push_back({i, e[v]});
        }
    }

    std::sort(e.begin() + 1, e.end(), [](const edge& lv, const edge& rv) -> bool
    {
        return lv.w < rv.w;
    });
    std::sort(data.begin(), data.end(), [](const Data& lv, const Data& rv) -> bool
    {
        if (lv.e.w != rv.e.w)
            return lv.e.w < rv.e.w;
        else
            return lv.id < rv.id;
    });

    DisjointSet ds(n + 1);

    for (int i = 1, j = 0; i <= m and j < data.size();)
    {
        for(; e[i].w < data[j].e.w; ++i)
        {
            if (int fu = ds.find(e[i].u), fv = ds.find(e[i].v); ds.is_same_root(fu, fv) == false)
                ds.merge(fu, fv);
		}

        while (j < data.size() and data[j].e.w == e[i].w)
        {
            int cnt = 0;
            for (int id = data[j].id; j < data.size() and id == data[j].id and data[j].e.w == e[i].w; ++j)
            {
                if (ans[id])
                    continue;

                if (int fu = ds.find(data[j].e.u), fv = ds.find(data[j].e.v); ds.is_same_root(fu, fv) == false)
                    ds.merge(fu, fv),
                    ++cnt;
                else
                    ans[id] = true;
            }

            while (cnt--)
            {
                ds.undo();
            }
        }
    }

    for (int i = 1; i <= q; ++i)
        std::cout << (ans[i] ? "NO\n" : "YES\n");

    return 0;
}