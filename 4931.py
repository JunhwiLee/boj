from collections import deque

def rotate_queue(q, k):
    if not q or k % len(q) == 0:
        return q
    k %= len(q)
    return q[k:] + q[:k]

def min_ops(start_q):
    N = len(start_q)
    target_q = tuple(sorted(start_q))
    start = (tuple(start_q), tuple(), tuple())

    dq = deque()
    dq.append((start, 0))
    visited = set([start])

    while dq:
        (Q, A, B), d = dq.popleft()

        # QA
        if len(Q) >= 1:
            for n in range(1, len(Q) + 1):
                moved = Q[:n]
                newQ = Q[n:]
                newA = A + moved
                state = (newQ, newA, B)
                if state not in visited:
                    if newQ == target_q and not A and not B:
                        return d + 1
                    visited.add(state)
                    dq.append((state, d + 1))

        # QB
        if len(Q) >= 1:
            for n in range(1, len(Q) + 1):
                moved = Q[:n]
                newQ = Q[n:]
                newB = B + moved
                state = (newQ, A, newB)
                if state not in visited:
                    if newQ == target_q and not A and not B:
                        return d + 1
                    visited.add(state)
                    dq.append((state, d + 1))

        # QQ
        if len(Q) >= 2:
            L = len(Q)
            for k in range(1, L):
                newQ = rotate_queue(Q, k)
                state = (newQ, A, B)
                if state not in visited:
                    if newQ == target_q and not A and not B:
                        return d + 1
                    visited.add(state)
                    dq.append((state, d + 1))

        # AQ
        if len(A) >= 1:
            for n in range(1, len(A) + 1):
                moved = A[-n:]
                newA = A[:-n]
                newQ = Q + moved
                state = (newQ, newA, B)
                if state not in visited:
                    if newQ == target_q and not A and not B:
                        return d + 1
                    visited.add(state)
                    dq.append((state, d + 1))

        if len(B) >= 1:
            for n in range(1, len(B) + 1):
                moved = B[-n:]
                newB = B[:-n]
                newQ = Q + moved
                state = (newQ, A, newB)
                if state not in visited:
                    if newQ == target_q and not A and not B:
                        return d + 1
                    visited.add(state)
                    dq.append((state, d + 1))

        if len(A) >= 1:
            for n in range(1, len(A) + 1):
                moved = A[-n:]
                newA = A[:-n]
                newB = B + moved
                state = (Q, newA, newB)
                if state not in visited:
                    visited.add(state)
                    dq.append((state, d + 1))

        if len(B) >= 1:
            for n in range(1, len(B) + 1):
                moved = B[-n:]
                newB = B[:-n]
                newA = A + moved
                state = (Q, newA, newB)
                if state not in visited:
                    visited.add(state)
                    dq.append((state, d + 1))

    return -1

line = input()
while line != "0":
    parts = list(map(int, line.split()))
    if parts[0] == 0:
        break
    N = parts[0]
    q = parts[1:]
    print(str(min_ops(q)))
    line = input()
