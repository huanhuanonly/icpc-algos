/**
 * Codeforces Round 888 (Div. 3)
 *
 * => F. Lisa and the Martians ( @c 1800 )
 *
 * -> https://codeforces.com/contest/1851/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/1851/submission/339195844 By huanhuanonly
 *
 * @b Binary-trie and @b Bitwise-inclusive-OR
 *
 * ----September 18, 2025 [10h:46m:25s]----
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
        std::array<int, 2> word;
        int id;
    };

    std::vector<node> tree;

    Trie() : tree(1) { }

    int apply_node()
    {
        tree.push_back({});
        return tree.size() - 1;
    }

    void insert(int n, int id)
    {
        int cur = 0;

        for (int i = (1 << 30 - 1); i >= 1; i >>= 1)
        {
            const bool c = n & i;

            if (tree[cur].word[c] == 0)
            {
                tree[cur].word[c] = apply_node();
            }

            cur = tree[cur].word[c];
        }

        tree[cur].id = id;
    }

    int find_max(int n)
    {
        int cur = 0;

        for (int i = (1 << 30 - 1); i >= 1; i >>= 1)
        {
            const bool c = n & i;

            if (tree[cur].word[c])
            {
                cur = tree[cur].word[c];
            }
            else
            {
                cur = tree[cur].word[not c];
            }
        }

        return tree[cur].id;
    }
};

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
        int n, k;
        std::cin >> n >> k;

        std::vector<int> v(n + 1);

        Trie trie;
        std::tuple<int, int, int, int> ans;

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> v[i];

            if (i > 1)
            {
                int j = trie.find_max(v[i]);
                int x = ((1 << k) - 1) ^ v[i];

                ans = std::max(ans, {(v[i] ^ x) & (v[j] ^ x), x, i, j});
            }

            trie.insert(v[i], i);
        }

        const auto& [max, x, i, j] = ans;
        std::cout << i << ' ' << j << ' ' << x << '\n';
    }

    return 0;
}