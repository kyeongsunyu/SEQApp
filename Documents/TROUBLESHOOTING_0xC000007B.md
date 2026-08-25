# 실행 즉시 0xC000007B 로 종료될 때

```
xxxxx 스레드가 종료되었습니다(코드: 3221225595 (0xc000007b)).
'[xxxxx] SEQApp.exe' 프로그램이 종료되었습니다(코드: 3221225595 (0xc000007b)).
```

## 의미

`0xC000007B = STATUS_INVALID_IMAGE_FORMAT`.
여러 스레드가 **모두 같은 코드**로 끝난 뒤 프로세스가 같은 코드로 종료되면,
Windows 로더가 만든 loader worker 스레드까지 함께 죽은 것이다.
즉 `InitInstance`/`main` **진입 전**, 정적 import DLL 을 해석하는 단계에서 실패한 것이며
애플리케이션 로직 버그가 아니다. (실행 중 오류라면 0xC0000005 같은 예외 코드가
특정 스레드 하나에만 찍힌다.)

원인은 사실상 하나다: **exe 와 비트(32/64)가 다른 DLL 을 물었다.**

## 이 프로젝트에서 주의할 점

`Library\AXL(Library)\Library\` 아래 `32Bit`, `64Bit` 폴더의

- `AXL.dll`
- `EzBasicAxl.dll` (AXL.dll 이 다시 import 한다)

는 **파일 이름이 서로 완전히 같다.** 파일명만으로는 비트를 구분할 수 없으므로,
실행 폴더 / `System32` / `SysWOW64` / `PATH` 중 먼저 잡히는 것이 exe 와 다른 비트면
바로 이 증상이 난다.

`SEQApp.vcxproj` 는 빌드 후 이벤트에서 `$(AxlBitDir)` 에 해당하는 DLL 을
`$(OutDir)` 로 복사해 이 문제를 막는다. 그래도 발생한다면 아래를 확인한다.

## 확인 절차 (개발자 명령 프롬프트)

```cmd
:: 1. exe 의 비트 확인 (14C = x86, 8664 = x64)
dumpbin /headers SEQApp.exe | findstr machine

:: 2. 정적 의존 DLL 목록
dumpbin /dependents SEQApp.exe

:: 3. 실제로 잡히는 AXL.dll 이 어느 것인지, 그 비트는 무엇인지
where AXL.dll
dumpbin /headers <위에서 나온 경로> | findstr machine
dumpbin /headers C:\Windows\System32\AXL.dll  | findstr machine
dumpbin /headers C:\Windows\SysWOW64\AXL.dll  | findstr machine

:: 4. 그래도 못 찾으면 로더 스냅을 켜고 디버거 출력 창을 본다
gflags /i SEQApp.exe +sls
::   확인 후 반드시 해제
gflags /i SEQApp.exe -sls
```

GUI 도구로는 **Dependencies**(Dependency Walker 후속)로 exe 를 열면
아키텍처가 어긋난 모듈이 바로 표시된다.

## 헷갈리기 쉬운 인접 오류

| 코드 | 의미 |
| --- | --- |
| `0xC000007B` | DLL 은 찾았는데 **비트/포맷이 다르다** (또는 파일 손상) |
| `0xC0000135` | 의존 DLL 을 **못 찾았다** (VC++ 재배포 미설치 등) |
| `0xC0000005` | 실행 중 액세스 위반 — 로더 문제가 아니라 코드 버그 |
