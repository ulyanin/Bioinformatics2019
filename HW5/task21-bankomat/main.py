
W = int(input())
coins = list(map(int, input().split(",")))
INF = int(1e9)
dp = [INF] * (W + 1)
dp[0] = 0
for w in range(W + 1):
    for c in coins:
        if w - c >= 0:
            dp[w] = min(dp[w], dp[w - c] + 1)
print(dp[W])