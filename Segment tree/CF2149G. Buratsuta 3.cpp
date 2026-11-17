/**
 * Codeforces Round 1054 (Div. 3)
 *
 * => G. Buratsuta 3 ( @c 2100 )
 *
 * -> https://codeforces.com/contest/2149/problem/G
 *
 * Submissions ~> https://codeforces.com/contest/2149/submission/340654055 By huanhuanonly
 *
 * @b Segment-tree and @b Extended-Boyer–Moore-majority-vote-algorithm
 *
 * @see https://zhuanlan.zhihu.com/p/387744743
 *
 * ----September 27, 2025 [01h:21m:16s]----
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

inline namespace huanhuanonly
{
template<typename _ValueType, typename _MergeFunc = std::plus<_ValueType>>
class SegmentTree
{
public:

    using value_type = _ValueType;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = int;

    constexpr explicit SegmentTree(size_type __n = 0)
        : tree(nodes_count(__n))
    { }

    constexpr SegmentTree(size_type __n, _MergeFunc __merge)
        : tree(nodes_count(__n)), merge(__merge)
    { }

    constexpr SegmentTree(size_type __n, const value_type& __value)
        : SegmentTree(__n)
    { set(__value); }

    constexpr SegmentTree(size_type __n, const value_type& __value, _MergeFunc __merge)
        : tree(nodes_count(__n)), merge(__merge)
    { set(__value); }

    template<typename _Container, typename = std::void_t<decltype(std::declval<_Container>().size()), decltype(std::declval<_Container>().begin())>>
    constexpr SegmentTree(const _Container& __c)
        : SegmentTree(static_cast<size_type>(std::size(__c)))
    { build(std::begin(__c)); }

    template<typename _Container, typename = std::void_t<decltype(std::declval<_Container>().size()), decltype(std::declval<_Container>().begin())>>
    constexpr SegmentTree(const _Container& __c, _MergeFunc __merge)
        : tree(nodes_count(static_cast<size_type>(std::size(__c)))), merge(__merge)
    { build(std::begin(__c)); }

    template<typename _ForwardIterator>
    constexpr SegmentTree(_ForwardIterator __first, _ForwardIterator __last)
        : SegmentTree(static_cast<size_type>(std::distance(__first, __last)))
    { build(__first, __last); }

    template<typename _ForwardIterator>
    constexpr SegmentTree(_ForwardIterator __first, _ForwardIterator __last, _MergeFunc __merge)
        : tree(nodes_count(static_cast<size_type>(std::distance(__first, __last)))), merge(__merge)
    { build(__first, __last); }

    [[nodiscard]] static constexpr size_type nodes_count(size_type __n) noexcept
    { return __n << 2; }

    [[nodiscard]] constexpr size_type nodes_count() const noexcept
    { return tree.size(); }

    [[nodiscard]] constexpr size_type size() const noexcept
    { return static_cast<size_type>(tree.size()) >> 2; }

    constexpr void resize(size_type __n)
    { tree.resize(nodes_count(__n)); }


    template<typename _Callback>
    constexpr void for_each(int __l, int __r, _Callback __func)
    { _M_for_each(1, 1, size(), __l + 1, __r + 1, __func); }

    template<typename _Callback>
    constexpr void for_each(_Callback __func)
    { for_each(0, size() - 1, __func); }


    template<typename _ForwardIterator>
    constexpr void build(_ForwardIterator __first)
    { build(0, size() - 1, __first); }

    template<typename _ForwardIterator>
    constexpr void build(int __l, int __r, _ForwardIterator __first)
    { for_each(__l, __r, [&](value_type& __v) -> bool { __v = *__first; ++__first; return true; }); }

    template<typename _ForwardIterator>
    constexpr void build(_ForwardIterator __first, _ForwardIterator __last)
    { build(0, __first, __last); }

    template<typename _ForwardIterator>
    constexpr void build(int __l, _ForwardIterator __first, _ForwardIterator __last)
    { if (__first != __last) { for_each(__l, size() - 1, [&](value_type& __v) -> bool { __v = *__first; return ++__first != __last; }); } }


    template<typename _ForwardIterator>
    constexpr void flatten(_ForwardIterator __first, size_type __n = std::numeric_limits<size_type>::max())
    { if (__n) { for_each(0, __n - 1, [&](const value_type& __v) -> bool { *__first = __v; ++__first; return true; }); } }

    template<typename _ForwardIterator>
    constexpr void flatten(int __l, int __r, _ForwardIterator __first)
    { for_each(__l, __r, [&](const value_type& __v) -> bool { *__first = __v; ++__first; return true; }); }

    template<typename _ForwardIterator>
    constexpr void flatten(_ForwardIterator __first, _ForwardIterator __last)
    { flatten(0, __first, __last); }

    template<typename _ForwardIterator>
    constexpr void flatten(int __l, _ForwardIterator __first, _ForwardIterator __last)
    { if (__first != __last) { for_each(__l, size() - 1, [&](const value_type& __v) -> bool { *__first = __v; return ++__first != __last; }); } }


    [[nodiscard]] constexpr value_type reduce(int __l, int __r)
    { return _M_reduce(1, 1, size(), __l + 1, __r + 1); }

    [[nodiscard]] constexpr const_reference at(int __p)
    { return _M_at(1, 1, size(), __p + 1); }

    [[nodiscard]] constexpr const_reference operator[](int __p)
    { return at(__p); }

    [[nodiscard]] constexpr value_type operator[](const std::pair<int, int>& __p)
    { return reduce(__p.first, __p.second); }

    template<typename _Tp = value_type>
    constexpr void set(const _Tp& __value)
    { set(0, size() - 1, __value); }

    template<typename _Tp, typename _BinaryOperation>
    constexpr void set(const _Tp& __value, _BinaryOperation __binary_op)
    { set(0, size() - 1, __value, __binary_op); }

    template<typename _Tp = value_type>
    constexpr void set(int __p, const _Tp& __value)
    { set(__p, __p, __value); }

    template<typename _Tp, typename _BinaryOperation>
    constexpr void set(int __p, const _Tp& __value, _BinaryOperation __binary_op)
    { set(__p, __p, __value, __binary_op); }

    template<typename _Tp = value_type>
    constexpr void set(int __l, int __r, const _Tp& __value)
    { for_each(__l, __r, [&](value_type& __v) -> bool { __v = __value; return true; }); }

    template<typename _Tp, typename _BinaryOperation>
    constexpr void set(int __l, int __r, const _Tp& __value, _BinaryOperation __binary_op)
    { for_each(__l, __r, [&](value_type& __v) -> bool { __v = __binary_op(__v, __value); return true; }); }


    constexpr void reset()
    { std::fill(tree.begin(), tree.end(), value_type{}); }

protected:

    [[nodiscard]] static constexpr int ls(int p) noexcept
    { return p << 1; }

    [[nodiscard]] static constexpr int rs(int p) noexcept
    { return p << 1 | 1; }

    constexpr void push_up(int p)
    { tree[p] = merge(tree[ls(p)], tree[rs(p)]); }

    virtual void push_down(int p, int l, int r)
    { }

    template<typename _Callback>
    constexpr bool _M_for_each(int p, int l, int r, int x, int y, _Callback&& __func)
    {
        if (l == r)
        {
            return __func(tree[p]);
        }

        push_down(p, l, r);

        int mid = l + r >> 1;

        bool continues = true;

        if (x <= mid)
        {
            continues = _M_for_each(ls(p), l, mid, x, y, __func);
        }

        if (y > mid and continues)
        {
            continues = _M_for_each(rs(p), mid + 1, r, x, y, __func);
        }

        push_up(p);

        return continues;
    }

    [[nodiscard]] constexpr value_type _M_reduce(int p, int l, int r, int x, int y)
    {
        if (x <= l and r <= y)
        {
            return tree[p];
        }

        push_down(p, l, r);

        int mid = l + r >> 1;

        if (x <= mid and y > mid)
            return merge(_M_reduce(ls(p), l, mid, x, y), _M_reduce(rs(p), mid + 1, r, x, y));
        else if (x <= mid)
            return _M_reduce(ls(p), l, mid, x, y);
        else
            return _M_reduce(rs(p), mid + 1, r, x, y);
    }

    [[nodiscard]] constexpr const_reference _M_at(int p, int l, int r, int i)
    {
        if (l == r)
        {
            return tree[p];
        }

        push_down(p, l, r);

        int mid = l + r >> 1;

        if (i <= mid)
            return _M_at(ls(p), l, mid, i);
        else
            return _M_at(rs(p), mid + 1, r, i);
    }

    std::vector<value_type> tree;
    _MergeFunc merge{};
};

template<typename _Container>
SegmentTree(const _Container&) -> SegmentTree<typename _Container::value_type>;

template<typename _Container, typename _MergeFunc>
SegmentTree(const _Container&, _MergeFunc) -> SegmentTree<typename _Container::value_type, _MergeFunc>;

template<typename _ForwardIterator>
SegmentTree(_ForwardIterator, _ForwardIterator) -> SegmentTree<decltype(*std::declval<_ForwardIterator>())>;

template<typename _ForwardIterator, typename _MergeFunc>
SegmentTree(_ForwardIterator, _ForwardIterator, _MergeFunc) -> SegmentTree<decltype(*std::declval<_ForwardIterator>()), _MergeFunc>;
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, q;
        std::cin >> n >> q;

        std::vector<int> v(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> v[i];
        }

        auto s = v;
        std::ranges::sort(s);
        s.erase(std::ranges::unique(s).begin(), s.end());

        std::vector<std::vector<int>> pos(n);

        for (int i = 0; i < n; ++i)
        {
            v[i] = std::ranges::lower_bound(s, v[i]) - s.begin();
            pos[v[i]].push_back(i);
        }

        auto count = [&](int value, int l, int r) -> int
        {
            const auto& ref = pos[value];

            const auto li = std::ranges::lower_bound(ref, l);
            const auto ri = std::ranges::upper_bound(ref, r);

            return ri - li;
        };

        struct node
        {
            struct item
            {
                int value;
                int count;
            };

            std::array<item, 2> data;

            node operator+(node other) const
            {
                node self = *this;

                for (int i = 0; i < other.data.size(); ++i)
                {
                    if (self.data[0].value == other.data[i].value)
                    {
                        self.data[0].count += other.data[i].count;
                        continue;
                    }

                    if (self.data[1].value == other.data[i].value)
                    {
                        self.data[1].count += other.data[i].count;
                        continue;
                    }

                    const int min = std::min({self.data[0].count, self.data[1].count, other.data[i].count});

                    self.data[0].count -= min;
                    self.data[1].count -= min;
                    other.data[i].count -= min;

                    if (other.data[i].count)
                    {
                        if (self.data[0].count == 0)
                        {
                            self.data[0] = other.data[i];
                        }
                        else
                        {
                            self.data[1] = other.data[i];
                        }
                    }
                }

                if (self.data[0].value > self.data[1].value)
                {
                    std::swap(self.data[0], self.data[1]);
                }

                return self;
            }
        };

        SegmentTree<node> seg(n);

        seg.for_each([&, i = 0](node& nd) mutable -> bool {
            nd = {node::item{-1, 0}, node::item{v[i++], 1}};
            return true;
        });

        while (q--)
        {
            int l, r;
            std::cin >> l >> r;

            --l, --r;

            const int len = r - l + 1;

            const auto result = seg.reduce(l, r);

            int cnt = 0;

            if (result.data[0].value != -1 and count(result.data[0].value, l, r) > len / 3)
            {
                ++cnt;
                std::cout << s[result.data[0].value] << ' ';
            }

            if (result.data[1].value != -1 and count(result.data[1].value, l, r) > len / 3)
            {
                ++cnt;
                std::cout << s[result.data[1].value] << ' ';
            }

            if (cnt == 0)
            {
                std::cout << -1;
            }

            std::cout.put('\n');
        }
    }

    return 0;
}