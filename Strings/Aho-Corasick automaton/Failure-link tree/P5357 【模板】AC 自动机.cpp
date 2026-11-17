/**
 * => P5357 【模板】AC 自动机 ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P5357
 *
 * Submissions ~> https://www.luogu.com.cn/record/152740552 By huanhuanonly
 *
 * @b Failure-link-tree on @b Aho–Corasick-automaton
 *
 * ----March 26, 2024 [11h:13m:28s]----
*/

#include <bits/stdc++.h>

using uint = unsigned int;
using llong = long long int;
using ullong = unsigned long long int;
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

    int size = 0;

    int insert(const std::string& s)
    {
        int now = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            int c = s[i] - 'a';

            if (tree[now].word[c] == 0)
                tree[now].word[c] = push_node();

            now = tree[now].word[c];
        }

        ++size;

        return now;
    }

    void build_fail(std::vector<std::vector<int>>& e)
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

        for (int i = 1; i < tree.size(); ++i)
        {
            e[tree[i].fail].push_back(i);
        }
    }

    std::vector<int> query(const std::string& s)
    {
        std::vector<int> cnts(tree.size() + 1);

        std::vector<std::vector<int>> e(tree.size() + 1);
        build_fail(e);

        int now = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            now = tree[now].word[s[i] - 'a'];
            ++tree[now].cnt;
        }

        std::function<int(int)> dfs = [&](int p) -> int
        {
            cnts[p] += tree[p].cnt;

            for (const auto& i : e[p])
            {
                cnts[p] += dfs(i);
            }

            return cnts[p];
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

    std::string s;
    std::vector<int> v(n);

    AhoCorasickAutomaton tree;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> s;

        v[i] = tree.insert(s);
    }

    std::cin >> s;

    auto cnts = tree.query(s);

    for (int i = 0; i < n; ++i)
    {
        std::cout << cnts[v[i]] << '\n';
    }

    return 0;
}