/**
 * Educational Codeforces Round 16
 *
 * => F. String Set Queries ( @c 2400 )
 *
 * -> https://codeforces.com/contest/710/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/710/submission/228788043 By huanhuanonly
 *
 * @b Aho–Corasick-automaton with @b Logarithmic-decomposition
 *
 * ----October 19, 2023 [19h:28m:30s]----
*/

#include <bits/stdc++.h>

using uint = unsigned;
using llong = long long;
using ullong = unsigned long long;


class acam
{
public:
    struct node
    {
        int word[26];
        int sonptr[26];

        int fail;
        int end;
        int cnt;
    };

    std::vector<node> v;

    std::vector<int> root;
    std::vector<int> size;

    explicit acam() : v(1, node()) { }

    inline std::size_t add_node()
    {
        v.push_back(node());
        return v.size() - 1;
    }

    inline int toindex(int c) { return c - 'a'; }

    int merge(int x, int y)
    {
        if (not x or not y) return x + y;

        v[x].end += v[y].end;

        for (int i = 0; i < 26; ++i)
        {
            v[x].sonptr[i] = merge(v[x].sonptr[i], v[y].sonptr[i]);
        }
        return x;
    }

    void build_fail(int cr)
    {
        std::queue<int> que;
        for (int i = 0; i < 26; ++i)
        {
            if (v[cr].sonptr[i])
            {
                v[cr].word[i] = v[cr].sonptr[i];

                v[v[cr].word[i]].fail = cr;
                que.push(v[cr].word[i]);
            }
            else
            {
                v[cr].word[i] = cr;
            }
        }

        while (not que.empty())
        {
            int now = que.front();
            que.pop();

            for (int i = 0; i < 26; ++i)
            {
                if (v[now].sonptr[i])
                {
                    v[now].word[i] = v[now].sonptr[i];

                    v[v[now].word[i]].fail = v[v[now].fail].word[i];

                    que.push(v[now].word[i]);
                }
                else
                {
                    v[now].word[i] = v[v[now].fail].word[i];
                }
            }
            v[now].cnt = v[now].end + v[v[now].fail].cnt;
        }
    }

    void insert(const std::string& s)
    {
        root.push_back(add_node());
        size.push_back(1);

        int now = root.back();
        for (const char& c : s)
        {
            if (v[now].sonptr[toindex(c)] == 0)
                v[now].sonptr[toindex(c)] = add_node();

            now = v[now].sonptr[toindex(c)];
        }
        v[now].end = 1;

        while (root.size() >= 2 and size[size.size() - 1] == size[size.size() - 2])
        {
            root[root.size() - 2] = merge(root[root.size() - 2], root[root.size() - 1]);
            size[size.size() - 2] += size[size.size() - 1];
            root.pop_back(), size.pop_back();
        }
        build_fail(root.back());
    }

    int count(const std::string& s)
    {
        int sum = 0;

        for (int now : root)
        {
            for (const char& c : s)
            {
                now = v[now].word[toindex(c)];
                sum += v[now].cnt;
            }
        }
        return sum;
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int m;
    std::cin >> m;

    int op;
    std::string s;

    acam trie_add, trie_del;

    for (int i = 0; i < m; ++i)
    {
        std::cin >> op >> s;

        switch (op)
        {
        case 1:
            trie_add.insert(s);
            break;
        case 2:
            trie_del.insert(s);
            break;
        case 3:
            std::cout << trie_add.count(s) - trie_del.count(s) << std::endl;
            break;
        }
    }

    return 0;
}