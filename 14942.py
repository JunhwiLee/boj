n = int(input())

energy = []

for i in range(n):
    energy.append(int(input()))

tree = [[] for _ in range(n)]

for i in range(n - 1):
    a, b, c = map(int, input().split())
    tree[a - 1].append((b - 1, c))
    tree[b - 1].append((a - 1, c))

res = [0 for _ in range(n)]
stack = []
path_length = []

def dfs(cur, pre, path):
    stack.append(cur)
    path_length.append(path)
    
    for nxt, weight in tree[cur]:
        if nxt == pre:
            continue
        dfs(nxt, cur, path + weight)

    #print(f"\n{cur + 1} is started")
    #print(stack)
    #print(path_length)

    answer = 0
    st, en = 0, len(path_length) - 1
    
    while st <= en:
        mid = (st + en) // 2

        if path_length[-1] - path_length[mid] <= energy[cur]:
            answer = mid
            en = mid - 1
        else:
            st = mid + 1

    res[cur] = stack[answer] + 1
    #print(f"target is : {energy[cur]}, result is : {res[cur]}")

    stack.pop()
    path_length.pop()

dfs(0, -1, 0)

for item in res:
    print(item)