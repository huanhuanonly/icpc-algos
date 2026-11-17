/**
 * Educational Codeforces Round 97 (Rated for Div. 2)
 *
 * => G. Death DBMS ( @c 2600 )
 *
 * -> https://codeforces.com/contest/1437/problem/G
 *
 * Submissions ~> https://codeforces.com/contest/1437/submission/253928821 By huanhuanonly
 *
 * @b Failure-link-tree on @b Aho–Corasick-automaton
 * @b Heavy-Light-decomposition
 * @b Segment-tree
 *
 * @note The root node of Aho-Corasick Automaton starts from 1
 *
 * ----March 29, 2024 [18h:44m:51s]----
*/

#include <bits/stdc++.h>

using uint = unsigned int;
using llong = long long int;
using ullong = unsigned long long int;
using ldouble = long double;

class SegmentTree
{
public:

    std::vector<int> tree, lazy;

    explicit SegmentTree(int n) : tree(n << 2, -1), lazy(n << 2, -1) { }

    static constexpr int ls(int p) { return p << 1; }
    static constexpr int rs(int p) { return p << 1 | 1; }

    void push_up(int p)
    {
        tree[p] = std::max(tree[ls(p)], tree[rs(p)]);
    }

    void add_lazy(int p, int l, int r, int value)
    {
        lazy[p] = value;
        tree[p] = value;
    }

    void push_down(int p, int l, int r)
    {
        if (lazy[p] != -1)
        {
            int mid = l + r >> 1;

            add_lazy(ls(p), l, mid, lazy[p]);
            add_lazy(rs(p), mid + 1, r, lazy[p]);

            lazy[p] = -1;
        }
    }

    void update(int p, int l, int r, int x, int y, int value)
    {
        if (x <= l and r <= y)
        {
            add_lazy(p, l, r, value);
            return;
        }

        push_down(p, l, r);

        int mid = l + r >> 1;

        if (x <= mid)
            update(ls(p), l, mid, x, y, value);
        if (y > mid)
            update(rs(p), mid + 1, r, x, y, value);

        push_up(p);
    }

    int getmax(int p, int l, int r, int x, int y)
    {
        if (x <= l and r <= y)
            return tree[p];

        push_down(p, l, r);

        int mid = l + r >> 1;

        int res = -1;

        if (x <= mid)
            res = std::max(res, getmax(ls(p), l, mid, x, y));
        if (y > mid)
            res = std::max(res, getmax(rs(p), mid + 1, r, x, y));

        return res;
    }
};

class AhoCorasickAutomaton
{
public:

    struct node
    {
        int word[26];
        int fail;

        node()
        {
            std::fill(std::begin(word), std::end(word), 1);
            fail = 1;
        }
    };

    std::vector<node> tree;

    AhoCorasickAutomaton() : tree(2) { }

    int push_node()
    {
        tree.push_back({});
        return tree.size() - 1;
    }

    int insert(const std::string& s)
    {
        int now = 1;

        for (int i = 0; i < s.size(); ++i)
        {
            if (tree[now].word[s[i] - 'a'] == 1)
                tree[now].word[s[i] - 'a'] = push_node();

            now = tree[now].word[s[i] - 'a'];
        }

        return now;
    }

    void build_fail()
    {
        std::queue<int> que;

        for (int i = 0; i < 26; ++i)
            if (tree[1].word[i] != 1)
                que.push(tree[1].word[i]);


        while (not que.empty())
        {
            int now = que.front();
            que.pop();

            for (int i = 0; i < 26; ++i)
            {
                if (tree[now].word[i] != 1)
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

    struct Link
    {
        int depth, top, wson, fa, size;
    };

    std::vector<Link> link;

    void build_tree(SegmentTree& seg, const std::vector<int>& nums)
    {
        in.resize(tree.size());
        out.resize(tree.size());

        link.resize(tree.size());

        std::vector<std::vector<int>> e(tree.size() + 1);

        for (int i = 2; i < tree.size(); ++i)
            e[tree[i].fail].push_back(i);

        std::function<void(int)> dfs = [&](int now) -> void
        {
            link[now].depth = link[link[now].fa].depth + 1;
            link[now].size = 1;

            for (const auto& i : e[now])
            {
                link[i].fa = now;

                dfs(i);

                link[now].size += link[i].size;

                if (link[i].size > link[link[now].wson].size)
                    link[now].wson = i;
            }
        };

        std::function<void(int, int)> dfs2 = [&, num = 0](int now, int head) mutable -> void
        {
            in[now] = ++num;

            link[now].top = head;

            if (link[now].wson)
                dfs2(link[now].wson, head);

            for (const auto& i : e[now])
            {
                if (i == link[now].wson)
                    continue;

                dfs2(i, i);
            }

            out[now] = num;
        };

        dfs(1);
        dfs2(1, 1);

        for (int i = 0; i < nums.size(); ++i)
        {
            seg.update(1, 1, tree.size(), in[nums[i]], out[nums[i]], 0);
        }
    }

    void update(SegmentTree& seg, int now, int value)
    {
        seg.update(1, 1, tree.size(), in[now], in[now], value);
    }

    int getmax(SegmentTree& seg, int now)
    {
        int res = -1;

        while (link[now].top)
        {
            res = std::max(res, seg.getmax(1, 1, tree.size(), in[link[now].top], in[now]));
            now = link[link[now].top].fa;
        }

        return res;
    }

    int query(const std::string& s, SegmentTree& seg)
    {
        int now = 1;
        int res = -1;

        for (int i = 0; i < s.size(); ++i)
        {
            now = tree[now].word[s[i] - 'a'];

            res = std::max(res, getmax(seg, now));
        }

        return res;
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

    int n, m;
    std::cin >> n >> m;

    std::string s;

    std::vector<int> nums(n);

    // now, max
    std::map<int, std::multiset<int, std::greater<int>>> mp;
    std::vector<int> log(n);

    AhoCorasickAutomaton tree;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> s;

        nums[i] = tree.insert(s);
        mp[nums[i]].insert(0);
    }

    tree.build_fail();

    SegmentTree seg(tree.tree.size());
    tree.build_tree(seg, nums);


    int opt;

    int pos, x;

    while (m--)
    {
        std::cin >> opt;

        if (opt == 1)
        {
            std::cin >> pos >> x;

            --pos;

            auto it = mp.find(nums[pos]);

            auto node = it->second.extract(log[pos]);
            node.value() = x;
            log[pos] = x;
            it->second.insert(std::move(node));

            tree.update(seg, nums[pos], *it->second.begin());
        }
        else
        {
            std::cin >> s;
            std::cout << tree.query(s, seg) << '\n';
        }
    }

    return 0;
}