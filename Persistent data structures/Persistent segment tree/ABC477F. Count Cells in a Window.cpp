/**
 * UNICORNProgramming Contest2026(AtCoder Beginner Contest 477)
 *
 * => F - Count Cells in a Window ( @c 525 )
 *
 * -> https://atcoder.jp/contests/abc477/tasks/abc477_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc477/submissions/79629243 By huanhuanonly
 *
 * @b Persistent-segment-tree
 *
 * ----September 29, 2026 [23h:53m:40s]----
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

struct PersistentSegmentTree
{
    struct node
    {
        int ls, rs;
        int64 value;
        int64 lazy;
    };

    std::vector<node> tree;

    PersistentSegmentTree()
    {
        tree.reserve(2e7);
        tree.emplace_back();
    }

    int new_node(int u = 0)
    {
        tree.push_back(tree[u]);
        return tree.size() - 1;
    }

    void add_lazy(int& u, int l, int r, int64 add)
    {
        u = new_node(u);

        tree[u].lazy += add;
        tree[u].value += add * (r - l + 1);
    }

    void push_up(int u)
    {
        tree[u].value = tree[tree[u].ls].value + tree[tree[u].rs].value;
    }

    void push_down(int u, int l, int r)
    {
        if (tree[u].lazy)
        {
            const int mid = l + r >> 1;

            add_lazy(tree[u].ls, l, mid, tree[u].lazy);
            add_lazy(tree[u].rs, mid + 1, r, tree[u].lazy);

            tree[u].lazy = 0;
        }
    }

    void range_add(int& u, int l, int r, int x, int y)
    {
        if (x <= l and r <= y)
        {
            add_lazy(u, l, r, 1);
            return;
        }

        u = new_node(u);
        push_down(u, l, r);

        const int mid = l + r >> 1;

        if (x <= mid)
        {
            range_add(tree[u].ls, l, mid, x, y);
        }

        if (y > mid)
        {
            range_add(tree[u].rs, mid + 1, r, x, y);
        }

        push_up(u);
    }

    int64 range_sum(int u, int l, int r, int x, int y) const
    {
        if (not u or x <= l and r <= y)
        {
            return tree[u].value;
        }

        const int mid = l + r >> 1;
        int64 sum = tree[u].lazy * (std::min(r, y) - std::max(l, x) + 1);

        if (x <= mid)
        {
            sum += range_sum(tree[u].ls, l, mid, x, y);
        }

        if (y > mid)
        {
            sum += range_sum(tree[u].rs, mid + 1, r, x, y);
        }

        return sum;
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

    int n, m, q;
    std::cin >> n >> m >> q;

    PersistentSegmentTree pseg;
    std::vector<int> roots(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        int l, r;
        std::cin >> l >> r;

        roots[i] = roots[i - 1];
        pseg.range_add(roots[i], 1, m, l, r);
    }

    while (q--)
    {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;

        std::cout << pseg.range_sum(roots[b], 1, m, c, d) - pseg.range_sum(roots[a - 1], 1, m, c, d) << '\n';
    }

    return 0;
}