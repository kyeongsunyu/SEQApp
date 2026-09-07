# 전기도면 (CAD)

라인스캔 검사장비 1축 엔코더 트리거 계통 전기 결선도.
설계 근거는 `../LineScan_EncoderTrigger_HW_Design.md` (Rev.2) 참조.

## 파일

| 파일 | 내용 |
|---|---|
| `LineScan_Trigger_SH1_System.dxf` | Sheet 1 — 시스템 결선도 (전원·모션·트리거 전체 계통) |
| `LineScan_Trigger_SH2_X4_Wiring.dxf` | Sheet 2 — X4 지령/상태 결선 (아진 ↔ MBDLT25SM) |
| `LineScan_Trigger_SH3_Trigger_Chain.dxf` | Sheet 3 — 트리거 계통 (분주출력 → HPC4L → 카메라) |
| `*.svg` | 각 시트의 브라우저 미리보기 (CAD 없이 확인용) |
| `gen_dxf.py` | 도면 생성 스크립트 — 수정 시 이 파일을 고치고 재생성 |

## 사양

- **포맷**: DXF R12 ASCII (AC1009) — AutoCAD / DraftSight / LibreCAD / EPLAN 호환
- **용지**: A3 가로 (420 × 297 mm), 1 unit = 1 mm
- **레이어**

  | 레이어 | 색 | 용도 |
  |---|---|---|
  | `BORDER` / `TITLE` | 흰 | 도면틀·표제란 |
  | `COMPONENT` | 파랑 | 기기 블록 |
  | `TERMINAL` | 흰 | 단자 |
  | `WIRE_PWR` | 빨강 | AC/DC 전원 |
  | `WIRE_SIG` | 초록 | 싱글엔디드 신호 |
  | `WIRE_DIFF` | 청록 | 차동 페어 (실드 TP) |
  | `WIRE_TRIG` | 자홍 | 트리거 5V TTL |
  | `NOTE` | 노랑 | 주기 |

## ⚠️ 도면 사용 전 필수 확인

1. **핀 번호가 비어 있습니다.** Sheet 2의 `X4-__` 칸과 Sheet 3의 카메라 핀 번호는
   매뉴얼 원문 대조를 하지 못해 의도적으로 공란으로 두었습니다.
   **하네스 제작 전 반드시 채우십시오.**
2. **리니어모터 자극검출 시퀀스**를 확인하기 전에는 FASTECH Ez-ML 모듈을
   제거하지 마십시오. (설계서 R-1)

## 재생성

```bash
python3 gen_dxf.py <출력디렉토리>
```

의존성 없음 (Python 3 표준 라이브러리만 사용). 도면 문자는 ASCII로 제한했습니다 —
DXF R12는 코드페이지가 고정되지 않아 한글이 CAD 환경에 따라 깨질 수 있습니다.
