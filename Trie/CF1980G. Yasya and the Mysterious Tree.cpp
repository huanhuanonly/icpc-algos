/**
 * Codeforces Round 950 (Div. 3)
 *
 * => G. Yasya and the Mysterious Tree ( @c 2300 )
 *
 * -> https://codeforces.com/contest/1980/problem/G
 *
 * Submissions ~> https://codeforces.com/contest/1980/submission/264225730 By huanhuanonly
 *
 * @b Binary-trie ( @a find-maximum-xor-sum-problems )
 *
 * ----June 05, 2024 [16h:13m:08s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class Trie
{
public:
    struct node
    {
        int word[2];
        int count;
    };

    std::vector<node> tree;

    Trie() : tree(1) { }

    int apply_node()
    {
        tree.push_back({});
        return tree.size() - 1;
    }

    void insert(int value)
    {
        int now = 0;
        ++tree[now].count;

        for (int i = (1 << 30); i > 0; i >>= 1)
        {
            int c = !!(value & i);

            if (tree[now].word[c] == 0)
                tree[now].word[c] = apply_node();

            now = tree[now].word[c];
            ++tree[now].count;
        }
    }

    void erase(int value)
    {
        int now = 0;
        --tree[now].count;

        for (int i = (1 << 30); i > 0; i >>= 1)
        {
            int c = !!(value & i);

            now = tree[now].word[c];
            --tree[now].count;
        }
    }

    int max_xor_sum(int value)
    {
        int now = 0;
        int res = 0;

        if (tree[now].count == 0)
            return res;

        for (int i = (1 << 30); i > 0; i >>= 1)
        {
            int c = !(value & i);

            if (tree[now].word[c] == 0 or tree[tree[now].word[c]].count == 0)
            {
                c = !c;
                res = (res << 1);
            }
            else
            {
                res = ((res | 1) << 1);
            }

            now = tree[now].word[c];
        }

        return res >> 1;
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, m;
        std::cin >> n >> m;

        struct edge
        {
            int to, w;
        };

        std::vector<std::vector<edge>> e(n + 1);

        for (int i = 1; i <= n - 1; ++i)
        {
            int u, v, w;
            std::cin >> u >> v >> w;

            e[u].push_back({v, w});
            e[v].push_back({u, w});
        }

        std::vector<Trie> trie(2);

        struct node
        {
            int depth;
            int xorsum;
        };

        std::vector<node> tree(n + 1);

        std::function<void(int, int)> dfs = [&](int u, int fa) -> void
        {
            trie[tree[u].depth & 1].insert(tree[u].xorsum);

            for (const auto& i : e[u])
            {
                if (i.to != fa)
                {
                    tree[i.to].xorsum = tree[u].xorsum ^ i.w;
                    tree[i.to].depth = tree[u].depth + 1;

                    dfs(i.to, u);
                }
            }
        };

        dfs(1, 1);

        char opt;
        int y, u, x;

        int sum = 0;

        while (m--)
        {
            std::cin >> opt;

            if (opt == '^')
            {
                std::cin >> y;
                sum ^= y;
            }
            else
            {
                std::cin >> u >> x;

                trie[tree[u].depth & 1].erase(tree[u].xorsum);

                std::cout <<
                    std::max(
                        trie[0].max_xor_sum(tree[u].xorsum ^ x ^ (tree[u].depth & 1 ? sum : 0)),
                        trie[1].max_xor_sum(tree[u].xorsum ^ x ^ sum ^ (tree[u].depth & 1 ? sum : 0))
                    );

                trie[tree[u].depth & 1].insert(tree[u].xorsum);

                std::cout.put(' ');
            }
        }

        std::cout.put('\n');
    }

    return 0;
}