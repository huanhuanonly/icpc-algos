/**
 * Japan Registry Services (JPRS) Programming Contest 2025#2 (AtCoder Beginner Contest 415)
 *
 * => F - Max Combo ( @c 525 )
 *
 * -> https://atcoder.jp/contests/abc415/tasks/abc415_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc415/submissions/67782255 By huanhuanonly
 *
 * @b Segment-tree ( @a maximum-subarray-sum )
 *
 * ----July 20, 2025 [18h:10m:42s]----
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

class SegmentTree
{
public:

    struct node
    {
        int value;
        int vl, vr;
        int size;
    };

    enum lazy_tag : uint8
    {
        DoNothing = 0,
        FullUp,
        Clear
    };

    explicit SegmentTree(int n)
        : tree(n << 2)
    { }

    static int ls(int u)
    { return u << 1; }

    static int rs(int u)
    { return u << 1 | 1; }

    void build(int u, int l, int r, const std::string& s, char c)
    {
        if (l == r)
        {
            if (s[l - 1] == c)
            {
                tree[u].vl = tree[u].vr = tree[u].value = 1;
            }

            tree[u].size = 1;
            return;
        }

        int mid = l + r >> 1;

        build(ls(u), l, mid, s, c);
        build(rs(u), mid + 1, r, s, c);

        push_up(u);
    }

    node merge(const node& fn, const node& sn)
    {
        return node{
            .value = std::max({fn.value, sn.value, fn.vr + sn.vl}),
            .vl = fn.value == fn.size ? fn.value + sn.vl : fn.vl,
            .vr = sn.value == sn.size ? sn.value + fn.vr : sn.vr,
            .size = fn.size + sn.size
        };
    }

    void push_up(int u)
    {
        tree[u] = merge(tree[ls(u)], tree[rs(u)]);
    }

    void update(int u, int l, int r, int pos, lazy_tag tag)
    {
        if (l == r)
        {
            if (tag == FullUp)
            {
                tree[u].vl = tree[u].vr = tree[u].value = r - l + 1;
            }
            else // if (tag == clear)
            {
                tree[u].vl = tree[u].vr = tree[u].value = 0;
            }

            return;
        }

        int mid = l + r >> 1;

        if (pos <= mid)
        {
            update(ls(u), l, mid, pos, tag);
        }
        else
        {
            update(rs(u), mid + 1, r, pos, tag);
        }

        push_up(u);
    }

    void full_up(int u, int l, int r, int pos)
    {
        update(u, l, r, pos, FullUp);
    }

    void clear(int u, int l, int r, int pos)
    {
        update(u, l, r, pos, Clear);
    }

    node get(int u, int l, int r, int x, int y)
    {
        if (x <= l and r <= y)
        {
            return tree[u];
        }

        int mid = l + r >> 1;

        if (y <= mid)
        {
            return get(ls(u), l, mid, x, y);
        }
        else if (x > mid)
        {
            return get(rs(u), mid + 1, r, x, y);
        }
        else
        {
            return merge(get(ls(u), l, mid, x, y), get(rs(u), mid + 1, r, x, y));
        }
    }

private:

    std::vector<node> tree;
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, q;
    std::cin >> n >> q;

    std::vector segs(26, SegmentTree(n));

    std::string s;
    std::cin >> s;

    for (char c = 'a'; c <= 'z'; ++c)
    {
        segs[c - 'a'].build(1, 1, n, s, c);
    }

    int opt;

    while (q--)
    {
        std::cin >> opt;

        if (opt == 1)
        {
            int i;
            char x;

            std::cin >> i >> x;

            segs[s[i - 1] - 'a'].clear(1, 1, n, i);

            s[i - 1] = x;

            segs[x - 'a'].full_up(1, 1, n, i);
        }
        else
        {
            int l, r;
            std::cin >> l >> r;

            int max = 0;

            for (int i = 0; i < 26; ++i)
            {
                max = std::max(max, segs[i].get(1, 1, n, l, r).value);
            }

            std::cout << max << '\n';
        }
    }

    return 0;
}