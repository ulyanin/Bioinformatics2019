import tqdm

score_table = """A  2 -2  0  0 -3  1 -1 -1 -1 -2 -1  0  1  0 -2  1  1  0 -6 -3
C -2 12 -5 -5 -4 -3 -3 -2 -5 -6 -5 -4 -3 -5 -4  0 -2 -2 -8  0
D  0 -5  4  3 -6  1  1 -2  0 -4 -3  2 -1  2 -1  0  0 -2 -7 -4
E  0 -5  3  4 -5  0  1 -2  0 -3 -2  1 -1  2 -1  0  0 -2 -7 -4
F -3 -4 -6 -5  9 -5 -2  1 -5  2  0 -3 -5 -5 -4 -3 -3 -1  0  7
G  1 -3  1  0 -5  5 -2 -3 -2 -4 -3  0  0 -1 -3  1  0 -1 -7 -5
H -1 -3  1  1 -2 -2  6 -2  0 -2 -2  2  0  3  2 -1 -1 -2 -3  0
I -1 -2 -2 -2  1 -3 -2  5 -2  2  2 -2 -2 -2 -2 -1  0  4 -5 -1
K -1 -5  0  0 -5 -2  0 -2  5 -3  0  1 -1  1  3  0  0 -2 -3 -4
L -2 -6 -4 -3  2 -4 -2  2 -3  6  4 -3 -3 -2 -3 -3 -2  2 -2 -1
M -1 -5 -3 -2  0 -3 -2  2  0  4  6 -2 -2 -1  0 -2 -1  2 -4 -2
N  0 -4  2  1 -3  0  2 -2  1 -3 -2  2  0  1  0  1  0 -2 -4 -2
P  1 -3 -1 -1 -5  0  0 -2 -1 -3 -2  0  6  0  0  1  0 -1 -6 -5
Q  0 -5  2  2 -5 -1  3 -2  1 -2 -1  1  0  4  1 -1 -1 -2 -5 -4
R -2 -4 -1 -1 -4 -3  2 -2  3 -3  0  0  0  1  6  0 -1 -2  2 -4
S  1  0  0  0 -3  1 -1 -1  0 -3 -2  1  1 -1  0  2  1 -1 -2 -3
T  1 -2  0  0 -3  0 -1  0  0 -2 -1  0  0 -1 -1  1  3  0 -5 -3
V  0 -2 -2 -2 -1 -1 -2  4 -2  2  2 -2 -1 -2 -2 -1  0  4 -6 -2
W -6 -8 -7 -7  0 -7 -3 -5 -3 -2 -4 -4 -6 -5  2 -2 -5 -6 17  0
Y -3  0 -4 -4  7 -5  0 -1 -4 -1 -2 -2 -5 -4 -4 -3 -3 -2  0 10
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
        if dp[i][j] < 0:
            dp[i][j] = 0
            parent[i][j] = -1
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

best_ans = 0
best_indices = None
for i in range(n + 1):
    for j in range(m + 1):
        if dp[i][j] > best_ans:
            best_ans = dp[i][j]
            best_indices = (i, j)
a1 = []
a2 = []
i, j = best_indices
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
print(best_ans)
print(''.join(a1[::-1]))
print(''.join(a2[::-1]))
