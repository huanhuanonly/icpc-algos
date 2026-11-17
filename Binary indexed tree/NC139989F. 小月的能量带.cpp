/**
 * 牛客周赛 Round 160
 *
 * => F-小月的能量带 ( @c 1700 )
 *
 * -> https://ac.nowcoder.com/acm/contest/139989/F
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84668522 By huanhuanonly
 *
 * @b Binary-search
 * @b Binary-indexed-tree
 *
 * ----September 08, 2026 [17h:45m:28s]----
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

    int64 n, t;
    std::cin >> n >> t;

    struct interval
    {
        int64 l, r;
        auto operator<=>(const interval& rhs) const = default;
    };

    std::vector<interval> v(n);
    std::map<int64, std::vector<int64>> map;

    for (auto& [l, r] : v)
    {
        std::cin >> l >> r;
        map[l].push_back(r);
    }

    for (auto& [key, value] : map)
    {
        std::ranges::sort(value);
    }

    int64 ans = 0;

    for (const auto& [l, r] : v)
    {
        const auto& ref = map[r - t];

        const auto lit = std::ranges::lower_bound(ref, l);
        const auto rit = std::ranges::lower_bound(ref, r);

        ans += rit - lit;
    }

    std::vector<int64> set;
    set.reserve(n + n);

    for (int64 i = 0; i < n; ++i)
    {
        set.push_back(v[i].l);
        set.push_back(v[i].r);
    }

    std::ranges::sort(set);
    set.erase(std::ranges::unique(set).begin(), set.end());

    auto $ = [&](int64 i) -> int64
    {
        return std::ranges::lower_bound(set, i) - set.begin();
    };

    BinaryIndexedTree<int64> bit(set.size());

    std::ranges::sort(v, {}, [](const interval& i) { return std::pair(i.r, -i.l); });

    for (int64 i = 0; i < n; ++i)
    {
        if (v[i].r - v[i].l == t)
        {
            ans += bit.sum($(v[i].l), $(v[i].r));
        }

        bit.add($(v[i].l), 1);
    }

    std::cout << ans << '\n';

    return 0;
}