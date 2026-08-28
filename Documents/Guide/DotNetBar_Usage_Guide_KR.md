# DevComponents DotNetBar 사용 가이드 (Visual Studio)

> 대상: SEQApp 개발자
> 정리일: 2026-08

---

## 0. 시작하기 전에 — SEQApp과의 관계

**DotNetBar은 .NET(WinForms / WPF) 전용 UI 컴포넌트입니다. MFC C++에서는 직접 사용할 수 없습니다.**

현재 `SEQApp.vcxproj` 설정:

| 항목 | 값 |
|---|---|
| Keyword | `MFCProj` |
| PlatformToolset | `v143` (VS2022) |
| UseOfMfc | `Dynamic` |
| CharacterSet | `Unicode` |
| Platform | Win32 / x64 |

즉 SEQApp 본체(시퀀스 엔진)에 DotNetBar 컨트롤을 폼 디자이너로 얹는 것은 불가능합니다.
선택지는 세 가지입니다.

### 선택지 A — MMI를 별도 C# 프로세스로 만들고 거기에 DotNetBar 적용 (권장)

SEQApp은 이미 **MMI를 별도 프로세스로 분리하는 구조**로 설계되어 있습니다.

- `SEQApp/Func/SharedMemBase.h` : 네임드 공유 메모리 `"/SMEMORY"` (크기 `0x40000 * 2`),
  앞 절반 Tx / 뒤 절반 Rx로 분할
- `enum TRunType { RUN_SEQ = 1, RUN_MMI = 2 };` : 프로세스 역할 구분
- `SEQApp/SeqThread/THREAD_MMI.cpp` : `MMI_MessageCommunication()` 을 1ms 주기로 폴링
- `SEQApp/Func/NVMMF.h` : `"MMF_MAP"` (크기 250000) 불휘발 데이터 영역
- 그 외 `THREAD_TcpServer.cpp` / `THREAD_UdpClient.cpp` 로 소켓 경로도 열려 있음

따라서 **C# WinForms + DotNetBar로 MMI(GUI)를 만들고, 공유 메모리나 TCP로 SEQApp과 통신**하는 것이
구조상 가장 자연스럽습니다. 시퀀스 엔진(리얼타임 우선순위 스레드)과 GUI가 프로세스 단위로
분리되므로 GUI 렉이 시퀀스 스캔 타임에 영향을 주지 않는다는 장점도 그대로 유지됩니다.

### 선택지 B — C++/CLI 혼합 모드로 MFC 안에 WinForms 호스팅

MFC는 `CWinFormsControl` / `CWinFormsView` 로 Windows Forms 컨트롤 호스팅을 지원합니다.

1. C++/CLI DLL 프로젝트를 새로 만들고 `/clr` 활성화
2. 그 DLL에서 DotNetBar 컨트롤을 담은 `UserControl` 작성
3. MFC 다이얼로그에서 `CWinFormsControl<MyUserControl>` 로 호스팅

가능은 하지만 비용이 큽니다: `/clr` 은 `/RTC`, 일부 최적화, `/GL`(WholeProgramOptimization) 과 충돌하고,
현재 Release 구성이 `WholeProgramOptimization=true` 라 조정이 필요합니다. 또한 CLR 로딩으로
프로세스 시작 시간과 GC 지연이 생기므로 **리얼타임 시퀀스 프로세스에는 권장하지 않습니다.**

### 선택지 C — MFC용 UI 라이브러리를 쓴다

DotNetBar과 비슷한 리본/도킹 UI를 MFC에서 원한다면:

- **MFC Feature Pack** (VS 기본 내장, 무료): `CMFCRibbonBar`, `CMFCVisualManager`, 도킹 창
- **BCGControlBar Pro** (상용): MFC Feature Pack의 원본
- **Codejock Xtreme Toolkit Pro** (상용)

---

## 1. DotNetBar 개요

