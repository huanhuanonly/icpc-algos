/**
 * 牛客周赛 Round 163
 *
 * => F-小月的前缀 ( @c 1500 )
 *
 * -> https://ac.nowcoder.com/acm/contest/140737/F
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84823727 By huanhuanonly
 *
 * @b Trie
 *
 * ----September 28, 2026 [00h:15m:50s]----
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

struct Trie
{
    struct node
    {
        std::array<int, 26> word;
        int cnt;
        int id;
    };

    std::vector<node> tree;

    Trie() : tree(1) { }

    void insert(int id, const std::string& s, int cnt)
    {
        int u = 0;

        for (int c : s)
        {
            c -= 'a';

            if (not tree[u].word[c])
            {
                tree[u].word[c] = tree.size();
                tree.emplace_back();
            }

            u = tree[u].word[c];
        }

        tree[u].cnt = cnt;
        tree[u].id = id;
    }

    int find(const std::string& s)
    {
        int u = 0;
        int last = 0;

        for (int c : s)
        {
            c -= 'a';

            if (not tree[u].word[c])
            {
                break;
            }

            u = tree[u].word[c];

            if (tree[u].cnt)
            {
                last = u;
            }
        }

        if (last)
        {
            --tree[last].cnt;
            return tree[last].id;
        }
        else
        {
            return 0;
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

    int n, q;
    std::cin >> n >> q;

    Trie trie;
    std::string s;

    for (int i = 1, c; i <= n; ++i)
    {
        std::cin >> s >> c;
        trie.insert(i, s, c);
    }

    while (q--)
    {
        std::cin >> s;
        std::cout << trie.find(s) << '\n';
    }

    return 0;
}