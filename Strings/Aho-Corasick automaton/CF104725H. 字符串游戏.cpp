/**
 * 2023年中国大学生程序设计竞赛女生专场
 *
 * => H. 字符串游戏
 *
 * -> https://codeforces.com/gym/104725/problem/H
 *
 * Submissions ~> https://codeforces.com/gym/104725/submission/263002890 By huanhuanonly
 *
 * @b Aho-Corasick-automaton
 *
 * ----May 28, 2024 [19h:33m:21s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

constexpr int MOD = 1e9 + 7;

class acam
{
public:

    struct node
    {
        int word[26];
        int fail;
        int end;
        int has;
    };

    std::vector<node> tree;

    acam() : tree(1) { }

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
            int c = s[i] - 'a';

            if (tree[now].word[c] == 0)
                tree[now].word[c] = push_node();

            now = tree[now].word[c];
        }

        tree[now].end = s.size();
        tree[now].has = true;
    }

    void build_fail()
    {
        std::queue<int> que;

        for (int i = 0; i < 26; ++i)
            if (tree[0].word[i])
                que.push(tree[0].word[i]);

        while (not que.empty())
        {
            int now = que.front();
            que.pop();

            for (int i = 0; i < 26; ++i)
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

            tree[now].has |= tree[tree[now].fail].has;
        }
    }

    ullong get_ans(const std::string& s)
    {
        ullong ans = 0;

        int now = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            now = tree[now].word[s[i] - 'a'];

            if (tree[now].has)
            {
                for (int u = now; tree[u].has; u = tree[u].fail)
                {
                    if (tree[u].end)
                    {
                        ans += ((i - tree[u].end + 1 + 1) * (s.size() - i)) % MOD;
                        ans %= MOD;
                    }
                }
            }
        }

        return ans % MOD;
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m;
    std::cin >> n >> m;

    acam tree;

    std::string s;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> s;
        tree.insert(s);
    }

    tree.build_fail();

    for (int i = 0; i < m; ++i)
    {
        std::cin >> s;
        std::cout << tree.get_ans(s) << '\n';
    }

    return 0;
}