| 항목 | 내용 |
|---|---|
| 제작사 | DevComponents LLC |
| 제품군 | DotNetBar for **Windows Forms**, for **WPF**, DotNetBar for Silverlight(단종) |
| 성격 | 상용 라이선스 (개발자 단위 구매) |
| 지원 IDE | Visual Studio 2005 ~ 2015 계열 공식 지원 (이후 버전은 수동 등록으로 사용) |
| 최종 버전 | 14.x 계열 (2016년 전후). 이후 사실상 신규 개발 중단 상태 |
| 런타임 | **.NET Framework 전용** — .NET Core / .NET 5+ WinForms는 공식 지원 없음 |
| 핵심 어셈블리 | `DevComponents.DotNetBar2.dll` (네임스페이스 `DevComponents.DotNetBar`) |

> ⚠️ 신규 프로젝트라면 이 점을 먼저 판단하세요.
> .NET Framework 4.x에 묶이고, 벤더 지원이 사실상 끝난 컴포넌트입니다.
> 아래 8장의 대안 검토를 함께 보시길 권합니다.

---

## 2. 설치

### 2-1. 설치 파일로 설치

1. 구매한 계정으로 DevComponents에서 설치 관리자(`DotNetBar_*.msi` / `setup.exe`) 다운로드
2. 실행 → 설치 경로 기본값: `C:\Program Files (x86)\DevComponents\DotNetBar for Windows Forms\`
3. 설치 시 Visual Studio 도구 상자에 **"DotNetBar"** 탭이 자동 등록됨
4. 함께 설치되는 것들
   - `Bin\` : 런타임 어셈블리 (`DevComponents.DotNetBar2.dll` 등)
   - `Help\` : CHM 도움말 — **API 레퍼런스의 1차 출처**
   - `Samples\` : C#/VB 샘플 솔루션 — 컨트롤별 사용법은 여기가 가장 빠름

### 2-2. 도구 상자에 안 뜰 때 (VS2017 이후에서 흔함)

DotNetBar 설치 관리자는 최신 VS를 인식하지 못하는 경우가 있습니다. 수동 등록:

1. 도구 상자 빈 곳 우클릭 → **탭 추가** → 이름 `DotNetBar`
2. 해당 탭 우클릭 → **항목 선택(Choose Items…)**
3. `.NET Framework 구성 요소` 탭 → **찾아보기** →
   `C:\Program Files (x86)\DevComponents\DotNetBar for Windows Forms\Bin\DevComponents.DotNetBar2.dll`
4. 확인 → 컨트롤 목록이 채워짐

### 2-3. 프로젝트에 참조 추가

```
프로젝트 → 참조 추가 → 찾아보기 → DevComponents.DotNetBar2.dll
```

- 참조 속성에서 **로컬 복사(Copy Local) = True** 로 둘 것 (배포 시 필요)
- 다국어를 쓴다면 `Bin\<언어코드>\` 하위 위성 어셈블리도 함께 배포

### 2-4. 라이선스 파일 (`licenses.licx`)

DotNetBar은 .NET 표준 컴포넌트 라이선싱을 씁니다.
디자이너에 컨트롤을 처음 올리면 프로젝트에 `Properties\licenses.licx` 가 자동 생성됩니다.

```
DevComponents.DotNetBar.ButtonX, DevComponents.DotNetBar2, Version=14.0.0.0, Culture=neutral, PublicKeyToken=...
```

- 이 파일은 **반드시 소스 관리에 커밋**하고, 빌드 작업을 `EmbeddedResource` 로 유지
- 빌드 서버 / CI 머신에도 DotNetBar이 설치되어 있어야 `lc.exe` 가 라이선스를 임베드할 수 있음
- 파일이 깨졌거나 버전이 안 맞으면 실행 시 라이선스 예외가 납니다 → 7장 참고

---

## 3. 기본 사용법

### 3-1. 폼 만들기

일반 `Form` 대신 DotNetBar 폼 베이스를 쓰면 비클라이언트 영역(타이틀바/테두리)까지 테마가 적용됩니다.

| 베이스 클래스 | 용도 |
|---|---|
| `Office2007Form` | Office 2007/2010 스타일 일반 창 |
| `RibbonForm` | 리본을 쓰는 메인 창 |
| `MetroForm` | Metro / Windows 8 스타일 창 |
| `Form` (기본) | 테마 미적용. 컨트롤만 DotNetBar 사용 |

```csharp
using DevComponents.DotNetBar;

