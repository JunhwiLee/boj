n = int(input())

def find(m):
    if n == 1:
        print("1 + 1 - 1")
        return
    if n == 2:
        print("3 + 3 - 4")
        return
    if n == 3:
        print("4 + 6 - 7")
        return
    if n == 5:
        print("4 + 5 - 6")
        return
        
    for i in range(1, 1001):
        for j in range(1, 1001):
            #if i == j: continue
            if m - 1 == i * i - j * j:
                print(f"1 + {i} - {j}")
                return
            if m - 4 == i * i - j * j:
                print(f"2 + {i} - {j}")
                return

for i in range(n):
    find(int(input()))