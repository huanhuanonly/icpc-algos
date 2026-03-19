/**
 * 2026牛客寒假算法基础集训营6
 * 
 * => C-小L的线段树 ( @c 2000 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120566/C
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82627257 By huanhuanonly
 * 
 * @b Segment-tree
 * 
 * ----March 07, 2026 [11h:53m:50s]----
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

class SegmentTree
{
public:

    struct node
    {
        int  count = 1;
        bool destroyed = false;
    };

    explicit SegmentTree(int n) : tree(n << 2) { }

    static int ls(int u) { return u << 1; }
    static int rs(int u) { return u << 1 | 1; }

    void push_up(int u)
    {
        if (tree[u].destroyed)
        {
            tree[u].count = tree[ls(u)].count + tree[rs(u)].count;
        }
        else
        {
            tree[u].count = 1;
        }
    }

    void destroy(int u, int l, int r, int x, int y)
    {
        if (x <= l and r <= y)
        {
            tree[u].destroyed = true;
            
            if (x == y)
            {
                tree[u].count = 0;
            }
            else
            {
                push_up(u);
            }

            return;
        }

        int mid = l + r >> 1;

        if (x <= mid)
        {
            destroy(ls(u), l, mid, x, y);
        }

        if (y > mid)
        {
            destroy(rs(u), mid + 1, r, x, y);
        }

        push_up(u);
    }

    int count(int u, int l, int r, int x, int y) const
    {
        if (x <= l and r <= y)
        {
            return tree[u].count;
        }

        int mid = l + r >> 1;

        int cnt = not tree[u].destroyed;

        if (x <= mid)
        {
            cnt += count(ls(u), l, mid, x, y);
        }

        if (y > mid)
        {
            cnt += count(rs(u), mid + 1, r, x, y);
        }

        return cnt;
    }

private:

    std::vector<node> tree;
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

    SegmentTree seg(n);

    for (int i = 0; i < n; ++i)
    {
        int opt, l, r;
        std::cin >> opt >> l >> r;

        if (opt == 1)
        {
            seg.destroy(1, 1, n, l, r);
        }
        else
        {
            std::cout << seg.count(1, 1, n, l, r) << '\n';
        }
    }

    return 0;
}