/**
 * Codeforces Round 248 (Div. 1)
 *
 * => C. Tachibana Kanade's Tofu ( @c 2500 )
 *
 * -> https://codeforces.com/contest/434/problem/C
 *
 * Submissions ~> https://codeforces.com/contest/434/submission/252576625 By huanhuanonly
 *
 * @b Automaton-DP on @b Aho-Corasick-automaton
 * @b Digit-DP
 *
 * ----March 21, 2024 [19h:12m:39s]----
*/

#include <bits/stdc++.h>

using uint = unsigned int;
using llong = long long int;
using ullong = unsigned long long int;
using ldouble = long double;

static constexpr const int MOD = 1000000007;

class AhoCorasickAutomaton
{
public:

    struct node
    {
        int word[21];
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

    void insert(const std::vector<int>& s, int value)
    {
        int now = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            if (tree[now].word[s[i]] == 0)
                tree[now].word[s[i]] = push_node();

            now = tree[now].word[s[i]];
        }

        tree[now].end += value;
    }

    void build_fail()
    {
        std::queue<int> que;

        for (int i = 0; i < 21; ++i)
        {
            if (tree[0].word[i])
            {
                que.push(tree[0].word[i]);
            }
        }

        while (not que.empty())
        {
            int now = que.front();
            que.pop();

            for (int i = 0; i < 21; ++i)
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

    ullong query(const std::vector<int>& v, int base, int mx)
    {
        std::vector<std::vector<std::vector<ullong>>> dp(
            v.size(),
                std::vector<std::vector<ullong>>(
                    tree.size(), std::vector<ullong>(500 + 1, ~0ull)
                )
        );

        std::function<ullong(int, int, int, bool, bool)> dfs =
            [&](int pos, int now, int cnt, bool lead, bool limit) -> ullong
        {
            if (pos == v.size())
                return cnt <= mx;

            if (not lead and not limit and ~dp[pos][now][cnt])
                return dp[pos][now][cnt];

            ullong sum = 0;

            for (int i = 0, up = (limit ? v[pos] : base - 1); i <= up; ++i)
            {
                if (lead and i == 0)
                    sum += dfs(pos + 1, 0, 0, true, limit and i == up);
                else
                {
                    if (cnt + tree[tree[now].word[i]].end > mx)
                        continue;

                    sum += dfs(pos + 1, tree[now].word[i], cnt + tree[tree[now].word[i]].end, false, limit and i == up) % MOD;
                    sum %= MOD;
                }
            }

            if (not lead and not limit)
                dp[pos][now][cnt] = sum;

            return sum;
        };

        return dfs(0, 0, 0, true, true);
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

    int n, m, k;
    std::cin >> n >> m >> k;

    int len;
    std::cin >> len;

    std::vector<int> l(len);

    for (int i = 0; i < len; ++i)
        std::cin >> l[i];

    std::cin >> len;

    std::vector<int> r(len);

    for (int i = 0; i < len; ++i)
        std::cin >> r[i];

    AhoCorasickAutomaton tree;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> len;

        std::vector<int> v(len);

        for (int j = 0; j < len; ++j)
            std::cin >> v[j];

        int value;
        std::cin >> value;

        tree.insert(v, value);
    }

    tree.build_fail();

    // --l
    for (int i = l.size() - 1; i >= 0; --i)
    {
        if (l[i] == 0)
            l[i] = m - 1;
        else
        {
            --l[i];
            break;
        }
    }

    if (l.front() == 0 and l.size() > 1)
        l.erase(l.begin());

    std::cout << (tree.query(r, m, k) + MOD - tree.query(l, m, k)) % MOD;

    return 0;
}