import math
import time
MAXD = 50

def add_str(a: str, b: str) -> str:
    i, j = len(a)-1, len(b)-1
    carry = 0
    res = []
    while i >= 0 or j >= 0 or carry:
        x = carry
        if i >= 0:
            x += ord(a[i]) - 48
            i -= 1
        if j >= 0:
            x += ord(b[j]) - 48
            j -= 1
        res.append(chr(x % 10 + 48))
        carry = x // 10
    res.reverse()
    s = "".join(res)
    if len(s) > MAXD:
        s = s[:MAXD]
    return s

INF = 2 ** 31
class Node:
    def __init__(self, sh):
        self.next = {}
        self.sh = sh
class Trie:
    def __init__(self):
        self.head = Node(INF)
    def insert(self, string, sh):
        cur = self.head
        for ch in string:
            if not ch in cur.next:
                cur.next[ch] = Node(sh)
            cur.sh = min(cur.sh, sh)
            cur = cur.next[ch]
    def search(self, string):
        cur = self.head
        for ch in string:
            if not ch in cur.next:
                return -1
            cur = cur.next[ch]
        return cur.sh

trie = Trie()

fr = "1"
se = "1"
trie.insert("1", 0)
for i in range(2, 100001):
    temp = add_str(fr, se)
    fr = se
    se = temp
    print(temp)
    trie.insert(temp, i)

n = int(input())
for i in range(n):
    print(f"Case #{i}: {trie.search(input())}")