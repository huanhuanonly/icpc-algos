/**
 * Codeforces Round 1102 (Div. 2)
 *
 * => F. Vessels, Heights and Two Versions (Hard Version) ( @c 1900 )
 *
 * -> https://codeforces.com/contest/2234/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/2234/submission/378139228 By huanhuanonly
 *
 * @b Monotonic-stack
 * @b Dfs
 *
 * ----June 11, 2026 [11h:10m:22s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n;
        std::cin >> n;

        std::vector<int> h(n + n);

        std::pair<int, int> maxpos;

        for (int i = 0; i < n; ++i)
        {
            std::cin >> h[i];
            h[i + n] = h[i];
            maxpos = std::max(maxpos, {h[i], i});
        }

        ++h[maxpos.second];
        ++h[maxpos.second + n];

        std::vector<int> prev(n + n), next(n + n);

        std::stack<int> st;

        for (int i = 0; i < n + n; ++i)
        {
            for (; not st.empty() and h[st.top()] < h[i]; st.pop());

            if (not st.empty())
            {
                prev[i] = st.top();
            }
            else
            {
                prev[i] = i;
            }

            st.push(i);
        }

        for (; not st.empty(); st.pop());

        for (int i = n + n - 1; i >= 0; --i)
        {
            for (; not st.empty() and h[st.top()] < h[i]; st.pop());

            if (not st.empty())
            {
                next[i] = st.top();
            }

            st.push(i);
        }

        std::ranges::copy(prev | std::views::drop(n - 1), prev.begin());
        prev.resize(n);
        next.resize(n);
        std::ranges::transform(prev, prev.begin(), [n](int x) -> int { return (x + 1) % n; });
        std::ranges::transform(next, next.begin(), [n](int x) -> int { return x % n; });

        --h[maxpos.second];
        --h[maxpos.second + n];

        std::vector<bool> vis_pre(n), vis_suf(n);
        std::vector<int64> pre(n), suf(n);

        auto dfs_backward = [&](const auto& self, int cpos, auto&& dist) -> void
        {
            if (vis_suf[cpos] or next[cpos] == cpos)
            {
                return;
            }

            vis_suf[cpos] = true;

            self(self, next[cpos], dist);
            suf[cpos] = suf[next[cpos]] + h[cpos] * dist(cpos, next[cpos]);
        };

        auto dfs_forward = [&](const auto& self, int cpos, auto&& dist) -> void
        {
            if (vis_pre[cpos] or prev[cpos] == cpos)
            {
                return;
            }

            vis_pre[cpos] = true;

            self(self, prev[cpos], dist);
            pre[cpos] = pre[prev[cpos]] + h[(cpos + n - 1) % n] * dist(cpos, prev[cpos]);
        };

        for (int i = 0; i < n; ++i)
        {
            dfs_backward(dfs_backward, i, [n](int i, int j) -> int64 { return (j + n - i) % n; });
            dfs_forward(dfs_forward, i, [n](int i, int j) -> int64 { return i < j ? i + (n - j) : i - j; });
        }

        for (int i = 0; i < n; ++i)
        {
            std::cout << pre[i] + suf[i] << " \n"[i + 1 == n];
        }
    }

    return 0;
}