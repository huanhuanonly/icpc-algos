/**
 * AtCoder Beginner Contest 419
 *
 * => F - All Included ( @c 550 )
 *
 * -> https://atcoder.jp/contests/abc419/tasks/abc419_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc419/submissions/78514995 By huanhuanonly
 *
 * @b Automaton-DP on @b Aho-Corasick-automaton
 * @b Bitmask-DP
 *
 * ----August 19, 2026 [02h:15m:19s]----
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

        int mask;
    };

    std::vector<node> tree;

    AhoCorasickAutomaton() : tree(1) { }

    int create_node()
    {
        tree.emplace_back();
        return tree.size() - 1;
    }

    void insert(const std::string& s, int id)
    {
        int u = 0;

        for (int c : s)
        {
            c -= 'a';

            if (not tree[u].word[c])
            {
                tree[u].word[c] = create_node();
            }

            u = tree[u].word[c];
        }

        tree[u].mask |= 1 << id;
    }

    void build()
    {
        std::queue<int> que;

        for (int i = 0; i < tree.front().word.size(); ++i)
        {
            if (tree[0].word[i])
            {
                que.push(tree.front().word[i]);
            }
        }

        while (not que.empty())
        {
            const int u = que.front();
            que.pop();

            for (int i = 0; i < tree.front().word.size(); ++i)
            {
                if (tree[u].word[i])
                {
                    tree[tree[u].word[i]].fail = tree[tree[u].fail].word[i];
                    que.push(tree[u].word[i]);
                }
                else
                {
                    tree[u].word[i] = tree[tree[u].fail].word[i];
                }
            }

            tree[u].mask |= tree[tree[u].fail].mask;
        }
    }

    uint64 calc(int len, int n, uint64 mod) const
    {
        std::vector dp(len + 1, std::vector(tree.size(), std::vector(1 << n, uint64{})));
        dp[0][0][0] = 1;

        for (int i = 0; i < len; ++i)
        {
            for (int u = 0; u < tree.size(); ++u)
            {
                for (int mask = 0; mask < 1 << n; ++mask)
                {
                    for (int c = 0; c < tree.front().word.size(); ++c)
                    {
                        (dp[i + 1][tree[u].word[c]][mask | tree[tree[u].word[c]].mask] += dp[i][u][mask]) %= mod;
                    }
                }
            }
        }

        uint64 cnt = 0;

        for (int u = 0; u < tree.size(); ++u)
        {
            (cnt += dp.back()[u].back()) %= mod;
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

    int n, len;
    std::cin >> n >> len;

    AhoCorasickAutomaton acam;
    std::string s;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> s;
        acam.insert(s, i);
    }

    acam.build();

    std::cout << acam.calc(len, n, 998244353) << '\n';

    return 0;
}