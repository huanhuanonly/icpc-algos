/**
 * => P3041 [USACO12JAN] Video Game G ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P3041
 *
 * Submissions ~> https://www.luogu.com.cn/record/150647579 By huanhuanonly
 *
 * @b Automaton-DP on @b Aho-Corasick-automaton
 *
 * ----March 13, 2024 [16h:07m:00s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class AhoCorasickAutomaton
{
public:

    AhoCorasickAutomaton() : tree(1) { }

    struct node
    {
        int word[3];
        int fail;
        int end;
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
            int c = s[i] - 'A';

            if (tree[now].word[c] == 0)
                tree[now].word[c] = push_node();

            now = tree[now].word[c];
        }

        ++tree[now].end;
    }

    void build_fail()
    {
        std::queue<int> que;

        for (int i = 0; i < 3; ++i)
            if (tree[0].word[i])
                que.push(tree[0].word[i]);

        while (not que.empty())
        {
            int now = que.front();
            que.pop();

            for (int i = 0; i < 3; ++i)
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
            tree[now].end += tree[tree[now].fail].end;
        }
    }

    int query(int len)
    {
        std::vector<std::vector<int>> dp(len + 1, std::vector<int>(tree.size(), INT_MIN));

        for (int i = 0; i <= len; ++i)
            dp[i][0] = 0;

        for (int i = 1; i <= len; ++i)
            for (int j = 0; j < tree.size(); ++j)
                for (int k = 0; k < 3; ++k)
                    dp[i][tree[j].word[k]] = std::max(dp[i][tree[j].word[k]], dp[i - 1][j] + tree[tree[j].word[k]].end);

        int ans = 0;

        for (int i = 0; i < tree.size(); ++i)
            ans = std::max(ans, dp[len][i]);

        return ans;
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

    int n, k;
    std::cin >> n >> k;

    std::string s;

    AhoCorasickAutomaton tree;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> s;

        tree.insert(s);
    }

    tree.build_fail();

    std::cout << tree.query(k) << '\n';

    return 0;
}