public partial class MainForm : Office2007Form
{
    public MainForm()
    {
        InitializeComponent();
    }
}
```

> 디자이너에서 만든 폼의 베이스 클래스를 바꿀 때는 `.cs` 와 `.Designer.cs` 양쪽이 아니라
> `.cs` 쪽 선언만 고치면 됩니다.

### 3-2. 전역 테마 — StyleManager

도구 상자에서 **StyleManager** 컴포넌트를 메인 폼에 하나 올려두면 앱 전체 테마가 통일됩니다.

```csharp
// 디자이너에서 StyleManager를 올린 뒤, 코드로 바꿀 때
StyleManager.Style = eStyle.Office2010Blue;
StyleManager.ManagerColorTint = System.Drawing.Color.SteelBlue;   // 색조 미세 조정
```

주요 `eStyle` 값: `Office2007Blue`, `Office2007Silver`, `Office2007Black`,
`Office2010Blue`, `Office2010Silver`, `Office2010Black`, `Windows7Blue`,
`Metro`, `VisualStudio2012Light`, `VisualStudio2012Dark`

### 3-3. 주요 컨트롤 대응표

일반 WinForms 컨트롤 → DotNetBar 대응:

| WinForms | DotNetBar | 비고 |
|---|---|---|
| `Button` | `ButtonX` | 색상/이미지/분할버튼/체크모드 지원 |
| `Label` | `LabelX` | HTML 태그 렌더링 지원 (`<b>`, `<font>` 등) |
| `TextBox` | `TextBoxX` | 워터마크, 버튼 임베드 |
| `ComboBox` | `ComboBoxEx` | 아이템별 이미지/설명 |
| `Panel` | `PanelEx` | 그라데이션 배경, 스타일 |
| `GroupBox` | `GroupPanel` | |
| `TabControl` | `SuperTabControl` | 탭 닫기/드래그/서브패널 |
| `TreeView` | `AdvTree` | 다중 컬럼, 셀 편집 |
| `DataGridView` | `DataGridViewX` / `SuperGrid` | `SuperGrid`가 상위 제품 |
| `ProgressBar` | `ProgressBarX`, `CircularProgress` | |
| `MessageBox` | `MessageBoxEx` | 테마 적용 메시지 박스 |
| `ToolTip` | `SuperTooltip` | 제목/본문/아이콘 |
| — | `RibbonControl` | Office 리본 |
| — | `Bar` + `DockSite` | 도킹 가능한 툴바/패널 |
| — | `SideBar`, `NavigationBar` | Outlook 스타일 내비게이션 |
| — | `SwitchButton`, `Slider`, `Rating` | |
| — | `MetroTileItem`, `MetroShell` | Metro 타일 UI |
| — | `CalendarView`, `Schedule` | 일정/간트 |

### 3-4. 코드 예제

**메시지 박스**

```csharp
using DevComponents.DotNetBar;

if (MessageBoxEx.Show(this,
        "모든 축을 원점 복귀합니다. 진행할까요?",
        "HOME",
        MessageBoxButtons.YesNo,
        MessageBoxIcon.Question) == DialogResult.Yes)
{
    StartHoming();
}
```

**HTML 텍스트를 쓰는 LabelX** — 상태 표시등처럼 쓰기 좋습니다.

```csharp
labelStatus.Text = "<b><font color=\"#C00000\">ALARM</font></b> : Axis 3 Servo Off";
```

**SuperTabControl에 탭 동적 추가**

```csharp
var tab = superTabControl1.CreateTab("Axis " + axisNo);
var panel = tab.AttachedControl;          // SuperTabControlPanel
panel.Controls.Add(new AxisMonitorControl(axisNo) { Dock = DockStyle.Fill });
superTabControl1.SelectedTab = tab;
```

**리본 버튼 이벤트**

```csharp
// 디자이너에서 RibbonControl → RibbonBar → ButtonItem 추가 후
private void buttonItemStart_Click(object sender, EventArgs e)
{
    _seqLink.SendCommand(SeqCommand.AutoStart);
}
```

**테마 런타임 전환**

```csharp
private void OnThemeChanged(eStyle style)
{
    StyleManager.Style = style;
    Properties.Settings.Default.UiStyle = (int)style;
    Properties.Settings.Default.Save();
}
```

---

## 4. SEQApp 연동 — C# MMI에서 공유 메모리 붙이기 (선택지 A 구현)

`SharedMemBase.h` 가 만드는 매핑을 C#에서 그대로 열 수 있습니다.

C++ 측 (`SEQApp/Func/SharedMemBase.h`):

```cpp
hSharedMemory = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"/SMEMORY");
if (hSharedMemory == nullptr)
    hSharedMemory = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr,
                                      PAGE_READWRITE, 0, SHALLOCSIZE, L"/SMEMORY");
