# [Unofficial Mirror] 2026 CCPC National Invitational (Nanchang) and The 3rd Jiangxi Provincial Programming Contest
#
# => I. 灯带
#
# -> https://codeforces.com/gym/106554/problem/I
#
# Submissions ~> https://codeforces.com/gym/106554/submission/379239885 By huanhuanonly
#
# @b Constructive and @b Greedy
#
# ----June 17, 2026 [20h:20m:02s]----

for _ in range(int(input())):
    n, m, cr, cg, cb = map(int, input().split())

    v = []

    for i in range(m):
        l, r = map(int, input().split())
        v.append((r - l + 1, l - 1, r - 1))

    v.sort()

    que = [[cr, 'R'], [cg, 'G'], [cb, 'B']]

    ans = [' '] * n

    yes = True

    for size, l, r in v:
        que.sort()

        if que[0][0] >= size:

            que[0][0] -= size

            for i in range(l, r + 1):
                ans[i] = que[0][1]

        elif que[0][0] + que[1][0] >= size:

            for i in range(l, l + que[0][0]):
                ans[i] = que[0][1]

            for i in range(l + que[0][0], r + 1):
                ans[i] = que[1][1]

            que[1][0] -= size - que[0][0]
            que[0][0] = 0

        elif que[1][0] + que[2][0] >= size:

            for i in range(l, l + que[1][0]):
                ans[i] = que[1][1]

            for i in range(l + que[1][0], r + 1):
                ans[i] = que[2][1]

            que[2][0] -= size - que[1][0]
            que[1][0] = 0

        else:

            yes = False
            break


    if yes:

        for i in range(n):
            if ans[i] == ' ':
                if que[0][0]:
                    que[0][0] -= 1
                    ans[i] = que[0][1]
                elif que[1][0]:
                    que[1][0] -= 1
                    ans[i] = que[1][1]
                else:
                    que[2][0] -= 1
                    ans[i] = que[2][1]

        print(''.join(ans))

    else:
        print('-1')