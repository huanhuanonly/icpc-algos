/**
 * Daiwa Securities Co. Ltd. Programming Contest 2024（AtCoder Beginner Contest 383）
 * 
 * => E - Sum of Max Matching ( @c 500 )
 * 
 * -> https://atcoder.jp/contests/abc383/tasks/abc383_e
 * 
 * Submissions ~> https://atcoder.jp/contests/abc383/submissions/65066470 By huanhuanonly
 * 
 * @b Kruskal’s-algorithm
 * 
 * ----April 20, 2025 [21h:54m:28s]----
 */

/// @brief This is an @c interesting problem!

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
    std::vector<std::multiset<int>> sets;

    explicit DisjointSet(std::size_t n)
        : tree(n), sets(n)
    {
        std::iota(tree.begin(), tree.end(), 0);
    }

    int find(int u)
    {
        return tree[u] == u ? u : tree[u] = find(tree[u]);
    }

    void merge(int u, int v)
    {
        int fv = find(v);
        int fu = find(u);

        if (sets[fu].size() < sets[fv].size())
        {
            std::swap(fv, fu);
        }

        sets[fu].merge(sets[fv]);
        tree[fv] = fu;
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

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::tuple<int, int, int>> log(m);

    for (auto& [w, u, v] : log)
    {
        std::cin >> u >> v >> w;
    }

    std::sort(log.begin(), log.end());

    DisjointSet ds(n + 1);
    
    enum Flag { None, Left, Right };
    std::vector<Flag> flags(n + 1, None);
    
    for (int i = 0, value; i < k; ++i)
    {
        std::cin >> value;
        flags[value] = Left;
        ds.sets[value].insert(value);
    }
    
    for (int i = 0, value; i < k; ++i)
    {
        std::cin >> value;
        flags[value] = Right;
        ds.sets[value].insert(value);
    }
    
    uint64 ans = 0;

    for (const auto& [w, u, v] : log)
    {
        if (ds.find(u) != ds.find(v))
        {
            if (ds.sets[ds.find(u)].size() and ds.sets[ds.find(v)].size() and
                flags[*ds.sets[ds.find(u)].begin()] != flags[*ds.sets[ds.find(v)].begin()])
            {
                auto* bigptr = &ds.sets[ds.find(u)];
                auto* smallptr = &ds.sets[ds.find(v)];

                if (bigptr->size() < smallptr->size())
                {
                    std::swap(*bigptr, *smallptr);
                }

                for (
                    auto bit = bigptr->begin(), sit = smallptr->begin();
                    sit != smallptr->end();
                    bit = bigptr->erase(bit), sit = smallptr->erase(sit))
                {
                    ans += w;
                }
            }

            ds.merge(u, v);
        }
    }

    std::cout << ans;

    return 0;
}