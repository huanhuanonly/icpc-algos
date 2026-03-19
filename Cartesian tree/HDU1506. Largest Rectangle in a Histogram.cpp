/**
 * University of Ulm Local Contest 2003
 * 
 * => Largest Rectangle in a Histogram
 * 
 * -> https://acm.hdu.edu.cn/showproblem.php?pid=1506
 * 
 * Submissions ~> https://acm.hdu.edu.cn/viewcode.php?rid=40784830 By huanhuanonly
 * 
 * @b Cartesian-tree ( @b Monotonic-stack )
 * 
 * ----March 18, 2026 [01h:07m:19s]----
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

#if defined(__SIZEOF_INT128__)
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;

#if defined(__SIZEOF_FLOAT80__)
using real80 = __float80;
#endif

#if defined(__SIZEOF_FLOAT128__)
using real128 = __float128;
#endif

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif
    
    for (int n; std::cin >> n and n; )
    {
        std::vector<int> v(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> v[i];
        }

        struct node
        {
            int ls, rs;
        };

        std::vector<node> tree(n + 1);

        std::stack<int> st;
        st.push(0);

        for (int u = 1; u <= n; ++u)
        {
            for (; v[u] < v[st.top()]; st.pop());

            tree[u].ls = std::exchange(tree[st.top()].rs, u);
            st.push(u);
        }

        uint64 ans = 0;

        auto dfs = [&](const auto& self, int u, bool first = true) -> int
        {
            if (u == 0 and not first)
            {
                return 0;
            }

            const uint64 cnt = self(self, tree[u].ls, false) + self(self, tree[u].rs, false) + 1;
            
            ans = std::max(ans, cnt * v[u]);
            return cnt;
        };

        dfs(dfs, 0);

        std::cout << ans << '\n';
    }

    return 0;
}