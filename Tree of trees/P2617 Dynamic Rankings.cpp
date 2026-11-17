/**
 * bzoj1901
 *
 * => P2617 Dynamic Rankings ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P2617
 *
 * Submissions ~> https://www.luogu.com.cn/record/282882086 By huanhuanonly
 *
 * @b Segment-tree-of-Segment-trees
 * @b Binary-search
 *
 * ----June 25, 2026 [10h:47m:32s]----
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

class SubSegmentTree
{
public:

    struct node
    {
        int ls, rs;
        int cnt;
    };

    static inline auto tree = std::vector<node>(6e7);

    int root = 0;

    static int create_node()
    {
        static int pos = 0;
        return ++pos;
    }

    static void push_up(int u)
    {
        tree[u].cnt = tree[tree[u].ls].cnt + tree[tree[u].rs].cnt;
    }

    static void add(int& u, int l, int r, int i, int value)
    {
        if (not u)
        {
            u = create_node();
        }

        if (l == r)
        {
            tree[u].cnt += value;
            return;
        }

        const int mid = l + r >> 1;

        if (i <= mid)
        {
            add(tree[u].ls, l, mid, i, value);
        }
        else
        {
            add(tree[u].rs, mid + 1, r, i, value);
        }

        push_up(u);
    }

    static int count_lt(int u, int l, int r, int i)
    {
        if (not u)
        {
            return 0;
        }

        if (l == r)
        {
            return 0;
        }

        const int mid = l + r >> 1;

        if (i <= mid)
        {
            return count_lt(tree[u].ls, l, mid, i);
        }
        else
        {
            return tree[tree[u].ls].cnt + count_lt(tree[u].rs, mid + 1, r, i);
        }
    }

    static void merge(int& u, int fu, int su, int l, int r)
    {
        if ((fu | su) == 0)
        {
            return;
        }

        u = create_node();

        tree[u].cnt = tree[fu].cnt + tree[su].cnt;

        if (l == r)
        {
            return;
        }

        const int mid = l + r >> 1;

        merge(tree[u].ls, tree[fu].ls, tree[su].ls, l, mid);
        merge(tree[u].rs, tree[fu].rs, tree[su].rs, mid + 1, r);
    }
};

class SegmentTree
{
public:

    using node = SubSegmentTree;

    std::vector<node> tree;

    static constexpr int maxw = 1e9 + 1;

    explicit SegmentTree(int n)
        : tree(n << 2)
    { }

    static int ls(int u)
    {
        return u << 1;
    }

    static int rs(int u)
    {
        return u << 1 | 1;
    }

    void push_up(int u)
    {
        node::merge(tree[u].root, tree[ls(u)].root, tree[rs(u)].root, 1, maxw);
    }

    void build(int u, int l, int r, const std::vector<int>& v)
    {
        if (l == r)
        {
            node::add(tree[u].root, 1, maxw, v[l], +1);
            return;
        }

        const int mid = l + r >> 1;

        build(ls(u), l, mid, v);
        build(rs(u), mid + 1, r, v);

        push_up(u);
    }

    void change(int u, int l, int r, int i, int old_value, int new_value)
    {
        node::add(tree[u].root, 1, maxw, old_value, -1);
        node::add(tree[u].root, 1, maxw, new_value, +1);

        if (l == r)
        {
            return;
        }

        const int mid = l + r >> 1;

        if (i <= mid)
        {
            change(ls(u), l, mid, i, old_value, new_value);
        }
        else
        {
            change(rs(u), mid + 1, r, i, old_value, new_value);
        }
    }

    int count_lt(int u, int l, int r, int x, int y, int i)
    {
        if (x <= l and r <= y)
        {
            return node::count_lt(tree[u].root, 1, maxw, i);
        }

        const int mid = l + r >> 1;

        int sum = 0;

        if (x <= mid)
        {
            sum = count_lt(ls(u), l, mid, x, y, i);
        }

        if (y > mid)
        {
            sum += count_lt(rs(u), mid + 1, r, x, y, i);
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

    int n, m;
    std::cin >> n >> m;

    std::vector<int> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
        ++v[i];
    }

    SegmentTree seg(n + 1);
    seg.build(1, 1, n, v);

    while (m--)
    {
        char opt;
        std::cin >> opt;

        if (opt == 'Q')
        {
            int l, r, k;
            std::cin >> l >> r >> k;

            auto check = [&](int mid) -> bool
            {
                const int cnt = seg.count_lt(1, 1, n, l, r, mid);
                return cnt < k;
            };

            int lo = 1, hi = 1e9 + 2, mid;

            while (hi - lo > 1)
            {
                mid = lo + hi >> 1;

                if (check(mid))
                {
                    lo = mid;
                }
                else
                {
                    hi = mid;
                }
            }

            std::cout << --lo << '\n';
        }
        else
        {
            int x, y;
            std::cin >> x >> y;

            ++y;

            seg.change(1, 1, n, x, v[x], y);
            v[x] = y;
        }
    }

    return 0;
}