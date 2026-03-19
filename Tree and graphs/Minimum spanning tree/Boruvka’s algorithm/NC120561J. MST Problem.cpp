/**
 * 2026牛客寒假算法基础集训营1
 * 
 * => J-MST Problem ( @c 3000 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120561/J
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82102407 By huanhuanonly
 * 
 * @b Boruvka’s-algorithm
 * 
 * ----February 06, 2026 [20h:37m:02s]----
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
    
        std::vector e(n + 1, std::vector<int>{});
    
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            std::cin >> u >> v;
    
            e[u].push_back(v);
            e[v].push_back(u);
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

        auto iota = std::views::iota(1, n + 1);
        std::set<int, decltype(comp)> s(iota.begin(), iota.end(), comp);

        DisjointSet dsu(n + 1);
        int cnt = n;

        uint64 ans = 0;

        auto eval = [&]() -> bool
        {
            bool continues = false;
            
            std::vector<std::vector<int>> sets(n + 1);

            for (int i = 1; i <= n; ++i)
            {
                sets[dsu.find(i)].push_back(i);
            }

            for (int i = 1; i <= n; ++i)
            {
                for (const auto& u : sets[i])
                {
                    s.erase(u);
                }
                
                bool found = false;
                std::pair<int, int> min;

                for (const auto& u : sets[i])
                {
                    const auto filter = std::views::filter([&](int v) -> bool { return dsu.find(u) != dsu.find(v); });

                    for (const auto& v : e[u] | filter)
                    {
                        s.erase(v);
                    }

                    if (not s.empty())
                    {
                        if (not found)
                        {
                            found = true;
                            min = {w[u] + w[*s.begin()], *s.begin()};
                        }
                        else
                        {
                            min = std::min(min, {w[u] + w[*s.begin()], *s.begin()});
                        }
                    }

                    for (const auto& v : e[u] | filter)
                    {
                        s.insert(v);
                    }
                }

                if (found and dsu.merge(i, min.second))
                {
                    ans += min.first;
                    continues = true;
                    --cnt;
                }
                
                for (const auto& u : sets[i])
                {
                    s.insert(u);
                }
            }

            return continues and cnt != 1;
        };
    
        while (eval());

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