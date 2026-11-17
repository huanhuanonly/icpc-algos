/**
 * The 4th Universal Cup. Extra Stage 4: Chongqing
 * 第十一届中国大学生程序设计竞赛 重庆站（CCPC 2025 Chongqing Site）
 *
 * => E. Dinner Invitation
 *
 * -> https://qoj.ac/contest/3387/problem/15423
 *
 * Submissions ~> https://qoj.ac/submission/3442661 By huanhuanonly
 *
 * @b Binary-search
 * @b Binary-indexed-tree
 *
 * ----November 12, 2026 [18h:03m:15s]----
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
    typename _BinaryOperation = std::plus<>,
    typename _InverseBinaryOperation = std::minus<>>
class BinaryIndexedTree
{
public:

    using value_type = _Tp;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;

    explicit constexpr
    BinaryIndexedTree(size_type __n = 0, const value_type& __identity = {}) noexcept
        : _M_BITree(__n + 1, __identity), _M_op{}, _M_inv_op{}
    { }

    constexpr
    BinaryIndexedTree(
        size_type __n, const value_type& __identity,
        _BinaryOperation __op, _InverseBinaryOperation __inv_op) noexcept
            : _M_BITree(__n + 1, __identity), _M_op(__op), _M_inv_op(__inv_op)
    { }

    [[nodiscard]] static constexpr size_type
    lowbit(size_type __x) noexcept
    { return __x & -__x; }

    [[nodiscard]] constexpr const_reference
    identity() const noexcept
    { return _M_BITree.front(); }

    template<typename _Up>
    constexpr void
    add(size_type __i, const _Up& __x) noexcept
    {
        for (++__i; __i < _M_BITree.size(); __i += lowbit(__i))
        {
            _M_BITree[__i] = _M_op(_M_BITree[__i], __x);
        }
    }

    template<typename _Up>
    constexpr void
    subtract(size_type __i, const _Up& __x) noexcept
    {
        for (++__i; __i < _M_BITree.size(); __i += lowbit(__i))
        {
            _M_BITree[__i] = _M_inv_op(_M_BITree[__i], __x);
        }
    }

    [[nodiscard]] constexpr value_type
    prefix_reduce(size_type __r) const noexcept
    {
        value_type result = _M_BITree[++__r];

        for (__r -= lowbit(__r); __r; __r -= lowbit(__r))
        {
            result = _M_op(_M_BITree[__r], result);
        }

        return result;
    }

    [[nodiscard]] constexpr value_type
    reduce(size_type __l, size_type __r) const noexcept
    { return __l ? _M_inv_op(prefix_reduce(__r), prefix_reduce(__l - 1)) : prefix_reduce(__r); }

    [[nodiscard]] constexpr value_type
    reduce() const noexcept
    { return empty() ? identity() : reduce(0, size() - 1); }

    [[nodiscard]] constexpr value_type
    get(size_type __i) const noexcept
    { return reduce(__i, __i); }

    constexpr void
    set(size_type __i, value_type __x) noexcept
    { reset(__i), add(__i, __x); }

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
    resize(size_type __n)
    {
        const auto c =
            std::views::iota(size_type{}, size()) |
            std::views::transform([&](size_type i) { return get(i); }) |
            std::ranges::to<std::vector>();

        for (size_type i = 0; i < size(); subtract(i, c[i]), ++i);
        _M_BITree.resize(__n + 1, identity());
        for (size_type i = 0; i < static_cast<size_type>(c.size()); add(i, c[i]), ++i);
    }

private:

    std::vector<value_type> _M_BITree;

    [[no_unique_address]] _BinaryOperation _M_op;
    [[no_unique_address]] _InverseBinaryOperation _M_inv_op;
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n;
        std::cin >> n;

        std::vector<std::pair<uint64, uint64>> v(n);

        for (auto& w : v | std::views::keys)
        {
            std::cin >> w;
        }

        for (auto& r : v | std::views::values)
        {
            std::cin >> r;
        }

        auto s = v | std::views::keys | std::ranges::to<std::vector>();
        std::ranges::sort(s);

        std::vector<int> offset(n);

        auto pos = [&](uint64 x) -> int
        {
            const auto p = std::ranges::lower_bound(s, x) - s.begin();
            return p + offset[p]++;
        };

        struct valsize
        {
            uint64 value;
            uint64 size;

            valsize operator+(const valsize& rhs) const
            {
                return valsize{value + rhs.value, size + rhs.size};
            }

            valsize operator-(const valsize& rhs) const
            {
                return valsize{value - rhs.value, size - rhs.size};
            }
        };

        BinaryIndexedTree<valsize> bit(n);

        for (int i = 0; i < n; ++i)
        {
            bit.add(i, valsize{s[i], 1});
        }

        std::ranges::sort(v, {}, &std::pair<uint64, uint64>::second);

        auto check = [&](int mid, uint64 limit) -> bool
        {
            const auto [value, size] = bit.prefix_reduce(mid);
            return size ? (value + size - 1) / size <= limit : true;
        };

        uint64 ans = 0;

        for (int i = 0; i < n; ++i)
        {
            int l = -1, r = n, mid;

            while (r - l > 1)
            {
                mid = l + r >> 1;

                if (check(mid, v[i].second))
                {
                    l = mid;
                }
                else
                {
                    r = mid;
                }
            }

            if (l >= 0)
            {
                ans = std::max(ans, bit.prefix_reduce(l).size);
            }

            bit.set(pos(v[i].first), valsize{0, 0});
        }

        std::cout << ans << '\n';
    }

    return 0;
}