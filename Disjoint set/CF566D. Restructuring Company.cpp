/**
 * VK Cup 2015 - Finals, online mirror
 * 
 * => D. Restructuring Company ( @c 1900 )
 * 
 * -> https://codeforces.com/contest/566/problem/D
 * 
 * Submissions ~> https://codeforces.com/contest/566/submission/361405369 By huanhuanonly
 * 
 * @b Disjoint-set ( @a for-next-pointer )
 * 
 * ----February 04, 2026 [20h:25m:15s]----
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

    void merge(int u, int v)
    {
        const int fu = find(u);
        const int fv = find(v);

        tree[std::min(fu, fv)] = std::max(fu, fv);
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

    int n, q;
    std::cin >> n >> q;

    DisjointSet dsu(n);
    DisjointSet rightmost(n);

    while (q--)
    {
        int opt, x, y;
        std::cin >> opt >> x >> y;

        --x, --y;

        if (opt == 1)
        {
            dsu.merge(x, y);
        }
        else if (opt == 2)
        {
            for (int i = rightmost.find(x); i + 1 <= y; i = rightmost.find(i))
            {
                dsu.merge(i, i + 1);
                rightmost.merge(i, i + 1);
            }
        }
        else
        {
            if (dsu.find(x) == dsu.find(y))
            {
                std::cout << "YES\n";
            }
            else
            {
                std::cout << "NO\n";
            }
        }
    }

    return 0;
}