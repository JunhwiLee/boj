t = int(input())

def dfs(tree, cur):
    sub = []
    m = 0
    for nxt in tree[cur]:
        dep, string = dfs(tree, nxt)
        m = max(m, dep)
        sub.append((dep, string))
    sub.sort()

    res_string = "1"
    for dep, string in sub:
        res_string += string
    res_string += "0"
    return m + 1, res_string

def f():
    n = int(input())
    tree = [[] for _ in range(n)]

    line = list(map(int, input().split()))
    for i in range(1, n):
        tree[line[i] - 1].append(i)

    dep, string = dfs(tree, 0)
    print(string)

for _ in range(t):
    f()