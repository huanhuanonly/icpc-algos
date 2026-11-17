/**
 * Codeforces Round 1119 (Div. 3)
 *
 * => E. Treasure Map Destruction (Constructive Version) ( @c 1500 )
 *
 * -> https://codeforces.com/contest/2259/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/2259/submission/389547834 By huanhuanonly
 *
 * @b Binary-indexed-tree
 *
 * ----September 06, 2026 [00h:06m:58s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n;
        std::cin >> n;

        BinaryIndexedTree<int> bit(n);

        std::vector<std::pair<int, int>> set;
        std::vector<int> pre(n + 1);

        for (int i = 0, v; i < n; ++i)
        {
            std::cin >> v;

            if (v > 0)
            {
                set.emplace_back(i - v, i + v);
                ++pre[std::max(0, i - v + 1)];
                --pre[std::min(n - 1, i + v - 1) + 1];
            }
            else if (v == 0)
            {
                bit.add(i, 1);
            }
        }

        std::ranges::sort(set);
        std::partial_sum(pre.begin(), pre.end(), pre.begin());

        bool yes = true;

        for (int i = 0; i < n; ++i)
        {
            if (pre[i] and bit.sum(i, i))
            {
                yes = false;
                break;
            }
        }

        for (const auto& [l, r] : set)
        {
            const auto mid = l + r >> 1;

            if (l >= 0 and not pre[l] and not bit.sum(l + 1, mid))
            {
                bit.add(l, 1);
            }
            else if (r < n and not pre[r] and not bit.sum(mid, r - 1))
            {
                bit.add(r, 1);
            }
            else
            {
                yes = false;
                break;
            }
        }

        if (set.empty())
        {
            std::cout << std::string(n, '1') << '\n';
        }
        else if (yes)
        {
            std::string s;

            for (int i = 0; i < n; ++i)
            {
                s.push_back('0' + !!bit.sum(i, i));
            }

            if (s.find('1') != s.npos)
            {
                std::cout << s << '\n';
            }
            else
            {
                std::cout << "-1\n";
            }
        }
        else
        {
            std::cout << "-1\n";
        }
    }

    return 0;
}