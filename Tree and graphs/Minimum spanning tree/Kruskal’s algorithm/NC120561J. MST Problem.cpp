/**
 * 2026牛客寒假算法基础集训营1
 * 
 * => J-MST Problem ( @c 3000 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120561/J
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82095044 By huanhuanonly
 * 
 * @b Kruskal’s-algorithm and @b Boruvka’s-algorithm
 * 
 * ----February 06, 2026 [16h:10m:41s]----
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

#if defined(__SIZEOF_INT128__)
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;

#if defined(__SIZEOF_FLOAT80__)
using real80 = __float80;
#endif

#if defined(__SIZEOF_FLOAT128__)
using real128 = __float128;
#endif

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

    bool merge(int u, int v)
    {
        if (const int fu = find(u), fv = find(v); fu != fv)
        {
            tree[fv] = fu;
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, m;
        std::cin >> n >> m;
    
        std::vector<int> w(n + 1);
    
        for (int i = 1; i <= n; ++i)
        {
            std::cin >> w[i];
        }
    
        auto comp = [&](int lhs, int rhs) -> bool
        {
            if (w[lhs] != w[rhs])
            {
                return w[lhs] < w[rhs];
            }
            else
            {
                return lhs < rhs;
            }
        };
    
        std::vector<int> s(n);
        std::iota(s.begin(), s.end(), 1);
        std::ranges::sort(s.begin(), s.end(), comp);
    
        std::vector e(n + 1, std::vector<int>{});
    
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            std::cin >> u >> v;
    
            e[u].push_back(v);
            e[v].push_back(u);
        }

        std::vector<std::pair<int, int>> es;

        for (int u = 1; u <= n; ++u)
        {
            std::ranges::sort(e[u], comp);
            e[u].erase(std::ranges::unique(e[u]).begin(), e[u].end());

            for (int i = 0, j = 0, cnt = 0; i < s.size() and cnt <= e[u].size() + 1; ++i)
            {
                for (; j < e[u].size() and comp(e[u][j], s[i]); ++j);

                if (u != s[i] and (j == e[u].size() or e[u][j] != s[i]))
                {
                    es.emplace_back(u, s[i]);
                    ++cnt;
                }
            }
        }
    
        std::ranges::sort(es, {}, [&](const auto& p) -> uint64
        {
            return w[p.first] + w[p.second];
        });

        DisjointSet dsu(n + 1);
    
        uint64 ans = 0;

        int cnt = n;

        for (const auto& [u, v] : es)
        {
            if (dsu.merge(u, v))
            {
                ans += w[u] + w[v];
                --cnt;
            }
        }
        
        if (cnt == 1)
        {
            std::cout << ans << '\n';
        }
        else
        {
            std::cout << -1 << '\n';
        }
    }

    return 0;
}