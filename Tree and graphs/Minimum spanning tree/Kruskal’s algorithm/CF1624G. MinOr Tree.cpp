/**
 * Codeforces Round 764 (Div. 3)
 * 
 * => G. MinOr Tree ( @c 1900 )
 * 
 * -> https://codeforces.com/contest/1624/problem/G
 * 
 * Submissions ~> https://codeforces.com/contest/1624/submission/341991942 By huanhuanonly
 * 
 * @b Kruskal’s-algorithm and @b Bitwise-OR
 * 
 * ----October 05, 2025 [18h:50m:23s]----
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
        int n, m;
        std::cin >> n >> m;

        struct edge
        {
            uint32 u, v, w;

            bool operator<(const edge& other) const noexcept
            {
                return std::tuple(u, v, w) < std::tuple(other.u, other.v, other.w);
            }
        };

        std::set<edge> st;

        for (uint32 i = 0; i < m; ++i)
        {
            uint32 u, v, w;
            std::cin >> u >> v >> w;

            st.emplace(u, v, w);
        }

        uint32 mask = ~0U;

        for (uint32 bit = 32U; bit--; )
        {
            DisjointSet dsu(n + 1);

            for (const auto& [u, v, w] : st)
            {
                if ((w & (1U << bit)) == 0)
                {
                    dsu.merge(u, v);
                }
            }

            bool b = true;

            for (int i = 2; i <= n; ++i)
            {
                if (dsu.find(i - 1) != dsu.find(i))
                {
                    b = false;
                    break;
                }
            }

            if (b)
            {
                mask ^= 1U << bit;

                for (auto it = st.begin(); it != st.end(); )
                {
                    if (it->w & ~mask)
                    {
                        it = st.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
        }

        std::cout << mask << '\n';
    }

    return 0;
}