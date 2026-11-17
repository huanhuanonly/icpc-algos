/**
 * Codeforces Round 1046 (Div. 2)
 *
 * => E. By the Assignment ( @c 2000 )
 *
 * -> https://codeforces.com/contest/2136/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/2136/submission/338662711 By huanhuanonly
 *
 * @b Tarjan's-algorithm ( @a bridge-finding )
 * @b Disjoint-set
 * @b Bitwise-XOR
 * @b Bipartite-graph
 *
 * ----September 15, 2025 [10h:50m:22s]----
*/

#include <bits/stdc++.h>

using int8 = signed char;
using int16 = short;
using int32 = int;
using int64 = long long;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

#ifdef __GNUC__
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;
using real128 = long double;

class DisjointSet
{
public:
    std::vector<int> tree;
    std::vector<int> values;

    explicit DisjointSet(std::size_t n, const std::vector<int>& vs)
        : tree(n), values(vs)
    {
        std::iota(tree.begin(), tree.end(), 0);
    }

    int find(int u)
    {
        return tree[u] == u ? u : tree[u] = find(tree[u]);
    }

    bool merge(int u, int v)
    {
        int fv = find(v), fu = find(u);

        if (values[fv] != values[fu] and values[fv] != -1 and values[fu] != -1)
        {
            return false;
        }

        if (values[fu] == -1)
        {
            values[fu] = values[fv];
        }
        else
        {
            values[fv] = values[fu];
        }

        tree[fv] = fu;
        return true;
    }
};

template<typename _Tp>
_Tp binary_exponentiation(_Tp __fv, _Tp __sv, _Tp __mod)
{
    __fv %= __mod;

    _Tp ans = 1;
    for (; __sv; __fv = (__fv * __fv) % __mod, __sv >>= 1)
        if (__sv & 1)
            ans = (ans * __fv) % __mod;
    return ans;
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, m, maxv;
        std::cin >> n >> m >> maxv;

        std::vector<int> v(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> v[i];
        }

        std::vector<std::vector<int>> e(n + 1);

        for (int i = 0; i < m; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            e[u].push_back(v);
            e[v].push_back(u);
        }

        constexpr uint64 mod = 998'244'353;

        std::set<std::pair<int, int>> removed_set;

        std::vector<std::pair<int, int>> dfn(n + 1);

        auto dfs = [&, cnt = 0](auto& self, int u, int fa) mutable -> void
        {
            dfn[u].first = dfn[u].second = ++cnt;

            for (int i : e[u] | std::views::filter([fa](int i) -> bool { return i != fa; }))
            {
                if (not dfn[i].first)
                {
                    self(self, i, u);
                    dfn[u].second = std::min(dfn[u].second, dfn[i].second);

                    if (dfn[i].second > dfn[u].first)
                    {
                        removed_set.insert(std::minmax(u, i));
                    }
                }
                else
                {
                    dfn[u].second = std::min(dfn[u].second, dfn[i].first);
                }
            }
        };

        dfs(dfs, 1, 0);

        DisjointSet dsu(n + 1, v);
        bool yes = true;

        for (int u = 1; u <= n; ++u)
        {
            std::erase_if(e[u], [&](int i) -> bool {
                return removed_set.contains(std::minmax(u, i));
            });

            for (int i : e[u])
            {
                yes = yes and dsu.merge(u, i);
            }
        }

        std::vector<bool> vis(n + 1);
        std::vector<bool> dis(n + 1);

        auto check = [&](int start) -> bool
        {

            bool found = false;

            std::queue<int> que;
            que.push(start);

            vis[start] = true;
            dis[start] = false;

            while (not que.empty())
            {
                int cur = que.front();
                que.pop();

                for (int i : e[cur])
                {
                    if (not vis[i])
                    {
                        dis[i] = not dis[cur];
                        vis[i] = true;
                        que.push(i);
                    }
                    else if (dis[i] == dis[cur])
                    {
                        found = true;
                    }
                }
            }

            if (found)
            {
                auto& ref = dsu.values[dsu.find(start)];

                if (ref != -1 and ref != 0)
                {
                    return false;
                }

                ref = 0;
            }

            return true;
        };

        for (int i = 1; i <= n; ++i)
        {
            if (not vis[i])
            {
                yes = yes and check(i);
            }
        }

        std::set<int> cnt;

        for (int i = 1; i <= n; ++i)
        {
            if (dsu.values[dsu.find(i)] == -1)
            {
                cnt.insert(dsu.find(i));
            }
        }

        if (yes)
        {
            std::cout << binary_exponentiation<uint64>(maxv, cnt.size(), mod) << '\n';
        }
        else
        {
            std::cout << 0 << '\n';
        }
    }

    return 0;
}