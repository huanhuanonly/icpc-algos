/**
 * => P4052 [JSOI2007] 文本生成器 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P4052
 *
 * Submissions ~> https://www.luogu.com.cn/record/280276965 By huanhuanonly
 *
 * @b Automaton-DP on @b Aho-Corasick-automaton
 *
 * ----June 01, 2026 [11h:58m:37s]----
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

class AhoCorasickAutomaton
{
public:

    struct node
    {
        std::array<int, 26> word;
        int fail;
        bool end;
    };

    std::vector<node> tree;

    AhoCorasickAutomaton() : tree(1) { }

    void insert(const std::string& s)
    {
        int now = 0;

        for (char c : s)
        {
            const int i = c - 'A';

            if (not tree[now].word[i])
            {
                tree[now].word[i] = tree.size();
                tree.emplace_back();
            }

            now = tree[now].word[i];
        }

        tree[now].end = true;
    }

    void build()
    {
        std::queue<int> que;

        for (int i = 0; i < 26; ++i)
        {
            if (tree[0].word[i])
            {
                que.push(tree[0].word[i]);
            }
        }

        while (not que.empty())
        {
            const int now = que.front();
            que.pop();

            for (int i = 0; i < 26; ++i)
            {
                if (tree[now].word[i])
                {
                    tree[tree[now].word[i]].fail = tree[tree[now].fail].word[i];
                    que.push(tree[now].word[i]);
                }
                else
                {
                    tree[now].word[i] = tree[tree[now].fail].word[i];
                }
            }

            tree[now].end |= tree[tree[now].fail].end;
        }
    }
};

inline namespace huanhuanonly {
    inline namespace math
{
template<
    typename _Tp, std::unsigned_integral _Up, typename _Mp,
    typename _MulOp = std::multiplies<_Tp>, typename _ModOp = std::modulus<void>>
requires
    requires(_MulOp __op, _Tp __x) { { __op(__x, __x) } -> std::convertible_to<_Tp>; } and
    requires(_ModOp __op, _Tp __lhs, _Mp __rhs) { { __op(__lhs, __rhs) } -> std::convertible_to<_Tp>; }
[[nodiscard]] constexpr _Tp
binary_exponentiation(_Tp __lhs, _Up __rhs, _Mp __mod, _MulOp __mul_op = {}, _ModOp __mod_op = {})
{
    auto result = static_cast<_Tp>(1);

    for (__lhs = __mod_op(__lhs, __mod); __rhs; __lhs = __mod_op(__mul_op(__lhs, __lhs), __mod), __rhs >>= 1)
    {
        if (__rhs & 1)
        {
            result = __mod_op(__mul_op(result, __lhs), __mod);
        }
    }

    return result;
}

template<typename _Tp, std::unsigned_integral _Up, typename _MulOp = std::multiplies<_Tp>>
requires requires(_MulOp __op, _Tp __x) { { __op(__x, __x) } -> std::convertible_to<_Tp>; }
[[nodiscard]] constexpr _Tp
binary_exponentiation(_Tp __lhs, _Up __rhs, _MulOp __mul_op = {})
{
    auto result = static_cast<_Tp>(1);

    for (; __rhs; __lhs = __mul_op(__lhs, __lhs), __rhs >>= 1)
    {
        if (__rhs & 1)
        {
            result = __mul_op(result, __lhs);
        }
    }

    return result;
}
}} // namespace huanhuanonly::math

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

    constexpr uint64 mod = 1e4 + 7;

    AhoCorasickAutomaton acam;

    std::string s;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> s;
        acam.insert(s);
    }

    acam.build();

    std::vector<uint64> f(acam.tree.size()), g(f.size());
    f[0] = 1;

    for (int i = 0; i < m; ++i)
    {
        for (int u = 0; u < f.size(); ++u)
        {
            for (int v : acam.tree[u].word)
            {
                if (not acam.tree[v].end)
                {
                    (g[v] += f[u]) %= mod;
                }
            }
        }

        std::swap(f, g);
        g.assign(f.size(), 0);
    }

    std::cout << (binary_exponentiation(26ULL, uint64(m), mod) + mod - *std::ranges::fold_left_first(f, std::plus{}) % mod) % mod << '\n';

    return 0;
}