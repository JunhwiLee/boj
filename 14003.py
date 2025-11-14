n = int(input())
arr = list(map(int, input().split()))
dp = []
mask = [-1] * n

def binary_search(val):
    st, en = 0, len(dp) - 1
    while st < en:
        mid = (st + en) // 2
        if dp[mid] < val:
            st = mid + 1
        else:
            en = mid
    return st

dp.append(arr[0])
last = 0

for i in range(1, n):
    if arr[i] > dp[-1]:
        dp.append(arr[i])
        mask[i] = last
        last = i
    else:
        idx = binary_search(arr[i])
        dp[idx] = arr[i]
        if idx == len(dp) - 1:
            mask[i] = mask[last]
            last = i

print(len(dp))
res = []

while not last == -1: 
    res.append(arr[last])
    last = mask[last]
print(*res[::-1])