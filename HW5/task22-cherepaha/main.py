def input_list():
    return list(map(int, input().split()))


n, m = input_list()
down = []
for i in range(n):
    down.append(input_list())
s = input()
assert s == "-"
right = []
for i in range(n + 1):
    right.append(input_list())
# print(down)
# print(right)s

dp = [[-1] * (m + 1) for i in range(n + 1)]
dp[0][0] = 0
for i in range(n + 1):
    for j in range(m + 1):
        if i < n:
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + down[i][j])
        if j < m:
            dp[i][j + 1] = max(dp[i][j + 1], dp[i][j] + right[i][j])
print(dp[n][m])
