# test.py
import sys
import subprocess
from textwrap import dedent

def read_cases(path: str, sep: str = "==="):
    with open(path, encoding="utf-8") as f:
        text = f.read()
    # 구분자 기준으로 케이스 분리
    raw_blocks = text.split(sep)
    cases = []
    for block in raw_blocks:
        case = block.strip()
        if case:  # 빈 블록은 무시
            cases.append(case)
    return cases

def LCS(n, arr):
    dp = []

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

    for i in range(1, n):
        if arr[i] > dp[-1]:
            dp.append(arr[i])
        else:
            idx = binary_search(arr[i])
            dp[idx] = arr[i]

    print(len(dp))

def judge(case_input: str, user_output: str) -> bool:
    """
    여기서 정답/오답을 판정한다.
    - 기대 출력이 고정돼 있지 않으므로,
      1) 내부에 정답 로직을 직접 구현하거나
      2) 레퍼런스 솔루션을 같이 실행해서 비교하는 방식으로 만들면 된다.
    현재는 예시로 True만 돌려둔다.
    """
    try:
        case_input = list(map(int, case_input.split()))
        user_output = list(map(int, user_output.split()))
        n = user_output[0]
        if(n == LCS(case_input[0], case_input[1:])):
            return False
        case_input = case_input[1:]
        user_output = user_output[1:]
        if n != len(user_output):
            return False

        for i in range(n - 1):
            if user_output[i] >= user_output[i + 1]:
                return False

        idx = 0
        for i in range(len(case_input)):
            if case_input[i] == user_output[idx]:
                idx += 1
            if idx == n:
                return True
    except:
        print("출력 형식 오류")
        return False
    # TODO: 여기에 실제 채점 로직 작성
    return False

def main():
    if len(sys.argv) != 3:
        print("Usage: python test.py <solution.py> <test_file>", file=sys.stderr)
        sys.exit(1)

    solution = sys.argv[1]   # 예: 14003.py
    test_file = sys.argv[2]  # 예: test.txt

    cases = read_cases(test_file)

    all_pass = True
    for idx, case_input in enumerate(cases, start=1):
        # 풀이 실행
        proc = subprocess.run(
            [sys.executable, solution],
            input=case_input + "\n",
            text=True,
            capture_output=True,
        )
        user_out = proc.stdout.rstrip("\n")

        ok = judge(case_input, user_out)

        print(f"[Case {idx}]")
        print("=== Input ===")
        print(case_input)
        print("=== Output ===")
        print(user_out)
        GREEN = "\033[32m"
        RED = "\033[31m"
        RESET = "\033[0m"
        print(f"Result: {f'{GREEN}OK{RESET}' if ok else f'{RED}FAIL{RESET}'}")
        print()

        if not ok:
            all_pass = False

    if all_pass:
        print("✅ 모든 테스트 케이스 통과")
    else:
        print("❌ 실패한 테스트 케이스가 있습니다.")
        sys.exit(1)

if __name__ == "__main__":
    main()
