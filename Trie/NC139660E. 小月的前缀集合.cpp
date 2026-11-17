/**
 * 牛客周赛 Round 159
 *
 * => E-小月的前缀集合 ( @c 1200 )
 *
 * -> https://ac.nowcoder.com/acm/contest/139660/E
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84627270 By huanhuanonly
 *
 * @b Binary-trie
 *
 * ----August 31, 2026 [08h:53m:07s]----
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

class Trie
{
public:

    struct node
    {
        std::array<int, 2> word;
        int cnt;
    };

    std::vector<node> tree;
    int total = 0;

    Trie()
        : tree(1)
    { }

    int new_node()
    {
        tree.emplace_back();
        return tree.size() - 1;
    }

    void insert(const std::string& s)
    {
        int u = 0;

        for (int c : s)
        {
            c -= '0';

            if (not tree[u].word[c])
            {
                tree[u].word[c] = new_node();
            }

            u = tree[u].word[c];

            if (not tree[u].cnt++)
            {
                ++total;
            }
        }
    }

    void remove(const std::string& s)
    {
        int u = 0;

        for (int c : s)
        {
            c -= '0';
            u = tree[u].word[c];

            if (not --tree[u].cnt)
            {
                --total;
            }
        }
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    Trie trie;

    int q;
    std::cin >> q;

    char op;
    std::string s;

    while (q--)
    {
        std::cin >> op >> s;

        if (op == '+')
        {
            trie.insert(s);
        }
        else
        {
            trie.remove(s);
        }

        std::cout << trie.total << '\n';
    }

    return 0;
}