pLoc = MapViewOfFile(hSharedMemory, FILE_MAP_ALL_ACCESS, 0, 0, SHALLOCSIZE);
```

C# MMI 측:

```csharp
using System.IO.MemoryMappedFiles;

const int SHALLOCSIZE = 0x40000 * 2;   // SharedMemBase.h 와 동일하게 유지

var mmf  = MemoryMappedFile.OpenExisting("/SMEMORY", MemoryMappedFileRights.ReadWrite);
var view = mmf.CreateViewAccessor(0, SHALLOCSIZE, MemoryMappedFileAccess.ReadWrite);

// SEQ가 쓰고 MMI가 읽는 영역은 뒤쪽 절반 (SHALLOCSIZE / 2 오프셋)
view.Read(SHALLOCSIZE / 2, out MmiRxHeader header);
```

구조체를 C#으로 옮길 때 **반드시** C++ 쪽 `#pragma pack(1)` 과 맞춰야 합니다:

```csharp
[StructLayout(LayoutKind.Sequential, Pack = 1)]
struct MmiRxHeader
{
    public ushort uStart;
    public ushort uCount;
    // ...
}
```

**주의사항**

- `SharedMemBase.h` / `NVMMF.h` 의 구조체가 바뀌면 C# 정의도 같이 바꿔야 합니다.
  구조체 정의를 한쪽에서 생성해 양쪽에 배포하는 방식(코드 생성 또는 공유 IDL)을 권장합니다.
- `NVMMF.h` 의 `"MMF_MAP"` 은 파일 백업 매핑(`CreateFileMapping(hFile, ...)`) 이므로
  C#에서는 `MemoryMappedFile.CreateFromFile(...)` 계열로 접근해야 합니다.
- SEQ 스레드가 `REALTIME_PRIORITY_CLASS` 로 도는 만큼, MMI 폴링 주기는 넉넉히(20~50ms) 잡고
  UI 스레드에서 직접 읽지 말고 백그라운드 스레드 → `Invoke` 로 갱신하세요.
- 32/64비트가 달라도 네임드 매핑 자체는 공유되지만, **구조체 크기가 달라지면 깨집니다.**
  `long`, 포인터, `size_t` 를 구조체에 넣지 마세요. C# MMI의 플랫폼 타깃을
  SEQApp 빌드 플랫폼(x64 또는 x86)과 맞추는 것이 안전합니다.

---

## 5. 배포 시 체크리스트

- [ ] `DevComponents.DotNetBar2.dll` 을 실행 파일과 같은 폴더에 배포 (Copy Local = True)
- [ ] `DevComponents.DotNetBar.Design.dll` 은 **디자인 타임 전용** — 배포 불필요
- [ ] `licenses.licx` 가 리소스로 임베드되어 빌드되었는지 확인
- [ ] 다국어 사용 시 `ko\DevComponents.DotNetBar2.resources.dll` 등 위성 어셈블리 포함
- [ ] 대상 PC에 해당 .NET Framework 버전 설치 확인 (보통 4.6.1 이상)
- [ ] 고해상도 장비 PC라면 DPI 설정 확인 (6장)

---

## 6. 고DPI 주의

DotNetBar은 Per-Monitor DPI 인식이 나온 시기 이전 제품이라, 최신 DPI 모드에서 레이아웃이 깨질 수 있습니다.
장비 PC가 FHD 100% 스케일이면 문제없지만, 그렇지 않다면 `app.config` 로 DPI 모드를 낮춰 고정하는 편이 안전합니다.

