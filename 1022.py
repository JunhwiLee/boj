r1, c1, r2, c2 = map(int, input().split())

def judge(i, j):
    k = max(abs(i), abs(j))
    res = (2 * k - 1) ** 2

    if i >= j:
        res += 6 * k + i + j
    else:
        res += 2 * k - i - j
    return res

res = []
longest = 0

for i in range(r1, r2 + 1):
    temp = []
    for j in range(c1, c2 + 1):
        k = str(judge(i, j))
        temp.append(k)
        longest = max(len(k), longest)
    res.append(temp)

blank = "                         "

for temp in res:
    for item in temp:
        print(blank[:longest - len(item)], end = '')
        print(item, end = ' ')
    print()