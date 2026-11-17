/**
 * The 2023 Guangdong Provincial Collegiate Programming Contest
 *
 * => F. Traveling in Cells
 *
 * -> https://codeforces.com/gym/104369/problem/F
 *
 * Submissions ~> https://codeforces.com/gym/104369/submission/388983274 By huanhuanonly
 *
 * @b Binary-search on @b Segment-tree
 * @b Binary-indexed-tree
 *
 * ----August 31, 2026 [17h:35m:42s]----
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

namespace SegmentTree
{
    struct node
    {
        int ls, rs;
        int value;
    };

    std::vector<node> tree(2e7);
    int idx = 0;

    void update(int& u, int l, int r, int pos, int add)
    {
        if (not u)
        {
            u = ++idx;
        }

        tree[u].value += add;

        if (l == r)
        {
            return;
        }

        const int mid = l + r >> 1;

        if (pos <= mid)
        {
            update(tree[u].ls, l, mid, pos, add);
        }
        else
        {
            update(tree[u].rs, mid + 1, r, pos, add);
        }
    }

    int sum(const auto& roots)
    {
        int s = 0;

        for (const auto& u : roots)
        {
            s += tree[u].value;
        }

        return s;
    }

    auto ls(const auto& roots)
    {
        auto s = roots;

        for (auto& u : s)
        {
            u = tree[u].ls;
        }

        return s;
    }

    auto rs(const auto& roots)
    {
        auto s = roots;

        for (auto& u : s)
        {
            u = tree[u].rs;
        }

        return s;
    }

    std::pair<int, bool> find_left(const auto& roots, int l, int r, int pos)
    {
        if (sum(roots) == r - l + 1)
        {
            return {l, true};
        }
        else if (l == r)
        {
            if (l == pos)
            {
                return {l, true};
            }
            else
            {
                return {0, false};
            }
        }

        const auto mid = l + r >> 1;

        if (pos <= mid)
        {
            return find_left(ls(roots), l, mid, pos);
        }
        else
        {
            if (const auto res = find_left(rs(roots), mid + 1, r, pos); res.second)
            {
                if (const auto res2 = find_left(ls(roots), l, mid, pos); res2.first)
                {
                    return res2;
                }
                else
                {
                    return {res.first, false};
                }
            }
            else
            {
                return res;
            }
        }
    }

    std::pair<int, bool> find_right(const auto& roots, int l, int r, int pos)
    {
        if (sum(roots) == r - l + 1)
        {
            return {r, true};
        }
        else if (l == r)
        {
            if (r == pos)
            {
                return {r, true};
            }
            else
            {
                return {0, false};
            }
        }

        const auto mid = l + r >> 1;

        if (pos > mid)
        {
            return find_right(rs(roots), mid + 1, r, pos);
        }
        else
        {
            if (const auto res = find_right(ls(roots), l, mid, pos); res.second)
            {
                if (const auto res2 = find_right(rs(roots), mid + 1, r, pos); res2.first)
                {
                    return res2;
                }
                else
                {
                    return {res.first, false};
                }
            }
            else
            {
                return res;
            }
        }
    }
};

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
        int n, q;
        std::cin >> n >> q;

        std::vector<int> roots(n + 1);
        BinaryIndexedTree<int64> bit(n + 1);

        std::vector<int> color(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> color[i];
            SegmentTree::update(roots[color[i]], 1, n, i, 1);
        }

        for (int i = 1, v; i <= n; ++i)
        {
            std::cin >> v;
            bit.add(i, v);
        }

        while (q--)
        {
            int op;
            std::cin >> op;

            if (op == 1)
            {
                int p, x;
                std::cin >> p >> x;

                SegmentTree::update(roots[color[p]], 1, n, p, -1);
                color[p] = x;
                SegmentTree::update(roots[color[p]], 1, n, p, +1);
            }
            else if (op == 2)
            {
                int p, x;
                std::cin >> p >> x;

                bit.set(p, x);
            }
            else
            {
                int x, k;
                std::cin >> x >> k;

                std::vector<int> set(k);

                for (int i = 0; i < k; ++i)
                {
                    std::cin >> set[i];
                }

                std::vector<int> us(k);

                for (auto&& [u, s] : std::views::zip(us, set))
                {
                    u = roots[s];
                }

                std::cout << bit.sum(
                    SegmentTree::find_left(us, 1, n, x).first,
                    SegmentTree::find_right(us, 1, n, x).first) << '\n';
            }
        }
    }

    return 0;
}