/**
 * => P4585 [FJOI2015] 火星商店问题 ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P4585
 *
 * Submissions ~> https://www.luogu.com.cn/record/287924277 By huanhuanonly
 *
 * @b Segment-tree-of-Binary-tries
 *
 * ----July 22, 2026 [22h:34m:09s]----
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

class Trie
{
public:

    struct node
    {
        std::array<int, 2> word;

        int time;
        int maxtime;
    };

    std::vector<node> tree;

    Trie() : tree(1) { }

    int create_node()
    {
        tree.emplace_back();
        return tree.size() - 1;
    }

    void insert(int x, int time)
    {
        int u = 0;

        for (int i = 20; i >= 0; --i)
        {
            const bool c = x & 1 << i;

            if (not tree[u].word[c])
            {
                tree[u].word[c] = create_node();
            }

            u = tree[u].word[c];
            tree[u].maxtime = std::max(tree[u].maxtime, time);
        }

        tree[u].time = time;
    }

    int max_xor_sum(int x, int after)
    {
        int u = 0;
        int ans = 0;

        for (int i = 20; i >= 0; --i)
        {
            const bool c = not (x & 1 << i);

            if (tree[u].word[c] and after < tree[tree[u].word[c]].maxtime)
            {
                ans |= 1 << i;
                u = tree[u].word[c];
            }
            else
            {
                u = tree[u].word[not c];
            }
        }

        return ans;
    }
};

class SegmentTree
{
public:

    std::vector<Trie> tree;

    explicit SegmentTree(const std::vector<int>& array)
        : tree(array.size() << 2)
    { build(1, 1, array.size() - 1, array); }

    static int ls(int u)
    {
        return u << 1;
    }

    static int rs(int u)
    {
        return u << 1 | 1;
    }

    void build(int u, int l, int r, const std::vector<int>& array)
    {
        for (int i = l; i <= r; ++i)
        {
            tree[u].insert(array[i], std::numeric_limits<int>::max());
        }

        if (l != r)
        {
            const int mid = l + r >> 1;
            build(ls(u), l, mid, array);
            build(rs(u), mid + 1, r, array);
        }
    }

    void insert(int u, int l, int r, int i, int x, int time)
    {
        tree[u].insert(x, time);

        if (l == r)
        {
            return;
        }

        const int mid = l + r >> 1;

        if (i <= mid)
        {
            insert(ls(u), l, mid, i, x, time);
        }
        else
        {
            insert(rs(u), mid + 1, r, i, x, time);
        }
    }

    int reduce(int u, int l, int r, int x, int y, int v, int after)
    {
        if (x <= l and r <= y)
        {
            return tree[u].max_xor_sum(v, after);
        }

        const int mid = l + r >> 1;

        int max = 0;

        if (x <= mid)
        {
            max = reduce(ls(u), l, mid, x, y, v, after);
        }

        if (y > mid)
        {
            max = std::max(max, reduce(rs(u), mid + 1, r, x, y, v, after));
        }

        return max;
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

    int n, m;
    std::cin >> n >> m;

    std::vector<int> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
    }

    SegmentTree seg(v);

    int time = 0;

    while (m--)
    {
        int opt;
        std::cin >> opt;

        if (opt == 0)
        {
            int s, v;
            std::cin >> s >> v;

            seg.insert(1, 1, n, s, v, ++time);
        }
        else
        {
            int l, r, x, d;
            std::cin >> l >> r >> x >> d;

            std::cout << seg.reduce(1, 1, n, l, r, x, time - d) << '\n';
        }
    }

    return 0;
}