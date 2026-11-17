/**
 * Yandex.Algorithm 2011: Round 2
 *
 * => C. Genetic engineering ( @c 2500 )
 *
 * -> https://codeforces.com/contest/86/problem/C
 *
 * Submissions ~> https://codeforces.com/contest/86/submission/255960019 By huanhuanonly
 *
 * @b Automaton-DP on @b Aho-Corasick-automaton
 * @b Digit-DP
 *
 * ----April 10, 2024 [14h:59m:39s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class AhoCorasickAutomaton
{
public:

    struct node
    {
        int word[4];
        int fail;
        int end;
    };

    std::vector<node> tree;

    AhoCorasickAutomaton() : tree(1) { }

    static int map(char c)
    {
        switch (c)
        {
            case 'A':
                return 0;

            case 'C':
                return 1;

            case 'G':
                return 2;

            case 'T':
                return 3;

            default:
                return 5201314;
        }
    }

    int push_node()
    {
        tree.push_back({});
        return tree.size() - 1;
    }

    void insert(const std::string& s)
    {
        int now = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            int c = map(s[i]);

            if (tree[now].word[c] == 0)
                tree[now].word[c] = push_node();

            now = tree[now].word[c];
        }

        tree[now].end = std::max<int>(tree[now].end, s.size());
    }

    void build_fail()
    {
        std::queue<int> que;

        for (int i = 0; i < 4; ++i)
            if (tree[0].word[i])
                que.push(tree[0].word[i]);

        while (not que.empty())
        {
            int now = que.front();
            que.pop();

            for (int i = 0; i < 4; ++i)
            {
                if (tree[now].word[i])
                {
                    que.push(tree[now].word[i]);
                    tree[tree[now].word[i]].fail = tree[tree[now].fail].word[i];
                }
                else
                {
                    tree[now].word[i] = tree[tree[now].fail].word[i];
                }
            }

            tree[now].end = std::max(tree[now].end, tree[tree[now].fail].end);
        }
    }

    ullong count(int len, int mod)
    {
        std::vector<std::vector<std::vector<ullong>>> dp(
            len, std::vector<std::vector<ullong>>(
                tree.size(), std::vector<ullong>(
                    11, -1))
        );

        /**
         * @param l The last location marked with end
        */
        std::function<ullong(int, int, int)> dfs = [&](int pos, int now, int l) -> ullong
        {
            if (pos == len)
                return pos - tree[now].end <= l and tree[now].end;

            if (pos - l > 10)
                return 0;

            if (dp[pos][now][pos - l] != -1)
                return dp[pos][now][pos - l];

            ullong sum = 0;

            for (int i = 0; i < 4; ++i)
            {
                sum += dfs(pos + 1, tree[now].word[i], pos - tree[now].end <= l ? pos : l);
                sum %= mod;
            }

            return dp[pos][now][pos - l] = sum;
        };

        return dfs(0, 0, 0);
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("Input.txt", "r", stdin);
    ::freopen("Output.txt", "w", stdout);
#endif

    int n, m;
    std::cin >> n >> m;

    AhoCorasickAutomaton tree;

    std::string s;

    for (int i = 0; i < m; ++i)
    {
        std::cin >> s;
        tree.insert(s);
    }

    tree.build_fail();

    std::cout << tree.count(n, 1e9 + 9);

    return 0;
}