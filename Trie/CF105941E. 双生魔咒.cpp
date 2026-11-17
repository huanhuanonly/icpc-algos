/**
 * 2025 National Invitational of CCPC (Zhengzhou), 2025 CCPC Henan Provincial Collegiate Programming Contest
 *
 * => E. 双生魔咒
 *
 * -> https://codeforces.com/gym/105941/problem/E
 *
 * Submissions ~> https://codeforces.com/gym/105941/submission/391048897 By huanhuanonly
 *
 * @b Trie
 *
 * ----September 17, 2026 [23h:46m:45s]----
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
        std::array<int, 26> word;
        int cnt;
    };

    std::vector<node> tree;

    Trie() : tree(1) { }

    void insert(const std::string& s)
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
            ++tree[u].cnt;
        }
    }

    int64 dfs(int u) const
    {
        if (not u)
        {
            return 0;
        }

        int64 cnt = int64(tree[u].cnt / 2) * ((tree[u].cnt + 1) / 2);

        for (const auto& v : tree[u].word)
        {
            cnt += dfs(v);
        }

        return cnt;
    }

    int64 count() const
    {
        int64 cnt = 0;

        for (const auto& v : tree[0].word)
        {
            cnt += dfs(v);
        }

        return cnt;
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

    int n;
    std::cin >> n;

    n <<= 1;

    Trie trie;
    std::string s;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> s;
        trie.insert(s);
    }

    std::cout << trie.count() << '\n';

    return 0;
}