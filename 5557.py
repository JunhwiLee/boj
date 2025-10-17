n = int(input())
arr = list(map(int, input().split()))

dp = [[0 for _ in range(21)] for _ in range(n)]
dp[0][arr[0]] = 1
for i in range(n - 2):
    for j in range(21):
        if dp[i][j]:
            if 0 <= j + arr[i + 1] <= 20:
                dp[i + 1][j + arr[i + 1]] += dp[i][j]
            if 0 <= j - arr[i + 1] <= 20:
                dp[i + 1][j - arr[i + 1]] += dp[i][j]
print(dp[n - 2][arr[n - 1]])