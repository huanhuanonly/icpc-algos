/**
 * Codeforces Round 305 (Div. 1)
 *
 * => E. Mike and Friends ( @c 2800 )
 *
 * -> https://codeforces.com/contest/547/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/547/submission/255208216 By huanhuanonly
 *
 * @b Failure-link-tree on @b Aho–Corasick-automaton
 * @b Heavy-Light-decomposition
 * @b Segment-tree
 *
 * ----April 06, 2024 [16h:20m:04s]----
*/

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

    int query(int p, int l, int r, int x, int y)
    {
        if (x <= l and r <= y)
            return tree[p];

        push_down(p, l, r);

        int mid = l + r >> 1;
        int sum = 0;

        if (x <= mid)
            sum += query(ls(p), l, mid, x, y);
        if (y > mid)
            sum += query(rs(p), mid + 1, r, x, y);

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

    void build_tree(const std::vector<int>& nums)
    {
        in.resize(tree.size());
        out.resize(tree.size());

        std::vector<std::vector<int>> e(tree.size() + 1);

        for (int i = 1; i < tree.size(); ++i)
            e[tree[i].fail].push_back(i);

        std::function<void(int)> dfs = [&, num = 0](int now) mutable -> void
        {
            in[now] = ++num;

            for (const auto& i : e[now])
            {
                dfs(i);
            }

            out[now] = num;
        };

        dfs(0);
    }

    void insert(const std::string& s, SegmentTree& seg)
    {
        int now = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            now = tree[now].word[s[i] - 'a'];
            seg.update(1, 1, tree.size(), in[now], in[now], 1);
        }
    }

    int count(int now, SegmentTree& seg)
    {
        return seg.query(1, 1, tree.size(), in[now], out[now]);
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

    int n, q;
    std::cin >> n >> q;

    std::vector<int> nums(n);

    std::vector<std::string> s(n);

    AhoCorasickAutomaton tree;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> s[i];

        nums[i] = tree.insert(s[i]);
    }

    SegmentTree seg(tree.tree.size());

    tree.build_fail();
    tree.build_tree(nums);

    struct node
    {
        int p, k, i, ans;
    };

    std::vector<node> v;
    v.reserve(q << 1);

    for (int i = 0; i < q; ++i)
    {
        int l, r, k;
        std::cin >> l >> r >> k;

        --l, --r, --k;

        v.push_back({l - 1, k, i << 1, 0});
        v.push_back({r, k, i << 1 | 1, 0});
    }

    std::sort(v.begin(), v.end(), [](const node& lv, const node& rv) -> bool
    {
        return lv.p < rv.p;
    });

    int pos = std::find_if(v.begin(), v.end(), [](const node& nd) -> bool { return nd.p >= 0; }) - v.begin();

    for (int i = 0; i < n; ++i)
    {
        tree.insert(s[i], seg);

        while (pos < v.size() and v[pos].p == i)
        {
            v[pos].ans = tree.count(nums[v[pos].k], seg);

            ++pos;
        }
    }

    std::sort(v.begin(), v.end(), [](const node& lv, const node& rv) -> bool
    {
        return lv.i < rv.i;
    });

    for (int i = 0; i < v.size(); i += 2)
    {
        std::cout << v[i + 1].ans - v[i].ans << '\n';
    }

    return 0;
}