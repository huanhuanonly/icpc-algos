/**
 * 牛客周赛 Round 103
 * 
 * => F-快乐 ( @c 2400 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/114593/F
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=78619394 By huanhuanonly
 * 
 * @b AhoCorasick-Automaton
 * 
 * ----August 03, 2025 [20h:47m:12s]----
*/

#include <bits/stdc++.h>

using int8 = signed char;
using int16 = short;
using int32 = int;
using int64 = long long;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

#ifdef __GNUC__
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;
using real128 = long double;

inline namespace huanhuanonly
{
class AhoCorasickAutomaton
{
public:

    struct node
    {
        int word[26];
        int fail;
        uint64 cnt;
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
            ++tree[now].cnt;
        }
    }

    void build_fail()
    {
        std::queue<int> que;

        for (int i = 0; i < 26; ++i)
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

            for (int i = 0; i < 26; ++i)
            {
                if (tree[now].word[i])
                {
                    que.push(tree[now].word[i]);
                    tree[tree[now].word[i]].fail = tree[tree[now].fail].word[i];

                    tree[tree[now].word[i]].cnt += tree[now].cnt;
                }
                else
                {
                    tree[now].word[i] = tree[tree[now].fail].word[i];
                }
            }

            tree[now].cnt = std::max(tree[now].cnt, tree[tree[now].fail].cnt);
        }
    }

    void clear()
    {
        tree.clear();
        tree.push_back({});
    }

    uint64 max_count(const std::string& s)
    {
        uint64 cnt = 0;

        for (int i = 0, now = 0; i < s.size(); ++i)
        {
            now = tree[now].word[s[i] - 'a'];
            cnt = std::max(cnt, tree[now].cnt);
        }

        return cnt;
    }
};
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, m;
        std::cin >> n >> m;

        std::string s;
        std::cin >> s;

        AhoCorasickAutomaton ac;

        std::string t;
        
        for (int i = 0; i < m; ++i)
        {
            std::cin >> t;
            ac.insert(t.begin(), t.end());
        }

        ac.build_fail();

        std::cout << ac.max_count(s) << '\n';
    }

    return 0;
}