/**
 * => P3311 [SDOI2014] 数数 ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P3311
 *
 * Submissions ~> https://www.luogu.com.cn/record/150699994 By huanhuanonly
 *
 * @b Automaton-DP on @b Aho-Corasick-automaton
 * @b Digit-DP
 *
 * ----March 13, 2024 [20h:17m:56s]----
*/

#include <bits/stdc++.h>

using uint = unsigned int;
using llong = long long int;
using ullong = unsigned long long int;
using ldouble = long double;

class AhoCorasickAutomaton
{
public:

    AhoCorasickAutomaton() : tree(1) { }

    explicit AhoCorasickAutomaton(std::size_t __size)
        : tree(1)
    {
        tree.reserve(__size);
    }

    struct node
    {
        int word[10];
        int fail;

        bool end;
    };

    std::vector<node> tree;

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
            int c = s[i] - '0';

            if (tree[now].word[c] == 0)
                tree[now].word[c] = push_node();

            now = tree[now].word[c];
        }

        tree[now].end = true;
    }

    void build_fail()
    {
        std::queue<int> que;

        for (int i = 0; i < 10; ++i)
            if (tree[0].word[i])
                que.push(tree[0].word[i]);

        while (not que.empty())
        {
            int now = que.front();
            que.pop();

            for (int i = 0; i < 10; ++i)
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

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("Input.txt", "r", stdin);
    ::freopen("Output.txt", "w", stdout);
#endif

    constexpr const int MOD = 1e9 + 7;

    AhoCorasickAutomaton tree;

    std::string n;
    std::cin >> n;

    int m;
    std::cin >> m;

    std::string s;
    for (int i = 0; i < m; ++i)
    {
        std::cin >> s;
        tree.insert(s);
    }

    tree.build_fail();

    std::vector<std::vector<ullong>> dp(n.size(), std::vector<ullong>(tree.tree.size(), ~0ull));

    std::function<ullong(int, int, bool, bool)> dfs = [&](int pos, int now, bool lead, bool limit) -> ullong
    {
        if (pos == n.size())
            return not tree.tree[now].end;

        if (not lead and not limit and ~dp[pos][now])
            return dp[pos][now];

        ullong sum = 0;

        for (int i = 0, up = (limit ? n[pos] - '0' : 9); i <= up; ++i)
        {
            if (lead and i == 0)
            {
                // The root node always starts from 0,
                // Because the tree contains leading 0
                sum += dfs(pos + 1, 0, 1, limit and i == up) % MOD;
            }
            else
            {
                if (tree.tree[tree.tree[now].word[i]].end)
                    continue;
                else
                    sum += dfs(pos + 1, tree.tree[now].word[i], 0, limit and i == up) % MOD;
            }

            sum %= MOD;
        }

        if (not lead and not limit)
            dp[pos][now] = sum;

        return sum;
    };

    std::cout << dfs(0, 0, true, true) - 1 << '\n';

    return 0;
}