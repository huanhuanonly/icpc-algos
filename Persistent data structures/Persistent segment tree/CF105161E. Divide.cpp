/**
 * 2024 Jiangsu Collegiate Programming Contest
 *
 * => E. Divide
 *
 * -> https://codeforces.com/gym/105161/problem/E
 *
 * Submissions ~> https://codeforces.com/gym/105161/submission/389024753 By huanhuanonly
 *
 * @b Persistent-segment-tree
 * @b Binary-search
 *
 * ----September 01, 2026 [01h:11m:49s]----
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

namespace PersistentSegmentTree
{
    struct node
    {
        int ls, rs;
        int count;
    };

    std::vector<node> tree(2e7);
    int idx = 0;

    void add(int& u, int l, int r, int pos)
    {
        tree[++idx] = tree[u];
        u = idx;
        ++tree[u].count;

        if (l == r)
        {
            return;
        }

        const int mid = l + r >> 1;

        if (pos <= mid)
        {
            add(tree[u].ls, l, mid, pos);
        }
        else
        {
            add(tree[u].rs, mid + 1, r, pos);
        }
    }

    int count(int u, int v, int l, int r, int pos)
    {
        if (pos <= l)
        {
            return tree[v].count - tree[u].count;
        }

        const int mid = l + r >> 1;

        if (pos <= mid)
        {
            return
                count(tree[u].ls, tree[v].ls, l, mid, pos) +
                count(tree[u].rs, tree[v].rs, mid + 1, r, pos);
        }
        else
        {
            return count(tree[u].rs, tree[v].rs, mid + 1, r, pos);
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

    int n, q;
    std::cin >> n >> q;

    constexpr int maxv = 1e5;
    std::vector<int> roots(n + 1);

    for (int i = 1, v; i <= n; ++i)
    {
        std::cin >> v;
        PersistentSegmentTree::add(roots[i] = roots[i - 1], 0, maxv, v);
    }

    while (q--)
    {
        int l, r, k;
        std::cin >> l >> r >> k;

        auto check = [&](int mid) -> bool
        {
            int cnt = 0;

            for (int i = 0; i < 17; ++i)
            {
                if (const auto pos = (mid + 1) << i; pos <= maxv)
                {
                    cnt += PersistentSegmentTree::count(roots[l - 1], roots[r], 0, maxv, pos);
                }
                else
                {
                    break;
                }
            }

            return cnt <= k;
        };

        int lo = -1, hi = maxv, mid;

        while (hi - lo > 1)
        {
            mid = lo + hi >> 1;

            if (check(mid))
            {
                hi = mid;
            }
            else
            {
                lo = mid;
            }
        }

        std::cout << hi << '\n';
    }

    return 0;
}