/**
 * Educational Codeforces Round 70 (Rated for Div. 2)
 *
 * => E. You Are Given Some Strings... ( @c 2400 )
 *
 * -> https://codeforces.com/contest/1202/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/1202/submission/255563686 By huanhuanonly
 *
 * @b Aho–Corasick-automaton
 *
 * ----April 08, 2024 [11h:09m:54s]----
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

    template<typename Iterator>
    void insert(Iterator first, Iterator last)
    {
        int now = 0;

        for (; first != last; ++first)
        {
            int c = *first - 'a';

            if (tree[now].word[c] == 0)
                tree[now].word[c] = push_node();

            now = tree[now].word[c];
        }

        ++tree[now].cnt;
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

            tree[now].cnt += tree[tree[now].fail].cnt;
        }
    }

    void clear()
    {
        tree.clear();
        tree.push_back({});
    }

    void count(const std::string& s, std::vector<int>& res)
    {
        for (int i = 0, now = 0; i < s.size(); ++i)
        {
            now = tree[now].word[s[i] - 'a'];
            res[i] = tree[now].cnt;
        }
    }

    void rcount(const std::string& s, std::vector<int>& res)
    {
        for (int i = s.size() - 1, now = 0; i >= 0; --i)
        {
            now = tree[now].word[s[i] - 'a'];
            res[i] = tree[now].cnt;
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

    std::string t;
    std::cin >> t;

    std::vector<int> pre(t.size()), suf(t.size());

    int n;
    std::cin >> n;

    AhoCorasickAutomaton tree;

    std::vector<std::string> s(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> s[i];
        tree.insert(s[i].begin(), s[i].end());
    }

    tree.build_fail();
    tree.count(t, pre);

    tree.clear();

    for (int i = 0; i < n; ++i)
    {
        tree.insert(s[i].rbegin(), s[i].rend());
    }

    tree.build_fail();
    tree.rcount(t, suf);

    ullong sum = 0;

    for (int i = 0; i < t.size() - 1; ++i)
    {
        sum += ullong(pre[i]) * suf[i + 1];
    }

    std::cout << sum;

    return 0;
}