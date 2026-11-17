/**
 * Codeforces Round 1016 (Div. 3)
 *
 * => G. Shorten the Array ( @c 1900 )
 *
 * -> https://codeforces.com/contest/2093/problem/G
 *
 * Submissions ~> https://codeforces.com/contest/2093/submission/315270356 By huanhuanonly
 *
 * @b Binary-trie
 *
 * ----April 13, 2025 [21h:33m:38s]----
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

class Trie
{
public:

    struct node
    {
        uint32 son[2];
        uint32 time;
    };

    Trie() : tree(1, node{ {0, 0}, 0 }) { }

    void insert(uint32 value, uint32 time)
    {
        uint32 now = 0;

        for (uint32 i = 30; i--; )
        {
            uint32 c = value >> i & 1;

            if (tree[now].son[c] == 0)
            {
                tree.push_back(node{ {0, 0}, 0 });
                tree[now].son[c] = tree.size() - 1;
            }

            now = tree[now].son[c];
            tree[now].time = std::max(tree[now].time, time);
        }
    }

    std::optional<uint32> find(uint32 value, uint32 k)
    {
        uint32 now = 0;
        uint32 max = 0;

        for (uint32 i = 30; i--; )
        {
            uint32 cv = value >> i & 1;
            uint32 ck = k >> i & 1;

            if (ck == 0)
            {
                // let ck = 1
                if (tree[now].son[cv ^ 1])
                {
                    max = std::max(max, tree[tree[now].son[cv ^ 1]].time);
                }
            }

            if (tree[now].son[cv ^ ck] == 0)
            {
                return max ? std::make_optional(max) : std::nullopt;
            }

            now = tree[now].son[cv ^ ck];
        }

        return std::max(max, tree[now].time);
    }

private:

    std::vector<node> tree;
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
        uint32 n, k;
        std::cin >> n >> k;

        std::vector<uint32> v(n + 1);

        for (uint32 i = 1; i <= n; ++i)
        {
            std::cin >> v[i];
        }

        uint32 ans = std::numeric_limits<decltype(ans)>::max();

        Trie trie;

        for (uint32 i = 1; i <= n; ++i)
        {
            trie.insert(v[i], i);

            if (auto res = trie.find(v[i], k); res.has_value())
            {
                ans = std::min(ans, i - res.value() + 1);
            }
        }

        if (ans != std::numeric_limits<decltype(ans)>::max())
            std::cout << ans << '\n';
        else
            std::cout << -1 << '\n';
    }

    return 0;
}