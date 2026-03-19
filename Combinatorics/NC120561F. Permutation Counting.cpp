/**
 * 2026牛客寒假算法基础集训营1
 * 
 * => F-Permutation Counting ( @c 2900 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120561/F
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82106378 By huanhuanonly
 * 
 * @b Combinatorics and @b Disjoint-set ( @a for-next-pointer )
 * 
 * ----February 07, 2026 [00h:52m:39s]----
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
        const auto [fmin, fmax] = std::minmax({find(u), find(v)});

        tree[fmin] = fmax;
    }
};

void chmin(auto& lhs, const auto& rhs)
{
    if (rhs < lhs)
    {
        lhs = rhs;
    }
}

void chmax(auto& lhs, const auto& rhs)
{
    if (lhs < rhs)
    {
        lhs = rhs;
    }
}

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

        constexpr uint64 mod = 998244353;

        std::vector<bool> vis(n + 1);

        std::vector iset(n + 1, std::make_pair(1, n));
        std::vector uset(n + 1, std::make_pair(0, 0));

        for (int i = 0; i < m; ++i)
        {
            int l, r, k;
            std::cin >> l >> r >> k;

            if (vis[k])
            {
                chmax(iset[k].first, l);
                chmin(iset[k].second, r);

                chmin(uset[k].first, l);
                chmax(uset[k].second, r);
            }
            else
            {
                iset[k] = uset[k] = {l, r};
                vis[k] = true;
            }
        }

        std::vector<uint64> cnt(n + 1);

        DisjointSet dsu(n + 2);
        uint64 remaining = n;

        for (int k = 1; k <= n; ++k)
        {
            if (vis[k])
            {
                for (int i = dsu.find(iset[k].first); i <= iset[k].second; i = dsu.find(i + 1))
                {
                    ++cnt[k];
                }
    
                for (int i = dsu.find(uset[k].first); i <= uset[k].second; i = dsu.find(i))
                {
                    dsu.merge(i, i + 1);
                    --remaining;
                }
            }
            else
            {
                cnt[k] = remaining;
            }
        }

        uint64 ans = 1;

        for (int k = n; k >= 1; --k)
        {
            if (vis[k])
            {
                (ans *= cnt[k]) %= mod;
            }
            else
            {
                if (cnt[k] < n - k)
                {
                    ans = 0;
                    break;
                }
    
                (ans *= cnt[k] - (n - k)) %= mod;
            }
        }

        std::cout << ans << '\n';
    }

    return 0;
}