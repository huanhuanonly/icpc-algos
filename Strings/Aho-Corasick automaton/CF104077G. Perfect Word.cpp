/**
 * The 2022 ICPC Asia Xian Regional Contest
 *
 * => G. Perfect Word
 *
 * -> https://codeforces.com/gym/104077/problem/G
 *
 * Submissions ~> https://codeforces.com/gym/104077/submission/256899984 By huanhuanonly
 *
 * @b Aho-Corasick-automaton
 *
 * ----April 16, 2024 [18h:59m:10s]----
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
        int end;
    };

    std::vector<node> tree;

    AhoCorasickAutomaton() : tree(1) { }

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

        tree[now].end = 1;
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

            tree[now].end += tree[tree[now].fail].end;
        }
    }

    bool check(const std::string& s)
    {
        int now = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            int c = s[i] - 'a';

            now = tree[now].word[c];

            if (tree[now].end <= i)
                return false;
        }

        return true;
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

    std::vector<std::string> v(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i];

        tree.insert(v[i]);
    }

    tree.build_fail();

    std::sort(v.begin(), v.end(), [](const std::string& lv, const std::string& rv) -> bool
    {
        return lv.size() > rv.size();
    });

    int ans = 0;

    for (int i = 0; i < n; ++i)
    {
        if (tree.check(v[i]))
        {
            ans = v[i].size();
            break;
        }
    }

    std::cout << ans;

    return 0;
}