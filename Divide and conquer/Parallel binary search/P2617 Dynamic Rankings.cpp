/**
 * bzoj1901
 *
 * => P2617 Dynamic Rankings ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P2617
 *
 * Submissions ~> https://www.luogu.com.cn/record/288604274 By huanhuanonly
 *
 * @b Parallel-binary-search
 * @b Binary-indexed-tree
 *
 * ----July 26, 2026 [00h:11m:03s]----
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

inline namespace huanhuanonly {
    inline namespace data_structure
{
template<
    typename _Tp,
    typename _BinaryOperation = std::plus<_Tp>,
    typename _InverseBinaryOperation = std::minus<_Tp>>
class BinaryIndexedTree
{
public:

    using value_type = _Tp;
    using size_type = int;

    explicit constexpr
    BinaryIndexedTree(size_type __n = 0, value_type __identity = {}) noexcept
        : _M_BITree(__n + 1, __identity), _M_op{}, _M_inv_op{}
    { }

    constexpr
    BinaryIndexedTree(size_type __n, value_type __identity, _BinaryOperation __op, _InverseBinaryOperation __inv_op) noexcept
        : _M_BITree(__n + 1, __identity), _M_op(__op), _M_inv_op(__inv_op)
    { }

    [[nodiscard]] static constexpr size_type
    lowbit(size_type __x) noexcept
    { return __x & -__x; }

    constexpr void
    add(size_type __i, value_type __value) noexcept
    {
        for (++__i; __i < _M_BITree.size(); __i += lowbit(__i))
        {
            _M_BITree[__i] = _M_op(_M_BITree[__i], __value);
        }
    }

    constexpr void
    subtract(size_type __i, value_type __value) noexcept
    {
        for (++__i; __i < _M_BITree.size(); __i += lowbit(__i))
        {
            _M_BITree[__i] = _M_inv_op(_M_BITree[__i], __value);
        }
    }

    [[nodiscard]] constexpr value_type
    prefix_sum(size_type __r) const noexcept
    {
        value_type result = _M_BITree[++__r];

        for (__r -= lowbit(__r); __r; __r -= lowbit(__r))
        {
            result = _M_op(_M_BITree[__r], result);
        }

        return result;
    }

    [[nodiscard]] constexpr value_type
    sum(size_type __l, size_type __r) const noexcept
    { return __l ? _M_inv_op(prefix_sum(__r), prefix_sum(__l - 1)) : prefix_sum(__r); }

    [[nodiscard]] constexpr value_type
    sum() const noexcept
    { return sum(0, size() - 1); }

    [[nodiscard]] constexpr value_type
    get(size_type __i) const noexcept
    { return sum(__i, __i); }

    constexpr void
    set(size_type __i, value_type __value) noexcept
    { reset(__i), add(__i, __value); }

    constexpr void
    reset(size_type __i) noexcept
    { subtract(__i, get(__i)); }

    constexpr void
    reset() noexcept
    { for (size_type i = 0; i < size(); reset(i), ++i); }

    [[nodiscard]] constexpr size_type
    size() const noexcept
    { return static_cast<size_type>(_M_BITree.size()) - 1; }

    [[nodiscard]] constexpr bool
    empty() const noexcept
    { return size() == 0; }

    constexpr void
    resize(size_type __n) noexcept
    { _M_BITree.resize(__n + 1); }

private:

    std::vector<value_type> _M_BITree;

    _BinaryOperation _M_op;
    _InverseBinaryOperation _M_inv_op;
};
}} // namespace huanhuanonly::data_structure

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

    struct query
    {
        enum { Q, C } type;

        union
        {
            struct { int l, r, k, id; };
            struct { int pos, value, add; };

            struct { int l, r, k, id; } q;
            struct { int pos, value, add; } c;
        };
    };

    std::vector<int64> v(n + 1);
    std::vector<query> queries;

    std::vector<int64> ans(m + 1, ~0);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
        queries.push_back(query{.type = query::C, .c = {i, v[i], 1}});
    }

    for (int i = 1; i <= m; ++i)
    {
        char type;
        std::cin >> type;

        if (type == 'Q')
        {
            int l, r, k;
            std::cin >> l >> r >> k;

            queries.push_back(query{.type = query::Q, .q = {l, r, k, i}});
        }
        else
        {
            int x, y;
            std::cin >> x >> y;

            queries.push_back(query{.type = query::C, .c = {x, v[x], -1}});
            queries.push_back(query{.type = query::C, .c = {x, v[x] = y, 1}});
        }
    }

    BinaryIndexedTree<int64> bit(n + 1);

    auto divide = [&](const auto& self, int64 l, int64 r, int64 ql, int64 qr) -> void
    {
        if (ql > qr)
        {
            return;
        }

        if (l == r)
        {
            for (int i = ql; i <= qr; ++i)
            {
                if (queries[i].type == query::Q)
                {
                    ans[queries[i].id] = l;
                }
            }

            return;
        }

        const auto mid = l + r >> 1;

        std::vector<query> lq, rq;

        for (int i = ql; i <= qr; ++i)
        {
            if (queries[i].type == query::C)
            {
                if (queries[i].value <= mid)
                {
                    bit.add(queries[i].pos, queries[i].add);
                    lq.push_back(queries[i]);
                }
                else
                {
                    rq.push_back(queries[i]);
                }
            }
            else
            {
                const auto cnt = bit.sum(queries[i].l, queries[i].r);

                if (cnt >= queries[i].k)
                {
                    lq.push_back(queries[i]);
                }
                else
                {
                    queries[i].k -= cnt;
                    rq.push_back(queries[i]);
                }
            }
        }

        for (int i = ql; i <= qr; ++i)
        {
            if (queries[i].type == query::C and queries[i].value <= mid)
            {
                bit.subtract(queries[i].pos, queries[i].add);
            }
        }

        std::ranges::move(rq, std::ranges::move(lq, queries.begin() + ql).out);

        self(self, l, mid, ql, ql + lq.size() - 1);
        self(self, mid + 1, r, ql + lq.size(), qr);
    };

    divide(divide, 0, 1e9, 0, queries.size() - 1);

    for (int i = 1; i <= m; ++i)
    {
        if (~ans[i])
        {
            std::cout << ans[i] << '\n';
        }
    }

    return 0;
}