n = int(input())

def find(num):
    if num == 1:
        print("1 + 1 - 1")
        return
    if num == 2:
        print("3 + 3 - 4")
        return
    if num == 3:
        print("4 + 6 - 7")
        return
    if num == 5:
        print("4 + 5 - 6")
        return
    m = num
    m -= 1

    a = 1

    mi = 0
    pl = 0

    if m % 4 == 0:
        mi = 2
        pl = m // 2
    elif m % 2 == 1:
        mi = 1
        pl = m
    else:
        m -= 3
        a = 2
        mi = 1
        pl = m

    print(f"{a} + {(pl + mi) // 2} - {(pl - mi) // 2}")
    if a ** 2 + ((pl + mi) // 2) ** 2 - ((pl - mi) // 2) ** 2 != num or a <= 0 or (pl + mi) // 2 <= 0 or ((pl - mi) // 2) <= 0:
        print(f"Error in {num}")
        exit()


for i in range(n):
    find(int(input()))