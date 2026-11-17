/**
 * Codeforces Round 1052 (Div. 2)
 *
 * => D2. Max Sum OR (Hard Version) ( @c 2000 )
 *
 * -> https://codeforces.com/contest/2146/problem/D2
 *
 * Submissions ~> https://codeforces.com/contest/2146/submission/340067931 By huanhuanonly
 *
 * @b Binary-trie
 *
 * ----September 24, 2025 [01h:30m:39s]----
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
        uint32 id;
        uint32 cnt;
    };

    std::vector<node> tree;
    int size;

    Trie() : tree(1), size(0) { }

    int apply_node()
    {
        tree.push_back({});
        return tree.size() - 1;
    }

    void insert(uint32 n, uint32 id)
    {
        ++size;

        int cur = 0;

        for (uint32 i = 1; i <= (1 << 30 - 1); i <<= 1)
        {
            const bool c = n & i;

            if (tree[cur].word[c] == 0)
            {
                tree[cur].word[c] = apply_node();
            }

            cur = tree[cur].word[c];
            ++tree[cur].cnt;
        }

        tree[cur].id = id;
    }

    void erase(uint32 n)
    {
        --size;

        int cur = 0;

        for (uint32 i = 1; i <= (1 << 30 - 1); i <<= 1)
        {
            const bool c = n & i;

            cur = tree[cur].word[c];
            --tree[cur].cnt;
        }
    }

    uint32 find_max(uint32 n)
    {
        if (size == 0)
        {
            return n;
        }

        int cur = 0;

        for (uint32 i = 1; i <= (1 << 30 - 1); i <<= 1)
        {
            const bool c = not (n & i);

            if (tree[cur].word[c] and tree[tree[cur].word[c]].cnt)
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
        uint32 l, r;
        std::cin >> l >> r;

        std::vector<uint32> v;
        v.reserve(r - l + 1);

        Trie trie;

        for (uint32 i = l; i <= r; ++i)
        {
            trie.insert(i, i);
        }

        uint64 sum = 0;

        for (uint32 i = l; i <= r; ++i)
        {
            uint32 value = trie.find_max(i);
            trie.erase(value);

            sum += value | i;
            v.push_back(value);
        }

        std::cout << sum << '\n';

        for (auto it = v.begin(); it != v.end(); ++it)
        {
            std::cout << *it << ' ';
        }

        std::cout.put('\n');
    }

    return 0;
}