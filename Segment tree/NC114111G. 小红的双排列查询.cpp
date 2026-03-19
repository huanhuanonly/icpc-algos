/**
 * 牛客周赛 Round 102
 * 
 * => G-小红的双排列查询 ( @c 2000 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/114111/G
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=78487996 By huanhuanonly
 * 
 * @b Segment-tree
 * 
 * ----July 27, 2025 [21h:15m:34s]----
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
template<typename _ValueType>
class SegmentTree
{
public:

    using value_type = _ValueType;

    explicit SegmentTree(std::size_t __n)
            : tree(__n << 2)
    { }

    template<typename _MergeFunc>
    SegmentTree(std::size_t __n, _MergeFunc __func)
            : tree(__n << 2), merge(__func)
    { }

    SegmentTree(std::size_t __n, const value_type& __value)
            : tree(__n << 2, __value)
    { }

    template<typename _MergeFunc>
    SegmentTree(std::size_t __n, const value_type& __value, _MergeFunc __func)
            : tree(__n << 2, __value), merge(__func)
    { }

    template<typename _Container, typename = std::void_t<decltype(std::declval<_Container>().size()), decltype(std::declval<_Container>().begin())>>
    SegmentTree(const _Container& __c)
            : tree(std::size(__c) << 2)
    { build(std::begin(__c)); }

    template<typename _Container, typename _MergeFunc, typename = std::void_t<decltype(std::declval<_Container>().size()), decltype(std::declval<_Container>().begin())>>
    SegmentTree(const _Container& __c, _MergeFunc __func)
            : tree(std::size(__c) << 2), merge(__func)
    { build(std::begin(__c)); }


    constexpr int size() const noexcept
    { return static_cast<int>(tree.size()) >> 2; }
    
    template<typename _ForwardIterator>
    void build(_ForwardIterator __first)
    { _M_build(1, 1, static_cast<int>(size()), __first); }
    
    template<typename _Container, typename = std::void_t<decltype(std::declval<_Container>().begin())>>
    void build(const _Container& __c)
    { build(__c.begin()); }

    template<std::size_t _StartingIndex, typename _Container, typename = std::void_t<decltype(std::declval<_Container>().begin())>>
    void build(const _Container& __c)
    { build(std::next(__c.begin(), _StartingIndex)); }


    template<typename _ForwardIterator>
    void to_vector(_ForwardIterator __first)
    { _M_to_vector(1, 1, size(), __first); }

    value_type sum(int __l, int __r)
    { return _M_sum(1, 1, size(), __l + 1, __r + 1); }

    value_type sum(int __p)
    { return sum(__p, __p); }

    const value_type& at(int __p)
    { return _M_at(1, 1, size(), __p + 1); }

    const value_type& operator[](int __p)
    { return at(__p); }

    template<typename _Tp>
    void set(int __p, const _Tp& __value = value_type{})
    {
        _M_set(1, 1, size(), __p + 1, __value,
            [](const value_type& [[maybe_unused]] __self, const _Tp& __value) {
                return __value;
            });
    }

    template<typename _Tp, typename _BinaryOperation>
    void set(int __p, const _Tp& __value, _BinaryOperation __binary_op)
    { _M_set(1, 1, size(), __p + 1, __value, __binary_op); }

protected:

    static constexpr int ls(int p) noexcept
    { return p << 1; }

    static constexpr int rs(int p) noexcept
    { return p << 1 | 1; }

    void push_up(int p)
    { tree[p] = merge(tree[ls(p)], tree[rs(p)]); }

    virtual void push_down(int p, int l, int r)
    { }

    template<typename _ForwardIterator>
    void _M_build(int p, int l, int r, _ForwardIterator& it)
    {
        if (l == r)
        {
            tree[p] = *it;
            ++it;

            return;
        }

        int mid = l + r >> 1;

        _M_build(ls(p), l, mid, it);
        _M_build(rs(p), mid + 1, r, it);

        push_up(p);
    }

    template<typename _ForwardIterator>
    void _M_to_vector(int p, int l, int r, _ForwardIterator& it)
    {
        if (l == r)
        {
            *it = tree[p];
            ++it;

            return;
        }

        push_down(p, l, r);

        int mid = l + r >> 1;

        _M_to_vector(ls(p), l, mid, it);
        _M_to_vector(rs(p), mid + 1, r, it);
    }

    value_type _M_sum(int p, int l, int r, int x, int y)
    {
        if (x <= l and r <= y)
        {
            return tree[p];
        }

        push_down(p, l, r);

        int mid = l + r >> 1;

        if (x <= mid and y > mid)
            return merge(_M_sum(ls(p), l, mid, x, y), _M_sum(rs(p), mid + 1, r, x, y));
        else if (x <= mid)
            return _M_sum(ls(p), l, mid, x, y);
        else
            return _M_sum(rs(p), mid + 1, r, x, y);
    }

    const value_type& _M_at(int p, int l, int r, int i)
    {
        if (l == r)
        {
            return tree[p];
        }

        push_down(p, l, r);

        int mid = l + r >> 1;

        if (i <= mid)
            return _M_at(ls(p), l, r, i);
        else
            return _M_at(rs(p), mid + 1, r, i);
    }

    template<typename _Tp, typename _BinaryOperation>
    void _M_set(int p, int l, int r, int i, const _Tp& v, const _BinaryOperation& bop)
    {
        if (l == r)
        {
            tree[p] = bop(tree[p], v);
            return;
        }

        push_down(p, l, r);

        int mid = l + r >> 1;

        if (i <= mid)
            _M_set(ls(p), l, mid, i, v, bop);
        else
            _M_set(rs(p), mid + 1, r, i, v, bop);

        push_up(p);
    }

    std::vector<value_type> tree;
    std::function<value_type(const value_type&, const value_type&)> merge = std::plus();
};

template<typename _Tp>
SegmentTree(std::size_t, const _Tp&) -> SegmentTree<_Tp>;

template<typename _Container>
SegmentTree(const _Container&) -> SegmentTree<typename _Container::value_type>;
}


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

    std::vector<int> v(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i];
    }

    SegmentTree<int> seg_min(n, [](int x, int y) -> int { return std::min(x, y); });
    SegmentTree<int> seg_max(n, [](int x, int y) -> int { return std::max(x, y); });

    SegmentTree<int> seg_sum(n, [](int x, int y) -> int { return x + y; });

    seg_min.build<0>(v);
    seg_max.build<0>(v);

    seg_sum.build<0>(v);

    std::random_device rd;
    std::mt19937 rng(rd());
    std::set<int> st;

    std::vector<int> table(n + 1);
    
    for (int i = 0; i < n; ++i)
    {
        int r = rng();

        for (; st.contains(r); r = rng());

        st.insert(r);
        table[i] = r;
    }

    SegmentTree<int> seg_xor(n, [](int x, int y) -> int { return x ^ y; });
    std::ranges::transform(v, v.begin(), [&table](int x) -> int { return table[x]; });

    seg_xor.build<0>(v);

    while (q--)
    {
        int l, r;
        std::cin >> l >> r;

        --l, --r;

        int len = r - l + 1;

        if (len % 2 == 0 and seg_min.sum(l, r) == 1 and seg_max.sum(l, r) == len / 2 and seg_xor.sum(l, r) == 0 and seg_sum.sum(l, r) == len / 2 * (len / 2 + 1))
        {
            std::cout << "Yes\n";
        }
        else
        {
            std::cout << "No\n";
        }
    }

    return 0;
}