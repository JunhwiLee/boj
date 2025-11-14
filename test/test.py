# test.py
import sys
import subprocess
import shlex

def read_cases(path: str, sep: str = "==="):
    with open(path, encoding="utf-8") as f:
        text = f.read()
    raw_blocks = text.split(sep)
    cases = []
    for block in raw_blocks:
        case = block.strip()
        if case:
            cases.append(case)
    return cases

def judge(case_input: str, user_output: str) -> bool:
    """
    - case_input: 원본 입력 문자열
    - user_output: 유저 프로그램의 출력 문자열
    """
    try:
        print("hello")
    except Exception as e:
        print("출력 형식 오류:", e)
        return False

    return False

def main():
    if len(sys.argv) != 3:
        print("Usage: python test.py \"<run_command>\" <test_file>", file=sys.stderr)
        print("  e.g. python test.py \"python3 14003.py\" case.txt", file=sys.stderr)
        print("       python test.py \"./exe\" case.txt", file=sys.stderr)
        print("       python test.py \"java boj14003\" case.txt", file=sys.stderr)
        sys.exit(1)

    run_cmd_str = sys.argv[1]  # 예: "python3 14003.py" / "./exe" / "java boj14003"
    test_file = sys.argv[2]     # 예: case/case14003.txt

    # 문자열을 실제 명령 리스트로 파싱
    run_cmd = shlex.split(run_cmd_str)

    cases = read_cases(test_file)

    all_pass = True
    for idx, case_input in enumerate(cases, start=1):
        # 풀이 실행
        proc = subprocess.run(
            run_cmd,
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
