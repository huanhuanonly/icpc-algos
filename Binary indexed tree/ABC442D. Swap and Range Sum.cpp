/**
 * JPRS Programming Contest 2026#1 (AtCoder Beginner Contest 442)
 * 
 * => D - Swap and Range Sum ( @c 400 )
 * 
 * -> https://atcoder.jp/contests/abc442/tasks/abc442_d
 * 
 * Submissions ~> https://atcoder.jp/contests/abc442/submissions/72700566 By huanhuanonly
 * 
 * @b Binary-indexed-tree
 * 
 * ----January 24, 2026 [22h:08m:10s]----
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
// Fenwick Tree
template<typename _Tp>
class BinaryIndexedTree
{
public:

    using value_type = _Tp;

    constexpr BinaryIndexedTree() noexcept = default;

    explicit constexpr BinaryIndexedTree(std::size_t __size) noexcept
        : _M_BITree(__size + 1)
    { }

    [[nodiscard]] static constexpr std::size_t lowbit(std::size_t __x) noexcept
    { return __x & -__x; }

    constexpr void add(std::size_t __i, value_type __value = 1)
    {
        for (++__i; __i < _M_BITree.size(); __i += lowbit(__i))
        {
            _M_BITree[__i] += __value;
        }
    }

    constexpr void subtract(std::size_t __i, value_type __value = 1)
    {
        for (++__i; __i < _M_BITree.size(); __i += lowbit(__i))
        {
            _M_BITree[__i] -= __value;
        }
    }

    [[nodiscard]] constexpr value_type sum(std::size_t __l)
    {
        value_type result{};

        for (++__l; __l; __l -= lowbit(__l))
        {
            result += _M_BITree[__l];
        }

        return result;
    }

    [[nodiscard]] constexpr value_type sum(std::size_t __l, std::size_t __r)
    { return __l ? sum(__r) - sum(__l - 1) : sum(__r); }

    [[nodiscard]] constexpr value_type get(std::size_t __i)
    { return sum(__i, __i); }

    constexpr value_type set(std::size_t __i, value_type __value)
    {
        value_type prev = get(__i);

        prev < __value ? add(__i, __value - prev) : subtract(__i, prev - __value);

        return prev;
    }

    constexpr void reset(std::size_t __size = static_cast<std::size_t>(-1))
    { __size == static_cast<std::size_t>(-1) ? std::ranges::fill(_M_BITree, value_type{}) : _M_BITree.assign(__size + 1, value_type{}); }

private:

    std::vector<value_type> _M_BITree;
};
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

    BinaryIndexedTree<int64> bit(n + 1);

    for (int64 i = 1, v; i <= n; ++i)
    {
        std::cin >> v;
        bit.add(i, v);
    }

    while (q--)
    {
        int opt;
        std::cin >> opt;

        if (opt == 1)
        {
            int64 i;
            std::cin >> i;

            const int64 x = bit.get(i), y = bit.get(i + 1);
            bit.set(i, y), bit.set(i + 1, x);
        }
        else
        {
            int64 l, r;
            std::cin >> l >> r;

            std::cout << bit.sum(l, r) << '\n';
        }
    }

    return 0;
}