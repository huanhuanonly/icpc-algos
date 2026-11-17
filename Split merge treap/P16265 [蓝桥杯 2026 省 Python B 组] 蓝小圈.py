# 蓝桥杯省赛自测（Python B 组）
#
# => P16265 [蓝桥杯 2026 省 Python B 组] 蓝小圈 ( @c 普及+/提高 )
#
# -> https://www.luogu.com.cn/problem/P16265
#
# Submissions ~> https://www.luogu.com.cn/record/273817779 By huanhuanonly
#
# @b Split-merge-treap ( @a with-lazy-propagation | @a dynamic-connectivity )
#
# ----April 13, 2026 [09h:32m:57s]----

import random
import sys

class Treap:
    class node:
        def __init__(self):
            self.ls = 0
            self.rs = 0
            self.fa = 0
            self.key = random.randint(0, 10 ** 9)
            self.value = 0
            self.lazy = 0

    def __init__(self, n):
        self.tree = [self.node() for i in range(n)]

    def push_down(self, u):
        if self.tree[u].lazy != 0:
            if self.tree[u].ls != 0:
                self.tree[self.tree[u].ls].value += self.tree[u].lazy
                self.tree[self.tree[u].ls].lazy += self.tree[u].lazy
            if self.tree[u].rs != 0:
                self.tree[self.tree[u].rs].value += self.tree[u].lazy
                self.tree[self.tree[u].rs].lazy += self.tree[u].lazy
            self.tree[u].lazy = 0


    def find(self, x):
        c = x
        que = [c]

        while self.tree[c].fa != 0:
            c = self.tree[c].fa
            que.append(c)

        for i in reversed(que):
            self.push_down(i)

        return c

    def _merge(self, x, y, fa):
        if x == 0 or y == 0:
            self.tree[x + y].fa = fa
            return x + y
        if self.tree[x].key > self.tree[y].key:
            self.push_down(x)
            self.tree[x].rs = self._merge(self.tree[x].rs, y, x)
            self.tree[x].fa = fa
            return x
        else:
            self.push_down(y)
            self.tree[y].ls = self._merge(x, self.tree[y].ls, y);
            self.tree[y].fa = fa
            return y

    def merge(self, x, y):
        x = self.find(x)
        y = self.find(y)

        if x != y:
            self._merge(x, y, 0)

sys.setrecursionlimit(10 ** 6)

n, q = map(int, input().split())

tree = Treap(n + 1)

for _ in range(q):
    data = list(map(int, input().split()))

    if data[0] == 1:
        tree.merge(data[1], data[2])
    elif data[0] == 2:
        tree.tree[data[1]].value += data[2]
    elif data[0] == 3:
        fa = tree.find(data[1])
        tree.tree[fa].value += data[2]
        tree.tree[fa].lazy += data[2]
    else:
        tree.find(data[1])
        print(tree.tree[data[1]].value)
