/**
 * Zepto Code Rush 2014
 * 
 * => C. Dungeons and Candies ( @c 1800 )
 * 
 * -> https://codeforces.com/contest/436/problem/C
 * 
 * Submissions ~> https://codeforces.com/contest/436/submission/342380858 By huanhuanonly
 * 
 * @b Kruskal’s-algorithm and @b Dfs
 * 
 * ----October 07, 2025 [12h:05m:05s]----
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

    explicit DisjointSet(std::size_t n)
        : tree(n)
    {
        std::iota(tree.begin(), tree.end(), 0);
    }

    int find(int u)
    {
        return tree[u] == u ? u : tree[u] = find(tree[u]);
    }

    void merge(int u, int v)
    {
        tree[find(v)] = find(u);
    }
};

int diff(const std::string& a, const std::string& b)
{
    int cnt = 0;

    for (int i = 0; i < a.size(); ++i)
    {
        cnt += a[i] != b[i];
    }

    return cnt;
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m, k, w;
    std::cin >> n >> m >> k >> w;

    std::vector v(k, std::string(n * m, '\0'));

    for (std::string& s : v)
    {
        for (char& c : s)
        {
            std::cin >> c;
        }
    }

    struct edge
    {
        int u, v, w;
    };

    std::vector<edge> e;
    e.reserve(k * (k - 1) / 2);

    for (int i = 0; i < k; ++i)
    {
        e.push_back({0, i + 1, n * m});

        for (int j = 0; j < i; ++j)
        {
            e.push_back({i + 1, j + 1, diff(v[i], v[j]) * w});
        }
    }

    std::ranges::sort(e, {}, &edge::w);

    DisjointSet dsu(k + 1);

    std::vector<std::vector<int>> g(k + 1);

    int sum = 0;

    for (int i = 0; i < e.size(); ++i)
    {
        if (dsu.find(e[i].u) != dsu.find(e[i].v))
        {
            dsu.merge(e[i].u, e[i].v);
            sum += e[i].w;

            g[e[i].u].push_back(e[i].v);
            g[e[i].v].push_back(e[i].u);
        }
    }

    std::cout << sum << '\n';

    auto dfs = [&](const auto& self, int u, int fa) -> void
    {
        for (int i : g[u] | std::views::filter([fa](int i) -> bool { return i != fa; }))
        {
            std::cout << i << ' ' << u << '\n';

            self(self, i, u);
        }
    };

    dfs(dfs, 0, 0);

    return 0;
}