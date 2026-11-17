/**
 * => P3966 [TJOI2013] 单词 ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P3966
 *
 * Submissions ~> https://www.luogu.com.cn/record/152799968 By huanhuanonly
 *
 * @b Failure-link-tree on @b Aho–Corasick-automaton
 *
 * ----March 26, 2024 [19h:01m:30s]----
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
        int word[26];
        int fail;
        int cnt;
    };

    std::vector<node> tree;

    AhoCorasickAutomaton() : tree(1) { }

    int push_node()
    {
        tree.push_back({});
        return tree.size() - 1;
    }

    int insert(const std::string& s)
    {
        int now = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            if (tree[now].word[s[i] - 'a'] == 0)
                tree[now].word[s[i] - 'a'] = push_node();

            now = tree[now].word[s[i] - 'a'];
            ++tree[now].cnt;
        }

        return now;
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
                    que.push(tree[now].word[i]);
                    tree[tree[now].word[i]].fail = tree[tree[now].fail].word[i];
                }
                else
                {
                    tree[now].word[i] = tree[tree[now].fail].word[i];
                }
            }
        }
    }

    std::vector<int> query()
    {
        std::vector<std::vector<int>> e(tree.size() + 1);

        for (int i = 1; i < tree.size(); ++i)
            e[tree[i].fail].push_back(i);

        std::vector<int> cnts(tree.size() + 1);

        std::function<void(int)> dfs = [&](int now) -> void
        {
            cnts[now] = tree[now].cnt;

            for (const auto& i : e[now])
            {
                dfs(i);
                cnts[now] += cnts[i];
            }
        };

        dfs(0);

        return cnts;
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

    int n;
    std::cin >> n;

    AhoCorasickAutomaton tree;

    std::string s;

    std::vector<int> v(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> s;

        v[i] = tree.insert(s);
    }

    tree.build_fail();

    auto cnts = tree.query();

    for (int i = 0; i < n; ++i)
    {
        std::cout << cnts[v[i]] << '\n';
    }

    return 0;
}