```xml
<configuration>
  <System.Windows.Forms.ApplicationConfigurationSection>
    <add key="DpiAwareness" value="PerMonitorV2" />   <!-- 또는 아예 미설정(System DPI) -->
  </System.Windows.Forms.ApplicationConfigurationSection>
</configuration>
```

실무적으로는 **DPI 인식을 끄고(System DPI) OS가 비트맵 스케일링하게 두는 쪽**이
장비 HMI에서는 레이아웃이 덜 깨집니다. 대신 약간 흐려집니다.

---

## 7. 자주 겪는 문제

| 증상 | 원인 / 해결 |
|---|---|
| 도구 상자에 DotNetBar 탭이 없음 | 설치 관리자가 최신 VS를 인식 못 함 → 2-2 수동 등록 |
| 실행 시 라이선스 관련 예외 | `licenses.licx` 누락/버전 불일치. 파일 삭제 후 디자이너에서 컨트롤을 다시 올려 재생성. 빌드 머신에도 DotNetBar 설치 필요 |
| 디자이너 열 때 "Could not load type" | 참조된 DLL 버전과 `licenses.licx` 안의 Version이 다름. 두 값을 일치시킬 것 |
| 폼은 테마가 적용됐는데 자식 컨트롤이 회색 | 표준 WinForms 컨트롤을 섞어 씀. DotNetBar 대응 컨트롤로 교체하거나 `PanelEx` 로 감쌀 것 |
| 한글이 잘려 보임 | DotNetBar 기본 폰트(Segoe UI/Tahoma)가 한글 폭을 못 맞춤. 폼 `Font` 를 `맑은 고딕, 9pt` 로 지정 |
| .NET 8 프로젝트로 마이그레이션 실패 | 정상. .NET Framework 전용 컴포넌트임 |
| x64 빌드에서 컨트롤이 안 보임 | 관리 어셈블리는 AnyCPU라 무관. 대부분 실제 원인은 위성 어셈블리 누락이나 DPI |

---

## 8. 대안 검토

DotNetBar은 벤더 지원이 사실상 종료되었고 .NET Framework에 묶여 있습니다.
새로 시작하는 MMI라면 아래를 함께 비교해 보길 권합니다.

| 라이브러리 | 라이선스 | .NET 8+ | 비고 |
|---|---|---|---|
| **Krypton Toolkit** | 무료 / 오픈소스 (BSD) | O | DotNetBar과 가장 성격이 비슷. 리본/도킹/네비게이터 포함 |
| **MaterialSkin.2** | 무료 / 오픈소스 (MIT) | O | Material 디자인. 장비 HMI엔 다소 캐주얼 |
| **Syncfusion Essential Studio** | Community 라이선스 무료(매출 조건) | O | 컨트롤 수 압도적 |
| **DevExpress WinForms** | 상용 | O | 산업용 HMI에서 가장 많이 쓰임 |
| **Telerik UI for WinForms** | 상용 | O | |
| **WPF + 자체 스타일** | 무료 | O | 장기적으로 가장 유연. 초기 학습 비용 있음 |

이미 DotNetBar 라이선스와 기존 화면 자산이 있다면 계속 쓰는 것도 합리적입니다.
다만 **신규 화면부터는 위 대안 중 하나로 점진 전환**하는 편이 유지보수 부담이 적습니다.

---

## 9. 참고 자료

- 설치 폴더의 `Help\DotNetBar.chm` — 공식 API 레퍼런스 (1차 출처)
- 설치 폴더의 `Samples\` — 컨트롤별 동작 예제
- [DotNetBar for Windows Forms — Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=DevCo.DotNetBarforWindowsForms)
- [방법: 구성 요소 및 컨트롤 라이선스 (Microsoft Learn)](https://learn.microsoft.com/ko-kr/previous-versions/visualstudio/visual-studio-2010/fe8b1eh9(v=vs.100))
- [도구 상자 창 (Microsoft Learn)](https://learn.microsoft.com/ko-kr/visualstudio/ide/reference/toolbox?view=vs-2022)
