/**
 * Educational DP Contest
 *
 * => F - LCS ( @c 100 )
 *
 * -> https://atcoder.jp/contests/dp/tasks/dp_f
 *
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/51019023 By huanhuanonly
 *
 * @b DP for @a longest-common-subsequence
 *
 * ----April 15, 2025 [21h:35m:57s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("Input.txt", "r", stdin);
    ::freopen("Output.txt", "w", stdout);
#endif

	std::string a, b;
	std::cin >> a >> b;

	a.insert(a.begin(), '~');
	b.insert(b.begin(), '!');

	std::vector<std::vector<int>> dp(a.size(), std::vector<int>(b.size()));

	for (int i = 1; i < a.size(); ++i)
	{
		for (int j = 1; j < b.size(); ++j)
		{
			if (a[i] == b[j])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
		}
	}

	std::string ans;
	ans.reserve(dp.back().back());

	std::function<bool(int, int)> dfs = [&](int x, int y) -> bool
	{
		if (x == 0 or y == 0)
		{
			return ans.size() == dp.back().back();
		}

		if (a[x] == b[y])
		{
			ans.push_back(a[x]);
			if (dfs(x - 1, y - 1))
				return true;
			ans.pop_back();
		}
		else if (dp[x - 1][y] > dp[x][y - 1])
		{
			if (dfs(x - 1, y))
				return true;
		}
		else if (dp[x - 1][y] < dp[x][y - 1])
		{
			if (dfs(x, y - 1))
				return true;
		}
		else
		{
			if (dfs(x - 1, y) or dfs(x, y - 1))
				return true;
		}

		return false;
	};

	dfs(a.size() - 1, b.size() - 1);

	std::reverse(ans.begin(), ans.end());
	std::cout << ans << '\n';

    return 0;
}