/**
 * AtCoder Beginner Contest 475
 *
 * => E - Quiz Competition: Qualifiers ( @c 475 )
 *
 * -> https://atcoder.jp/contests/abc475/tasks/abc475_e
 *
 * Submissions ~> https://atcoder.jp/contests/abc475/submissions/79271376 By huanhuanonly
 *
 * @b Binary-trie
 *
 * ----September 15, 2026 [09h:19m:02s]----
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
        int size;
    };

    std::vector<node> tree;

    Trie() : tree(1) { }

    void insert(const std::vector<bool>& s)
    {
        int u = 0;

        for (const bool b : s)
        {
            if (not tree[u].word[b])
            {
                tree[u].word[b] = tree.size();
                tree.emplace_back();
            }

            u = tree[u].word[b];
            ++tree[u].size;
        }
    }

    void remove(const std::vector<bool>& s)
    {
        int u = 0;

        for (const bool b : s)
        {
            u = tree[u].word[b];
            --tree[u].size;
        }
    }

    bool check(const std::vector<bool>& s, int cnt)
    {
        int u = 0;

        for (const bool b : s)
        {
            if (tree[tree[u].word[0]].size <= cnt)
            {
                if (b == false)
                {
                    return true;
                }

                cnt -= tree[tree[u].word[0]].size;
                u = tree[u].word[1];
            }
            else
            {
                if (b == true)
                {
                    return false;
                }

                u = tree[u].word[0];
            }
        }

        return false;
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

    int n, m, k;
    std::cin >> n >> m >> k;

    std::string t;
    std::cin >> t;

    std::vector v(n, std::vector<bool>(k));
    std::string s;

    Trie trie;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> s;

        for (int j = 0; j < k; ++j)
        {
            v[i][j] = s[j] != t[j];
        }

        trie.insert(v[i]);
    }

    int q;
    std::cin >> q;

    while (q--)
    {
        int i, j;
        std::cin >> i >> j;

        --i, --j;

        trie.remove(v[i]);
        v[i][j] = not v[i][j];
        trie.insert(v[i]);

        if (trie.check(v[i], m))
        {
            std::cout << "Yes\n";
        }
        else
        {
            std::cout << "No\n";
        }
    }

    return 0;
}