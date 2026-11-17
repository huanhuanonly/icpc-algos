/**
 * 2024牛客暑期多校训练营7
 *
 * => D-Interval Selection
 *
 * -> https://ac.nowcoder.com/acm/contest/81602/D
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=71108748 By huanhuanonly
 *
 * @b Segment-tree
 *
 * ----August 22, 2024 [16h:16m:17s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

template<typename _ValueType>
class SegmentTree
{
public:
    using value_type = _ValueType;

    std::vector<value_type> tree;

    std::function<value_type(const value_type&, const value_type&)> merge;

    explicit SegmentTree(
        std::size_t n,
        const decltype(merge)& func = [](const value_type& lv, const value_type& rv) -> value_type { return lv + rv; })
            : tree(n << 2), merge(func)
    { }

    SegmentTree(
        std::size_t n,
        const value_type& value,
        const decltype(merge)& func = [](const value_type& lv, const value_type& rv) -> value_type { return lv + rv; })
            : tree(n << 2, value), merge(func)
    { }

    static constexpr std::size_t ls(std::size_t p) { return p << 1; }
    static constexpr std::size_t rs(std::size_t p) { return p << 1 | 1; }

    void push_up(int p)
    {
        tree[p] = merge(tree[ls(p)], tree[rs(p)]);
    }

    virtual void push_down(int p, int l, int r)
    { }

    void build(int p, int l, int r, const std::vector<value_type>& arr)
    {
        if (l == r)
        {
            tree[p] = arr[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(ls(p), l, mid, arr);
        build(rs(p), mid + 1, r, arr);

        push_up(p);
    }

    value_type get_sum(int p, int l, int r, int x, int y)
    {
        if (x <= l and r <= y)
            return tree[p];

        push_down(p, l, r);

        value_type res{};
        int mid = (l + r) >> 1;

        if (x <= mid)
            res = merge(res, get_sum(ls(p), l, mid, x, y));
        if (y > mid)
            res = merge(res, get_sum(rs(p), mid + 1, r, x, y));

        return res;
    }
};

template<typename _ValueType, typename _LazyType>
class LazySegmentTree : public SegmentTree<_ValueType>
{
public:
    using value_type = _ValueType;
    using lazy_type  = _LazyType;

    using SegmentTree<_ValueType>::ls;
    using SegmentTree<_ValueType>::rs;

    using SegmentTree<_ValueType>::push_up;

    using SegmentTree<_ValueType>::tree;

    std::vector<lazy_type> lazy;

    template<typename ...Args>
    LazySegmentTree(Args&& ...args)
        : SegmentTree<_ValueType>(args...), lazy(tree.size()) { }

    virtual void add_lazy(int p, int l, int r, const lazy_type& v)
    {
        lazy[p] += v;
        tree[p].min += v;
    }

    virtual void push_down(int p, int l, int r) override
    {
        if (lazy[p])
        {
            int mid = (l + r) >> 1;

            add_lazy(ls(p), l, mid, lazy[p]);
            add_lazy(rs(p), mid + 1, r, lazy[p]);
            lazy[p] = 0;
        }
    }

    void update(int p, int l, int r, int x, int y, const lazy_type& v)
    {
        if (x <= l and r <= y)
        {
            add_lazy(p, l, r, v);
            return;
        }

        push_down(p, l, r);

        int mid = (l + r) >> 1;

        if (x <= mid)
            update(ls(p), l, mid, x, y, v);
        if (y > mid)
            update(rs(p), mid + 1, r, x, y, v);

        push_up(p);
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, k;
        std::cin >> n >> k;

        std::vector<int> v(n + 1);

        std::map<int, std::vector<int>> mp;

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> v[i];
            mp[v[i]].push_back(i);
        }

        struct node
        {
            int min, count;
        };

        LazySegmentTree<node, int> seg(n, [](const node& lv, const node& rv) -> node
        {
            if (lv.min == rv.min)
                return node{lv.min, lv.count + rv.count};
            else if (lv.min < rv.min)
                return lv;
            else
                return rv;
        });

        seg.build(1, 1, n, std::vector<node>(n + 1, node{0, 1}));

        ullong ans = 0;

        std::map<int, int> idx;

        std::map<int, std::function<void(void)>> undo;

        // Enumerate the right endpoints, and count the feasible left endpoints
        for (int i = 1; i <= n; ++i)
        {
            if (undo.find(v[i]) != undo.end())
                undo[v[i]]();

            if (idx[v[i]] >= k)
            {
                seg.update(1, 1, n, 1, mp[v[i]][idx[v[i]] - k], 1);
            }

            if (idx[v[i]] >= k - 1)
            {
                if (k != 1)
                {
                    int start = mp[v[i]][idx[v[i]] - k + 1] + 1;

                    seg.update(1, 1, n, start, i, 1);

                    undo[v[i]] = [&seg, n, start, i]() -> void
                    {
                        seg.update(1, 1, n, start, i, -1);
                    };
                }

                node nd = seg.get_sum(1, 1, n, 1, i);

                if (nd.min == 0)
                    ans += nd.count;
            }
            else
            {
                seg.update(1, 1, n, 1, i, 1);

                undo[v[i]] = [&seg, n, i]() -> void
                {
                    seg.update(1, 1, n, 1, i, -1);
                };
            }

            ++idx[v[i]];
        }

        std::cout << ans << '\n';
    }

    return 0;
}