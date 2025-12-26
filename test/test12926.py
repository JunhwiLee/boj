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


def _normalize_output(s: str) -> str:
    """
    출력 비교용 정규화:
    - 끝쪽 공백/개행 제거
    - 각 줄 끝의 공백 제거
    """
    s = s.rstrip("\n")
    lines = s.splitlines()
    lines = [line.rstrip() for line in lines]
    return "\n".join(lines)


def judge(case_input: str, user_output: str, ref_cmd=None) -> bool:
    """
    - case_input: 원본 입력 문자열
    - user_output: 유저 프로그램의 출력 문자열
    - ref_cmd: 참조(정답) 프로그램 실행 커맨드 리스트 (없으면 None)

    ref_cmd가 주어지면:
      - 동일한 입력으로 ref_cmd를 실행해 참조 출력과 비교

    ref_cmd가 없으면:
      - 서브태스크/P 문제처럼 직접 채점 로직을 여기에 구현해서 사용
    """
    # 참조 코드가 있는 경우: 출력 비교
    if ref_cmd is not None:
        try:
            proc = subprocess.run(
                ref_cmd,
                input=case_input + "\n",
                text=True,
                capture_output=True,
            )
        except Exception as e:
            print("⚠ 참조 코드 실행 실패:", e, file=sys.stderr)
            return False

        ref_out = proc.stdout

        norm_user = _normalize_output(user_output)
        norm_ref = _normalize_output(ref_out)

        return norm_user == norm_ref

    # 참조 코드가 없는 경우: 직접 채점(P 문제 등)
    try:
        # TODO: 여기에서 case_input, user_output을 이용한
        #       커스텀 판별 로직을 구현하면 됨.
        # 예시) 간단히 출력이 비어있지 않으면 OK 라는 식:
        # return bool(user_output.strip())

        # 기본은 항상 실패로 두고, P 문제마다 수정해서 사용
        print("⚠ ref_cmd가 없으므로 커스텀 judge 로직을 구현해야 합니다.", file=sys.stderr)
        return False
    except Exception as e:
        print("출력 형식/채점 오류:", e, file=sys.stderr)
        return False


def main():
    # 인자:
    #   1: 유저 프로그램 실행 커맨드 문자열
    #   2: 케이스 파일 경로
    #   3: (옵션) 참조 프로그램 실행 커맨드 문자열
    if not (3 <= len(sys.argv) <= 4):
        print("Usage: python test.py \"<run_command>\" <test_file> [\"<ref_command>\"]", file=sys.stderr)
        print("  e.g. python test.py \"python3 14003.py\" case.txt", file=sys.stderr)
        print("       python test.py \"./exe\" case.txt", file=sys.stderr)
        print("       python test.py \"java boj14003\" case.txt", file=sys.stderr)
        print("  with reference:", file=sys.stderr)
        print("       python test.py \"./exe\" case.txt \"./exe_ref\"", file=sys.stderr)
        sys.exit(1)

    run_cmd_str = sys.argv[1]   # 예: "python3 14003.py" / "./exe" / "java boj14003"
    test_file = sys.argv[2]     # 예: case/case14003.txt

    ref_cmd = None
    if len(sys.argv) == 4:
        ref_cmd_str = sys.argv[3]
        ref_cmd = shlex.split(ref_cmd_str)

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

        ok = judge(case_input, user_out, ref_cmd)

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
