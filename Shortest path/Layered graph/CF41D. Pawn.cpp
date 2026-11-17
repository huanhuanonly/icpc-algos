/**
 * Codeforces Beta Round 40 (Div. 2)
 *
 * => D. Pawn ( @c 1900 )
 *
 * -> https://codeforces.com/contest/41/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/41/submission/270128782 By huanhuanonly
 *
 * @b Bfs based on @b Layered-graph
 *
 * ----July 12, 2024 [14h:36m:48s]----
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
	::freopen("in", "r", stdin);
	::freopen("out", "w", stdout);
#endif

	int n, m, k;
	std::cin >> n >> m >> k;

	++k;

	std::vector<std::string> mp(n + 1);

	for (int i = 1; i <= n; ++i)
		std::cin >> mp[i],
		mp[i].insert(mp[i].begin(), '^');

	constexpr char toed = '/';
	std::vector<std::vector<std::vector<char>>> vis(n + 1, std::vector<std::vector<char>>(m + 1, std::vector<char>(910)));

	auto bfs = [&]() -> void
	{
		struct point
		{
			int x, y;
			int dis;

			bool operator<(const point& you) const
			{
				return this->dis > you.dis;
			}
		};

		std::priority_queue<point> que;

		for (int i = 1; i <= m; ++i)
		{
			que.push({n, i, mp[n][i] - '0'});
			vis[n][i][mp[n][i] - '0'] = toed;
		}

		while (not que.empty())
		{
			auto now = que.top();
			que.pop();

			for (const auto& i : {-1, 1})
			{
				if (int nx = now.x - 1, ny = now.y + i, nd = now.dis + mp[nx][ny] - '0';
				 	nx >= 1 and nx <= n and ny >= 1 and ny <= m and not vis[nx][ny][nd])
				{
					vis[nx][ny][nd] = (i == -1 ? 'L' : 'R');
					que.push({nx, ny, nd});
				}
			}
		}
	};

	bfs();

	int mx = -1;
	int col = 0;

	for (int i = 1; i <= m; ++i)
	{
		for (int lay = static_cast<int>(vis[1][i].size()); lay >= 0; --lay)
		{
			if (lay % k == 0 and vis[1][i][lay] and lay > mx)
			{
				mx = lay;
				col = i;
				break;
			}
		}
	}

	if (mx == -1)
	{
		std::cout << -1;
	}
	else
	{
		std::cout << mx << '\n';

		std::string ans;

		int x = 1, y = col, dis = mx;

		for (; x < n; ++x)
		{
			ans.push_back(vis[x][y][dis]);

			if (vis[x][y][dis] == 'L')
			{
				dis -= mp[x][y] - '0';
				++y;
			}
			else
			{
				dis -= mp[x][y] - '0';
				--y;
			}
		}

		std::cout << y << '\n';

		std::reverse(ans.begin(), ans.end());

		std::cout << ans << '\n';
	}

	return 0;
}