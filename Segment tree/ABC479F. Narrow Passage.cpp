/**
 * AtCoder Beginner Contest 479
 *
 * => F - Narrow Passage ( @c 500 )
 *
 * -> https://atcoder.jp/contests/abc479/tasks/abc479_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc479/submissions/80035979 By huanhuanonly
 *
 * @b Segment-tree
 *
 * ----October 14, 2026 [17h:20m:23s]----
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

struct SegmentTree
{
    struct node
    {
        int ls, rs;
        int value;
    };

    std::vector<node> tree;

    SegmentTree()
        : tree(2)
    { }

    void push_up(int u)
    {
        tree[u].value = tree[tree[u].ls].value + tree[tree[u].rs].value;
    }

    int add(int u, int l, int r, int p)
    {
        if (not u)
        {
            u = tree.size();
            tree.emplace_back();
        }

        if (l == r)
        {
            ++tree[u].value;
            return u;
        }

        const int mid = l + r >> 1;

        if (p <= mid)
        {
            tree[u].ls = add(tree[u].ls, l, mid, p);
        }
        else
        {
            tree[u].rs = add(tree[u].rs, mid + 1, r, p);
        }

        push_up(u);
        return u;
    }

    int range_sum(int u, int l, int r, int x, int y) const
    {
        if (not u)
        {
            return 0;
        }

        if (x <= l and r <= y)
        {
            return tree[u].value;
        }

        const int mid = l + r >> 1;
        int sum = 0;

        if (x <= mid)
        {
            sum = range_sum(tree[u].ls, l, mid, x, y);
        }
        if (y > mid)
        {
            sum += range_sum(tree[u].rs, mid + 1, r, x, y);
        }

        return sum;
    }

    void clear()
    {
        tree.resize(2);
        tree[1] = node{};
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

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> v(n);
    int maxv = 0;

    for (auto& i : v | std::views::keys)
    {
        std::cin >> i;
        maxv = std::max(maxv, i);
    }

    for (auto& i : v | std::views::values)
    {
        std::cin >> i;
        maxv = std::max(maxv, i);
    }

    std::ranges::sort(v);

    SegmentTree seg;
    int64 ans = 0;

    seg.clear();

    std::vector<int> ltr(n), rtl(n);

    for (int i = 0; i < n; ++i)
    {
        const auto& [s, t] = v[i];
        ltr[i] = seg.range_sum(1, 0, maxv, t, maxv);
        seg.add(1, 0, maxv, t);

        ans += ltr[i];
    }

    seg.clear();

    for (int i = n - 1; i >= 0; --i)
    {
        const auto& [s, t] = v[i];
        rtl[i] = seg.range_sum(1, 0, maxv, 0, t);
        seg.add(1, 0, maxv, t);
    }

    seg.clear();

    for (int i = 0; i < n; ++i)
    {
        const auto& [s, t] = v[i];
        ans += std::abs((s + rtl[i] - ltr[i]) - t);
    }

    std::cout << ans << '\n';

    return 0;
}