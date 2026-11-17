/**
 * AtCoder Beginner Contest 350
 *
 * => F - Transpose ( @c 550 )
 *
 * -> https://atcoder.jp/contests/abc350/tasks/abc350_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc350/submissions/53236623 By huanhuanonly
 *
 * @b Split-merge-treap
 *
 * ----May 08, 2024 [12h:38m:07s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class Treap
{
public:

    struct node
    {
        int ls, rs;
        int key;
        char value;

        int size;

        bool reversed;
    };

    std::vector<node> tree;
    int root = 0;

    Treap() : tree(1) { }

    int push_node(char value)
    {
        static std::mt19937 rng;

        tree.push_back({0, 0, int(rng()), value, 1});
        return tree.size() - 1;
    }

    static void transform(char& value)
    {
        if (std::islower(value))
            value = std::toupper(value);
        else
            value = std::tolower(value);
    }

    void push_up(int u)
    {
        tree[u].size = tree[tree[u].ls].size + tree[tree[u].rs].size + 1;
    }

    void push_down(int u)
    {
        if (tree[u].reversed)
        {
            tree[u].reversed = false;

            tree[tree[u].ls].reversed ^= 1;
            tree[tree[u].rs].reversed ^= 1;

            std::swap(tree[u].ls, tree[u].rs);
            transform(tree[u].value);
        }
    }

    void split(int u, int k, int& rx, int& ry)
    {
        if (u == 0)
        {
            rx = ry = 0;
            return;
        }

        push_down(u);

        if (tree[tree[u].ls].size >= k)
        {
            ry = u;
            split(tree[u].ls, k, rx, tree[u].ls);
        }
        else if (tree[tree[u].ls].size + 1 == k)
        {
            rx = u;
            ry = tree[u].rs;
            tree[u].rs = 0;
        }
        else
        {
            rx = u;
            split(tree[u].rs, k - tree[tree[u].ls].size - 1, tree[u].rs, ry);
        }

        push_up(u);
    }

    int merge(int u, int v)
    {
        if (u == 0 or v == 0)
            return u + v;

        if (tree[u].key > tree[v].key)
        {
            push_down(u);
            tree[u].rs = merge(tree[u].rs, v);
            push_up(u);
            return u;
        }
        else
        {
            push_down(v);
            tree[v].ls = merge(u, tree[v].ls);
            push_up(v);
            return v;
        }
    }

    void insert(char value)
    {
        root = merge(root, push_node(value));
    }

    void reverse(int k)
    {
        int x, y;
        split(root, k - 1, x, y);

        tree[y].reversed ^= 1;

        root = merge(x, y);
    }

    void inorder(int u, auto func)
    {
        if (u == 0)
            return;

        push_down(u);

        inorder(tree[u].ls, func);

        func(u);

        inorder(tree[u].rs, func);
    }

    std::string str()
    {
        std::string res;

        inorder(root, [&](int u) -> void { res.push_back(tree[u].value); });

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

    std::string s;
    std::cin >> s;

    int pos = 1;

    std::stack<int> st;

    Treap tree;

    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == '(')
        {
            st.push(pos);
        }
        else if (s[i] == ')')
        {
            tree.reverse(st.top());
            st.pop();
        }
        else
        {
            tree.insert(s[i]);
            ++pos;
        }
    }

    std::cout << tree.str();

    return 0;
}