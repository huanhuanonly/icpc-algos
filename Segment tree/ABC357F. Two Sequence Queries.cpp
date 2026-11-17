/**
 * SuntoryProgrammingContest2024（AtCoder Beginner Contest 357）
 *
 * => F - Two Sequence Queries ( @c 550 )
 *
 * -> https://atcoder.jp/contests/abc357/tasks/abc357_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc357/submissions/54497432 By huanhuanonly
 *
 * @b Segment-tree
 *
 * ----June 13, 2024 [15h:21m:01s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

constexpr int MOD = 998244353;

class SegmentTree
{
public:

    struct node
    {
        ullong first, second, sum;
    };

    std::vector<node> tree;
    std::vector<std::pair<ullong, ullong>> lazy;

    explicit SegmentTree(int n)
        : tree(n << 2), lazy(n << 2)
    { }

    static int ls(int u) { return u << 1; }
    static int rs(int u) { return u << 1 | 1; }

    void push_up(int u)
    {
        tree[u].first = (tree[ls(u)].first + tree[rs(u)].first) % MOD;
        tree[u].second = (tree[ls(u)].second + tree[rs(u)].second) % MOD;
        tree[u].sum = (tree[ls(u)].sum + tree[rs(u)].sum) % MOD;
    }

    void add_lazy_first(int u, int l, int r, ullong v)
    {
        (lazy[u].first += v) %= MOD;
        (tree[u].first += v * (r - l + 1) % MOD) %= MOD;
        (tree[u].sum += v * tree[u].second % MOD) %= MOD;
    }

    void add_lazy_second(int u, int l, int r, ullong v)
    {
        (lazy[u].second += v) %= MOD;
        (tree[u].second += v * (r - l + 1) % MOD) %= MOD;
        (tree[u].sum += v * tree[u].first % MOD) %= MOD;
    }

    void push_down(int u, int l, int r)
    {
        if (lazy[u].first)
        {
            int mid = l + r >> 1;
            add_lazy_first(ls(u), l, mid, lazy[u].first);
            add_lazy_first(rs(u), mid + 1, r, lazy[u].first);
            lazy[u].first = 0;
        }

        if (lazy[u].second)
        {
            int mid = l + r >> 1;
            add_lazy_second(ls(u), l, mid, lazy[u].second);
            add_lazy_second(rs(u), mid + 1, r, lazy[u].second);
            lazy[u].second = 0;
        }
    }

    void build(int u, int l, int r, const std::vector<std::pair<ullong, ullong>>& v)
    {
        if (l == r)
        {
            tree[u].first = v[l].first;
            tree[u].second = v[l].second;
            tree[u].sum = tree[u].first * tree[u].second % MOD;
            return;
        }

        int mid = l + r >> 1;

        build(ls(u), l, mid, v);
        build(rs(u), mid + 1, r, v);

        push_up(u);
    }

    void update(int u, int l, int r, int x, int y, const std::pair<ullong, ullong>& v)
    {
        if (x <= l and r <= y)
        {
            add_lazy_first(u, l, r, v.first);
            add_lazy_second(u, l, r, v.second);
            return;
        }

        push_down(u, l, r);

        int mid = l + r >> 1;

        if (x <= mid)
            update(ls(u), l, mid, x, y, v);
        if (y > mid)
            update(rs(u), mid + 1, r, x, y, v);

        push_up(u);
    }

    ullong get_sum(int u, int l, int r, int x, int y)
    {
        if (x <= l and r <= y)
            return tree[u].sum % MOD;

        push_down(u, l, r);

        int mid = l + r >> 1;
        ullong sum = 0;

        if (x <= mid)
            sum += get_sum(ls(u), l, mid, x, y);
        if (y > mid)
            sum += get_sum(rs(u), mid + 1, r, x, y);

        return sum % MOD;
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

    int n, q;
    std::cin >> n >> q;

    std::vector<std::pair<ullong, ullong>> v(n + 1);

    for (int i = 1; i <= n; ++i)
        std::cin >> v[i].first;

    for (int i = 1; i <= n; ++i)
        std::cin >> v[i].second;

    SegmentTree seg(n);

    seg.build(1, 1, n, v);

    ullong opt, l, r, x;

    while (q--)
    {
        std::cin >> opt >> l >> r;

        if (opt == 1)
        {
            std::cin >> x;
            seg.update(1, 1, n, l, r, std::make_pair(x, 0));
        }
        else if (opt == 2)
        {
            std::cin >> x;
            seg.update(1, 1, n, l, r, std::make_pair(0, x));
        }
        else
        {
            std::cout << seg.get_sum(1, 1, n, l, r) << '\n';
        }
    }

    return 0;
}