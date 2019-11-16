import tqdm

score_table = """A  4  0 -2 -1 -2  0 -2 -1 -1 -1 -1 -2 -1 -1 -1  1  0  0 -3 -2
C  0  9 -3 -4 -2 -3 -3 -1 -3 -1 -1 -3 -3 -3 -3 -1 -1 -1 -2 -2
D -2 -3  6  2 -3 -1 -1 -3 -1 -4 -3  1 -1  0 -2  0 -1 -3 -4 -3
E -1 -4  2  5 -3 -2  0 -3  1 -3 -2  0 -1  2  0  0 -1 -2 -3 -2
F -2 -2 -3 -3  6 -3 -1  0 -3  0  0 -3 -4 -3 -3 -2 -2 -1  1  3
G  0 -3 -1 -2 -3  6 -2 -4 -2 -4 -3  0 -2 -2 -2  0 -2 -3 -2 -3
H -2 -3 -1  0 -1 -2  8 -3 -1 -3 -2  1 -2  0  0 -1 -2 -3 -2  2
I -1 -1 -3 -3  0 -4 -3  4 -3  2  1 -3 -3 -3 -3 -2 -1  3 -3 -1
K -1 -3 -1  1 -3 -2 -1 -3  5 -2 -1  0 -1  1  2  0 -1 -2 -3 -2
L -1 -1 -4 -3  0 -4 -3  2 -2  4  2 -3 -3 -2 -2 -2 -1  1 -2 -1
M -1 -1 -3 -2  0 -3 -2  1 -1  2  5 -2 -2  0 -1 -1 -1  1 -1 -1
N -2 -3  1  0 -3  0  1 -3  0 -3 -2  6 -2  0  0  1  0 -3 -4 -2
P -1 -3 -1 -1 -4 -2 -2 -3 -1 -3 -2 -2  7 -1 -2 -1 -1 -2 -4 -3
Q -1 -3  0  2 -3 -2  0 -3  1 -2  0  0 -1  5  1  0 -1 -2 -2 -1
R -1 -3 -2  0 -3 -2  0 -3  2 -2 -1  0 -2  1  5 -1 -1 -3 -3 -2
S  1 -1  0  0 -2  0 -1 -2  0 -2 -1  1 -1  0 -1  4  1 -2 -3 -2
T  0 -1 -1 -1 -2 -2 -2 -1 -1 -1 -1  0 -1 -1 -1  1  5  0 -2 -2
V  0 -1 -3 -2 -1 -3 -3  3 -2  1  1 -3 -2 -2 -3 -2  0  4 -3 -1
W -3 -2 -4 -3  1 -2 -2 -3 -3 -2 -1 -4 -4 -2 -3 -3 -2 -3 11  2
Y -2 -2 -3 -2  3 -3  2 -1 -2 -1 -1 -2 -3 -1 -2 -2 -2 -1  2  7
"""
INDENT_COST = -5
scores = []
letters = []
for line in score_table.strip("\n").split("\n"):
    tokens = list(filter(bool, line.split(" ")))
    letters.append(tokens[0])
    scores.append(list(map(int, tokens[1:])))
# for line in scores:
#     print(line)

scores_map = dict()
for i, a in enumerate(letters):
    for j, b in enumerate(letters):
        key = a + b
        scores_map[key] = scores[i][j]

s1 = input().strip()
s2 = input().strip()
n = len(s1)
m = len(s2)
INF = int(1e9)
dp = [[-INF] * (m + 1) for i in range(n + 1)]
parent = [[-1] * (m + 1) for i in range(n + 1)]
dp[0][0] = 0
for i in tqdm.tqdm(range(n)):
    for j in range(m):
        if dp[i + 1][j] < dp[i][j] + INDENT_COST:
            dp[i + 1][j] = dp[i][j] + INDENT_COST
            parent[i + 1][j] = 0
        if dp[i][j + 1] < dp[i][j] + INDENT_COST:
            dp[i][j + 1] = dp[i][j] + INDENT_COST
            parent[i][j + 1] = 1
        cost = scores_map[s1[i] + s2[j]]
        if dp[i + 1][j + 1] < dp[i][j] + cost:
            dp[i + 1][j + 1] = dp[i][j] + cost
            parent[i + 1][j + 1] = 2
# for i in range(n + 1):
#     print('\t'.join(map(str, dp[i])))
# print()
a1 = []
a2 = []
i = n
j = m
while parent[i][j] != -1:
    if parent[i][j] == 0:
        i -= 1
        a1.append(s1[i])
        a2.append('-')
    elif parent[i][j] == 1:
        j -= 1
        a1.append('-')
        a2.append(s2[j])
    else:
        i -= 1
        j -= 1
        a1.append(s1[i])
        a2.append(s2[j])
print(dp[n][m])
print(''.join(a1[::-1]))
print(''.join(a2[::-1]))
