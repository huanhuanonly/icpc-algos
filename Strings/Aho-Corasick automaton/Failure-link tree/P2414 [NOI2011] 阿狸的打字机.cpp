/**
 * => P2414 [NOI2011] 阿狸的打字机 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P2414
 *
 * Submissions ~> https://www.luogu.com.cn/record/152789922 By huanhuanonly
 *
 * @b Failure-link-tree on @b Aho–Corasick-automaton
 * @b Binary-indexed-tree
 *
 * ----March 26, 2024 [17h:50m:16s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class BinaryIndexedTree
{
public:

    std::vector<int> tree;

    explicit BinaryIndexedTree(int n) : tree(n) { }

    static constexpr int lowbit(int p) { return p & -p; }

    void update(int p, int value)
    {
        while (p < tree.size())
        {
            tree[p] += value;
            p += lowbit(p);
        }
    }

    int query(int p)
    {
        int sum = 0;

        while (p > 0)
        {
            sum += tree[p];
            p -= lowbit(p);
        }

        return sum;
    }
};

class AhoCorasickAutomaton
{
public:

    struct node
    {
        int word[26];

        int parent;
        int fail;
    };

    std::vector<node> tree;

    AhoCorasickAutomaton() : tree(1) { }

    int push_node()
    {
        tree.push_back({});
        return tree.size() - 1;
    }

    std::vector<int> insert(const std::string& s)
    {
        int now = 0;

        std::vector<int> nums(1);

        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == 'B')
            {
                now = tree[now].parent;
            }
            else if (s[i] == 'P')
            {
                nums.push_back(now);
            }
            else
            {
                if (tree[now].word[s[i] - 'a'] == 0)
                    tree[now].word[s[i] - 'a'] = push_node();

                tree[tree[now].word[s[i] - 'a']].parent = now;
                now = tree[now].word[s[i] - 'a'];
            }
        }

        return nums;
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

    struct Ans
    {
        int x, y, i, ans;
    };

    void query(const std::string& s, std::vector<Ans>& log)
    {
        auto nums = insert(s);
        int pos = 0;

        build_fail();

        // Build Fail-tree (Reverse Fail-pointer)
        std::vector<std::vector<int>> e(tree.size() + 1);

        for (int i = 1; i < tree.size(); ++i)
            e[tree[i].fail].push_back(i);


        // Get the dfs-order
        std::vector<int> l(tree.size() + 1), r(tree.size() + 1);

        std::function<void(int)> dfs = [&, num = 0](int now) mutable -> void
        {
            l[now] = ++num;

            for (const auto& i : e[now])
            {
                dfs(i);
            }

            r[now] = ++num;
        };

        dfs(0);


        BinaryIndexedTree bit(tree.size() * 2 + 1);

        int now = 0;
        int num = 1;

        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == 'B')
            {
                bit.update(l[now], -1);

                now = tree[now].parent;
            }
            else if (s[i] == 'P')
            {
                for (; pos < log.size() and log[pos].y == num; ++pos)
                {
                    log[pos].ans = bit.query(r[nums[log[pos].x]]) - bit.query(l[nums[log[pos].x]] - 1);
                }
                ++num;
            }
            else
            {
                now = tree[now].word[s[i] - 'a'];

                bit.update(l[now], 1);
            }
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

    std::string s;
    std::cin >> s;

    std::vector<AhoCorasickAutomaton::Ans> log;

    int q;
    std::cin >> q;

    for (int i = 0; i < q; ++i)
    {
        int x, y;
        std::cin >> x >> y;

        log.emplace_back(x, y, i, 0);
    }

    std::sort(log.begin(), log.end(), [](const auto& lv, const auto& rv) -> bool
        {
            return lv.y < rv.y;
        });

    AhoCorasickAutomaton tree;

    tree.query(s, log);

    std::sort(log.begin(), log.end(), [](const auto& lv, const auto& rv) -> bool
        {
            return lv.i < rv.i;
        });

    for (int i = 0; i < q; ++i)
        std::cout << log[i].ans << '\n';

    return 0;
}