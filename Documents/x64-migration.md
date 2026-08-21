# SEQApp x64 전환 확인 결과

대상: `SEQApp.vcxproj` / `SEQApp.sln` (MFC, v143, Unicode, MFC 동적 링크)

## 1. 프로젝트 설정 변경

x64 구성이 이미 존재했지만 Win32 구성과 동일한 수준으로 맞춰져 있지 않아
그대로는 빌드가 되지 않는 상태였다. 다음을 수정했다.

| 항목 | 이전 | 변경 후 |
| --- | --- | --- |
| 플랫폼 순서 | `Win32`가 먼저 → 기본 플랫폼이 Win32 | `x64`를 먼저 기재 → 기본 플랫폼이 x64 |
| `Release\|x64` 미리 컴파일된 헤더 | `Use` (하지만 `/Yc`를 만드는 파일이 없음 → C1010) | `NotUsing` (Debug 구성과 동일) |
| `Release\|x64` SDLCheck | `true` → `sprintf`/`strcpy`/`inet_ntoa`가 C4996 오류 | `false` (Debug 구성과 동일) |
| `Release\|x64` 전처리기 | `_CRT_SECURE_NO_WARNINGS`, `_WINSOCK_DEPRECATED_NO_WARNINGS` 없음 | 추가 |
| `Release\|x64` AXL 링크 | 라이브러리 경로·`AXL.lib` 자체가 없음 → LNK2019 | Debug\|x64와 동일하게 지정 |
| 두 x64 구성 언어 표준 | 지정 없음 (기본 C++14) | `stdcpp17`, `ConformanceMode=false` (Debug\|Win32와 동일) |
| 두 x64 구성 소스 인코딩 | Release에는 `/source-charset:utf-8` 없음 | 두 구성 모두 지정 |
| AXL 검색 경로 | `C:\Program Files (x86)\EzSoftware UC\...` 절대 경로만 | 저장소에 포함된 `Library\AXL(Library)\Library\64Bit`를 먼저 검색, 기존 절대 경로는 뒤에 유지 |
| `Debug\|x64` 출력 경로 | 지정 없음 (`x64\Debug\`) | `C:\WORK\` (Debug\|Win32와 동일) |

`Debug|x64`의 출력 경로를 `C:\WORK\`로 맞췄으므로, **같은 폴더의 32비트
`AXL.dll` / `EzBasicAxl.dll`을 `Library\AXL(Library)\Library\64Bit`의 64비트
버전으로 반드시 교체해야 한다.** 32비트 DLL이 남아 있으면 실행 시
`0xC000007B`로 실패한다.

## 2. 소스 수정

- `SEQApp/Tools/CLASS_INI.cpp` `CIni::__StrDupEx()` — 두 포인터를 `DWORD`로
  잘라낸 뒤 빼고 있었다(C4311). `lpEnd - lpStart`로 바꿨다. 포인터 차이는
  이미 TCHAR 단위이므로 `sizeof(TCHAR)` 나눗셈은 제거했다.
- `SEQApp/SeqThread/THREAD_TcpServer.cpp` / `SEQApp/SeqMain/CLASS_Main.h`
  `ClientVisionConn()` — `void(void*)` 함수를 `LPTHREAD_START_ROUTINE`으로
  강제 캐스팅해 `CreateThread`에 넘기고 있었다. 반환값이 없어 스레드 종료
  코드가 쓰레기 값이 된다. `DWORD WINAPI (LPVOID)`로 선언을 바로잡고 캐스팅을
  제거했다.

## 3. 검증

### 3.1 프로세스 간 구조체 레이아웃

SEQApp은 `MMIApp` / `COMMUNICATION_App` / 비전 장비와 구조체를 그대로
주고받는다. SEQApp만 x64가 되어도 이 바이트 배치가 바뀌지 않아야 한다.

`tools/abi_check/run.sh`가 실제 헤더를 32비트·64비트 MSVC ABI로 각각 파싱해
레코드 레이아웃을 비교한다. 결과: **80개 구조체 전부 크기·오프셋 동일**.

| 채널 | 구조체 | 크기 (x86 = x64) |
| --- | --- | --- |
| 공유 메모리 `/SMEMORY` | `TMemCommand` | 40,008 (버퍼 반쪽 262,144) |
| 메모리 매핑 파일 | `_MMF` | 160,194 (`MMFSIZE` 250,000) |
| `WM_COPYDATA` | `SEQ_RSP` / `SEQ_LOG` | 264 / 512 |
| 비전 TCP | `VISION_PROTOCOL_DATA` | 1,028 |
| 설비 상태 | `TMachineStatus` | 1,041 |

모든 통신 구조체가 `#pragma pack(1)` + 고정 폭 타입만 사용하고 포인터 멤버가
없어서 그렇다. `unsigned long`도 MSVC에서는 x64에서도 4바이트다(LLP64).

### 3.2 소스 전수 검사

`SEQApp/` 전체(32,730줄)에서 다음을 확인했다.

- 인라인 어셈블리(`__asm`) — 없음. x64 MSVC는 인라인 어셈블리를 지원하지 않는다.
- 포인터를 32비트 정수로 캐스팅(C4311/C4302) — `CLASS_INI.cpp` 1건, 수정 완료.
- 정수를 포인터로 캐스팅(C4312) — 없음.
- `SOCKET`을 `int`에 담는 코드 — 없음. 전부 `SOCKET` 타입을 유지한다.
- `SetWindowLong` / `GetWindowLong` 계열 — 사용처 없음(주석 1건).
- 타이머/스레드 콜백 — `DWORD_PTR` 사용, x64에서 정상.
- 가변 인자에 포인터·`size_t`를 `%d`로 넘기는 곳 — 없음.
- `MMI2SEQ` 등 통신 구조체의 포인터 멤버 — 없음.

### 3.3 남은 확인 사항

- 실제 컴파일·링크는 Visual Studio 2022(v143) + Windows 10 SDK 환경에서
  `Debug|x64`, `Release|x64` 두 구성으로 확인해야 한다. 이 저장소에서는
  MSVC가 없어 위 정적 검증까지만 수행했다.
- 대상 PC에 x64용 MFC 재배포 패키지(`mfc140u.dll`)가 필요하다.
- 프로젝트 전역에서 C4267(`size_t` → `int` 축소)이 `DisableSpecificWarnings`로
  꺼져 있다. x64 전환에서 가장 많이 나오는 경고가 이것이므로, 한 번은 이
  설정을 풀고 빌드해 경고 목록을 훑어보길 권한다. 현재 코드의 해당 위치는
  모두 소켓 버퍼(수 KB) 길이라 실질적인 위험은 없다.

## 4. x64와 무관하게 발견한 기존 결함

전환 범위 밖이라 수정하지 않았다.

- `SEQApp/Tools/CLASS_FileLog.cpp` `Delete_Dated_File()` — `char*`를
  `(LPCWSTR)`로 캐스팅해 `FindFirstFile`에 넘긴다. 또 실패 판정을
  `if (hFind)`로 하는데 실패값은 `INVALID_HANDLE_VALUE`(=-1)이라 항상 참이다.
- `SEQApp/Tools/CLASS_INI.cpp` `__TrimString()` — `_tcsdup()`(malloc)으로 받은
  메모리를 `delete[]`로 해제한다.
- `SEQApp/SeqThread/THREAD_TcpServer.cpp` — 접속마다 같은 `p_ThrArg` 한 개를
  재사용해 스레드에 넘긴다. 동시 접속 시 경합이 발생한다.
- `SEQApp/SeqMain/CLASS_3Point.cpp`, `SEQApp/SeqMain/SEQ00_AutoRun.cpp`는
  프로젝트에 포함되어 있지 않다. 전자는 호출부가 모두 주석 처리되어 있고,
  후자는 `FUNC_AutoRun.cpp`와 같은 함수를 정의하므로 넣으면 중복 정의가 된다.
  현재 제외 상태가 맞다.
