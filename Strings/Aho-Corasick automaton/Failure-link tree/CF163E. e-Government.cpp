/**
 * VK Cup 2012 Round 2
 *
 * => E. e-Government ( @c 2800 )
 *
 * -> https://codeforces.com/contest/163/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/163/submission/253490440 By huanhuanonly
 *
 * @b Failure-link-tree on @b Aho–Corasick-automaton
 * @b Segment-tree
 *
 * @see https://www.cnblogs.com/forgot-dream/p/17674583.html
 *
 * ----March 27, 2024 [20h:10m:33s]----
*/

/// @warning TLE with C++20; Accepted with C++17.

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class SegmentTree
{
public:

    std::vector<int> tree, lazy;

    explicit SegmentTree(int n) : tree(n << 2), lazy(n << 2) { }

    static constexpr int ls(int p) { return p << 1; }
    static constexpr int rs(int p) { return p << 1 | 1; }

    void push_up(int p)
    {
        tree[p] = tree[ls(p)] + tree[rs(p)];
    }

    void add_lazy(int p, int l, int r, int value)
    {
        lazy[p] += value;
        tree[p] += (r - l + 1) * value;
    }

    void push_down(int p, int l, int r)
    {
        if (lazy[p])
        {
            int mid = l + r >> 1;

            add_lazy(ls(p), l, mid, lazy[p]);
            add_lazy(rs(p), mid + 1, r, lazy[p]);

            lazy[p] = 0;
        }
    }

    void add(int p, int l, int r, int x, int y, int value)
    {
        if (x <= l and r <= y)
        {
            add_lazy(p, l, r, value);
            return;
        }

        push_down(p, l, r);

        int mid = l + r >> 1;

        if (x <= mid)
            add(ls(p), l, mid, x, y, value);
        if (y > mid)
            add(rs(p), mid + 1, r, x, y, value);

        push_up(p);
    }

    int getsum(int p, int l, int r, int x, int y)
    {
        if (x <= l and r <= y)
            return tree[p];

        push_down(p, l, r);

        int mid = l + r >> 1;

        int sum = 0;

        if (x <= mid)
            sum += getsum(ls(p), l, mid, x, y);
        if (y > mid)
            sum += getsum(rs(p), mid + 1, r, x, y);

        return sum;
    }
};

class AhoCorasickAutomaton
{
public:

    struct node
    {
        int word[26];
        int fail;
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

    std::vector<int> in, out;

    void reverse_fail()
    {
        std::vector<std::vector<int>> e(tree.size() + 1);

        for (int i = 1; i < tree.size(); ++i)
        {
            e[tree[i].fail].push_back(i);
        }

        in.resize(tree.size());
        out.resize(tree.size());

        std::function<void(int)> dfs = [&, num = 0](int now) mutable -> void
        {
            in[now] = ++num;

            for (const auto& i : e[now])
            {
                dfs(i);
            }

            out[now] = ++num;
        };

        dfs(0);
    }

    void build_segment_tree(SegmentTree& seg, const std::vector<int>& nums)
    {
        for (int i = 1; i < nums.size(); ++i)
        {
            seg.add(1, 1, tree.size() * 2, in[nums[i]], out[nums[i]], 1);
        }
    }

    int query(const std::string& s, SegmentTree& seg)
    {
        int n = tree.size() * 2;

        int now = 0;
        int sum = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            now = tree[now].word[s[i] - 'a'];

            sum += seg.getsum(1, 1, n, in[now], in[now]);
        }

        return sum;
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

    std::vector<int> nums(k + 1);

    AhoCorasickAutomaton tree;

    std::string s;

    for (int i = 1; i <= k; ++i)
    {
        std::cin >> s;
        nums[i] = tree.insert(s);
    }

    std::vector<bool> vis(k + 1, true);

    tree.build_fail();
    tree.reverse_fail();

    SegmentTree seg(tree.tree.size() * 2);

    tree.build_segment_tree(seg, nums);

    for (int q = 0; q < n; ++q)
    {
        char opt;
        std::cin >> opt;

        if (opt == '+')
        {
            int num;
            std::cin >> num;

            if (vis[num] == false)
            {
                vis[num] = true;
                seg.add(1, 1, tree.tree.size() * 2, tree.in[nums[num]], tree.out[nums[num]], 1);
            }
        }
        else if (opt == '-')
        {
            int num;
            std::cin >> num;

            if (vis[num] == true)
            {
                vis[num] = false;
                seg.add(1, 1, tree.tree.size() * 2, tree.in[nums[num]], tree.out[nums[num]], -1);
            }
        }
        else
        {
            std::cin >> s;

            std::cout << tree.query(s, seg) << '\n';
        }
    }

    return 0;
}