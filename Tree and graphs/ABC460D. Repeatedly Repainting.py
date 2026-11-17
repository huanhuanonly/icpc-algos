# AtCoder Beginner Contest 460
#
# => D - Repeatedly Repainting ( @c 425 )
#
# -> https://atcoder.jp/contests/abc460/tasks/abc460_d
#
# Submissions ~> https://atcoder.jp/contests/abc460/submissions/76353256 By huanhuanonly
#
# @b Bfs on @a Graphs
# @b Constructive
#
# ----June 02, 2026 [22h:02m:46s]----

import collections

h, w = map(int, input().split())

mp = [list(input()) for i in range(h)]
d = [(0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)]

def run():
    global mp

    mpt = [['.'] * w for i in range(h)]
    for x in range(h):
        for y in range(w):
            if mp[x][y] == '#':
                for dx, dy in d:
                    if 0 <= x + dx < h and 0 <= y + dy < w and mp[x + dx][y + dy] == '.':
                        mpt[x + dx][y + dy] = '#'
    mp = mpt

run()
run()

vis = [[False] * w for i in range(h)]

que = collections.deque()

for i in range(h):
    for j in range(w):
        if mp[i][j] == '#':
            que.append((i, j))

while que:
    x, y = que.popleft()

    for dx, dy in d:
        if 0 <= x + dx < h and 0 <= y + dy < w and mp[x + dx][y + dy] == '.' and not vis[x + dx][y + dy]:
            vis[x + dx][y + dy] = True
            if mp[x][y] == '.':
                mp[x + dx][y + dy] = '#'
            que.append((x + dx, y + dy))


for i in mp:
    print(*i, sep='')