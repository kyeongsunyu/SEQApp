# 라인스캔 검사장비 — 1축 엔코더 트리거 하드웨어 설계서

| 항목 | 내용 |
|---|---|
| 대상 | 신규 라인스캔 검사장비 (1축 스캔) |
| 서보 드라이버 | Panasonic **MBDLT25SM** (MINAS A6S 계열, 400W, 200–240V) |
| 이송 기구 | 리니어모터 + 리니어스케일 |
| 트리거 모듈 | Ajinextek **SIO-HPC4L** (엔코더 4CH, 고속 차동 입력 ~5 MHz) |
| 위치 피드백원 | 서보 드라이버 X4 분주 출력 (OA/OB/OZ) |
| 트리거 피치 | **5.0 µm** |
| 트리거 출력 | 5 V TTL (push-pull) → 카메라 Trigger IN |

---

## 0. 착수 전 확인 필수 — 설계 전제를 무너뜨릴 수 있는 항목

### R-1. MBDLT25SM의 리니어모터(full-closed) 지원 여부 — **최우선**

- `MBDLT25S**F**` = MINAS A6S 400W 로 확인됨. **`SM` 서픽스는 확인하지 못함.**
- Panasonic 자료상 **A6SE / A6SG 계열은 full-closed 제어를 지원하지 않음.**
- 리니어모터 + 리니어스케일 구성은 스케일이 유일한 위치 피드백이므로 **full-closed(리니어) 제어가 필수**.

> **미지원 모델이면 이 설계 전체가 성립하지 않습니다.** 드라이버 교체 또는 회전형 + 볼스크류로 기구 변경이 필요합니다.
> Panasonic 기술지원에 정확한 모델 코드로 ① 리니어모터 구동 지원 ② full-closed 제어 지원 ③ 분주 출력 소스로 external scale 선택 가능 여부를 확인하십시오.

### R-2. X4 커넥터 핀 번호

본 설계서의 X4 핀 번호는 MINAS A5/A6 일반 배열을 근거로 한 것으로, **원문 매뉴얼로 대조하지 못했습니다.** 배선 전 반드시 해당 모델 매뉴얼의 X4 핀 배치도로 확인하십시오.

### R-3. 카메라 Control I/O 핀 배열

카메라측 `pin 1 = Trigger IN`, `pin 3 = DC GND` 역시 매뉴얼 원문 대조가 필요합니다. 오결선 시 입력단 CMOS 버퍼가 손상될 수 있습니다.

---

## 1. 시스템 구성

```
 [리니어스케일]
       │ (RS-422 차동 A/B/Z)
       ▼
 [MBDLT25SM]  X5 : 외부 스케일 입력 (EXA/EXB/EXZ 또는 시리얼)
       │        └ 서보는 스케일을 위치 피드백으로 사용 (full-closed)
       │
       │ X4 : 분주 출력 (Pulse Regeneration)
       │      출력 소스 = external scale  ★
       ▼ OA±/OB±/OZ± (라인드라이버, 최대 4 Mpps)
 [SIO-HPC4L]  고속 차동 입력 → 4체배 → 32bit 카운터
       │      periodic mode : 카운터가 피치에 도달할 때마다 HW 자동 펄스
       ▼ TRIG OUT (5 V TTL push-pull)
 [라인스캔 카메라]  Control I/O pin1 Trigger IN / pin3 GND
```

### 이 구성이 유효한 이유

리니어모터에서는 **모터 위치 = 리니어스케일 위치**입니다. 따라서 X4 분주 출력의 소스를 external scale로 두면, 스케일을 HPC4L에 직결한 것과 **위치 정확도가 동등**합니다.

(볼스크류 구성이었다면 X4 분주 출력은 모터축 기준이라 리드오차·백래시·열팽창이 트리거 위치에 그대로 실려 스케일 직결이 필수였을 것입니다. 리니어모터라 이 문제가 없습니다.)

**단, 분주 출력 소스가 encoder가 아니라 external scale로 설정되어야 합니다.** 파라미터 확인 항목입니다.

---

## 2. 라인스캔은 TDI보다 훨씬 관대합니다 — 정밀도 목표 설정

기존 TDI 장비(VT-16K5X, 256단)와 신규 라인스캔의 피치 오차 영향은 **완전히 다릅니다.**

| | TDI 256단 | 라인스캔 (N=1) |
|---|---|---|
| 피치 오차 ε의 영향 | **smear = 256 × ε** (화질 붕괴) | 이미지 종횡비 오차 = ε |
| ε = 1 % 일 때 | 2.56 px 뭉갬 | 100 px당 1 px 신축 |
| 허용 ε | **0.2 %** | 용도에 따라 **0.5 ~ 2 %** |

- **외관 검사만** → ε 2 % 이내면 실용상 무해
- **치수 측정 병행** → ε 0.2 % 이내 필요

아래 설계표는 이 목표에 따라 UPP를 고르도록 구성했습니다.

---

## 3. 수치 설계

### 3.1 제약 조건 3가지

| # | 제약 | 값 |
|---|---|---|
| C-1 | 트리거 피치가 **정수 엔코더 카운트** | `5.0 µm / UPP = 정수` |
| C-2 | 드라이버 분주 출력 상한 | **4 Mpps** |
| C-3 | HPC4L 차동 입력 상한 | **5 MHz** |

→ 실질 병목은 **C-2 (드라이버 4 Mpps)** 입니다.

### 3.2 UPP 후보 설계표

`UPP` = 4체배 후 1 카운트당 거리 · `f_A` = A상 분주 출력 주파수 = `v / (4 × UPP)`

| UPP | 5 µm의 카운트 | 피치 조정 스텝 (=ε 분해능) | A상 주기거리 | f_A @300 mm/s | @500 mm/s | @800 mm/s |
|---|---|---|---|---|---|---|
| 0.5 µm | 10 | 10 % | 2.0 µm | 150 kHz | 250 kHz | 400 kHz |
| 0.25 µm | 20 | 5 % | 1.0 µm | 300 kHz | 500 kHz | 800 kHz |
| 0.1 µm | 50 | 2 % | 0.4 µm | 750 kHz | 1.25 MHz | 2.0 MHz |
| **0.05 µm** | **100** | **1 %** | 0.2 µm | 1.5 MHz | **2.5 MHz** | 4.0 MHz ⚠ |
| 0.025 µm | 200 | 0.5 % | 0.1 µm | 3.0 MHz | 5.0 MHz ❌ | ❌ |
| 0.01 µm | 500 | 0.2 % | 0.04 µm | 7.5 MHz ❌ | ❌ | ❌ |

### 3.3 권장안

| 용도 | 권장 UPP | 피치 카운트 | 비고 |
|---|---|---|---|
| **외관 검사 (기본 권장)** | **0.1 µm** | 50 | f_A 여유 3.2배 @500 mm/s. 안정적 |
| 치수 측정 병행 | 0.025 µm | 200 | ε 0.5 %. **최고속 300 mm/s로 제한됨** |

**기본 권장: UPP = 0.1 µm.** 피치 = 정확히 50 카운트로 떨어지고, 500 mm/s에서 분주 출력 1.25 MHz로 4 Mpps 대비 충분한 여유가 있습니다.

### 3.4 속도 상한

```
v_max = 카메라 라인레이트 × 5.0 µm
```

| 카메라 라인레이트 | v_max | UPP 0.1 µm일 때 f_A |
|---|---|---|
| 50 kHz | 250 mm/s | 625 kHz ✅ |
| 100 kHz | 500 mm/s | 1.25 MHz ✅ |
| 150 kHz | 750 mm/s | 1.88 MHz ✅ |
| 200 kHz | 1,000 mm/s | 2.5 MHz ✅ |

UPP 0.1 µm면 카메라가 200 kHz여도 드라이버 4 Mpps 안에 들어옵니다.

> 오버트리거(트리거가 카메라 라인주기보다 빨리 도착)는 라인 누락 → 이미지 압축으로 나타납니다. 속도 리플·오버슈트를 고려해 **v_max에 20~30 % 마진**을 두십시오.

---

## 4. 결선

### 4.1 드라이버 X4 → SIO-HPC4L (엔코더 입력)

| 신호 | X4 핀 (※R-2 대조 필요) | HPC4L |
|---|---|---|
| OA+ | 21 | ENC A+ |
| OA− | 22 | ENC A− |
| OB+ | 48 | ENC B+ |
| OB− | 49 | ENC B− |
| OZ+ | 23 | ENC Z+ |
| OZ− | 24 | ENC Z− |
| SG (신호 GND) | 25 | GND |

- **실드 트위스트 페어 3쌍** (A쌍 / B쌍 / Z쌍), 실드는 드라이버측 1점 접지
- 차동 전송이므로 노이즈 내성 양호. 서보 전력선과는 분리 배선
- Z상은 원점 복귀용. 스캔 트리거에는 사용하지 않으나 배선해 두면 원점 재현성 확보에 유리

### 4.2 SIO-HPC4L → 카메라 (트리거 출력)

| HPC4L | 카메라 Control I/O (※R-3 대조 필요) |
|---|---|
| TRIG OUT 0 | pin 1 — Trigger IN |
| GND | pin 3 — DC GND |

- 5 V TTL push-pull ↔ 카메라 V_IH 2~5 V → **레벨 호환. 풀업 불필요**
- **케이블 1 m 초과 시 출력단에 직렬 33~47 Ω** (반사·링잉 억제). 링잉이 입력 임계값을 넘나들면 1펄스가 2펄스로 카운트됩니다
- 실드 트위스트 페어, 2 m 이내 권장
- 접지 전위차가 우려되면 **고속 포토커플러(6N137급, ~10 Mbps) 절연**. 일반 포토커플러는 응답이 느려 사용 불가

---

## 5. 서보 드라이버 파라미터

| 파라미터 | 설정 | 목적 |
|---|---|---|
| 제어 모드 | full-closed (리니어) | 스케일 기반 위치 제어 |
| 분주 출력 소스 | **external scale** | X4 출력이 스케일 위치를 반영 ★ |
| Pr0.11 (출력 펄스 수) | UPP 목표에 맞춰 산출 | 3.2절 표 참조 |
| Pr0.12 (출력 방향 반전) | 스캔 방향에 맞춰 | HPC4L `AxcSignalSetEncReverse`로도 대응 가능 |

> **Pr0.11은 "모터 1회전당 출력 펄스 수"로 정의된 회전형 기준 파라미터입니다.** 리니어모터/full-closed 구성에서 분주비가 어떤 파라미터로 결정되는지는 해당 모델 매뉴얼에서 확인해야 합니다. 스케일 펄스를 무분주로 그대로 출력하는 것이 가장 단순하고 오차가 없으므로, 가능하다면 그 방식을 우선 검토하십시오.

### 스캔 프로파일

```
가속 → 속도 정정(settling) → [트리거 구간 진입] → 등속 스캔 → [구간 이탈] → 감속
```

트리거 Block 구간을 등속 구간 안쪽으로 설정하고, 진입 전 정정이 끝나도록 조주 거리를 확보하십시오.

---

## 6. SIO-HPC4L 설정 (periodic mode)

버퍼를 사용하지 않는 하드웨어 위치주기 트리거입니다. 트리거 개수 제한이 없습니다.

```cpp
AxcTriggerSetEnable       (ch, 0);          // 설정 중 출력 정지
AxcTriggerSetEncoderInput (ch, encInput);   // 엔코더 입력 0~3
AxcSignalSetEncInputMethod(ch, 0x03);       // A/B상 4체배
AxcSignalSetEncSource     (ch, 0x00);       // A/B상 신호
AxcSignalSetEncReverse    (ch, bReverse);   // 진행 방향

AxcMotSetMoveUnitPerPulse (ch, 0.0001);     // UPP = 0.1 um = 0.0001 mm
AxcTriggerSetFunction     (ch, 0x03);       // ★ periodic mode (위치 주기)
AxcTriggerSetBlock        (ch, start, end, 0.005);  // 구간 + 피치 5 um
AxcTriggerSetDirectionCheck(ch, 0x01);      // 증가 방향에서만

AxcTriggerSetTriggerOutport(ch, 0x1);       // Trigger Out 0
AxcTriggerSetTime          (ch, 2.0);       // 펄스 폭 2 us  (카메라 최소 1 us)
AxcTriggerSetLevel         (ch, 1);         // High active
AxcTriggerSetTriggerOutCount(ch, 1);        // 주기당 1발

AxcTriggerSetTriggerCountClear(ch);
AxcTriggerSetEnable           (ch, 1);      // 활성화
```

스캔 시작 전 원점: `AxcStatusSetActPos(ch, 0.0)`
정지: `AxcTriggerSetEnable(ch, 0)`

카메라측 대응 설정:
- `Trigger Mode` = On
- `Trigger Source` = External
- `Trigger Activation` = **Rising Edge** (High active + push-pull이므로 반전 없음)

> `AxcTriggerSetFunction` periodic mode(0x03)와 `SetBlock`/`SetPosPeriod`는 AXC 헤더에 SIO-HPC4 전용으로 명시되어 있어 확실합니다.
> `AxcTriggerSetTriggerOutCount` / `AxcTriggerReadTriggerCount`는 헤더상 SIO-HPC4 명시가 없어 **지원 여부 확인이 필요**합니다.

---

## 7. 검증 절차

### V-1. 분주 출력 확인 (배선 직후)
드라이버 X4 OA/OB를 스코프 차동 프로브로 관측. 축을 알려진 거리 D만큼 이동시켜 펄스 수를 세고 `D / 펄스수`가 설계 UPP와 일치하는지 확인.

### V-2. 카운터 검증
```cpp
AxcStatusSetActPos(ch, 0.0);
// 축을 정확히 100 mm 이동
AxcStatusGetActPos(ch, &pos);   // 100.000 mm 가 나와야 함
```
어긋나면 UPP 또는 분주 설정이 틀린 것입니다.

### V-3. 트리거 개수 검증 — **가장 중요**
```cpp
AxcTriggerSetTriggerCountClear(ch);
// 스캔 200 mm 실행
AxcTriggerReadTriggerCount(ch, &n);   // 200mm / 5um = 40,000 이어야 함
```
실제 피치 = 이동거리 / n. 설계값과의 차이가 곧 ε입니다.
(API 미지원 시 카메라 Strobe OUT 또는 HPC4L 트리거 출력선을 카운터로 계수)

### V-4. 트리거 인식 확인
HPC4L 트리거 출력과 카메라 **Strobe OUT(pin 4)** 을 스코프 2채널로 동시 관측. 펄스 누락·중복이 바로 보입니다. 속도를 단계적으로 올리며 최고속까지 누락이 없는지 확인.

### V-5. 이미지 검증
격자 타깃 스캔 → 스캔 방향/어레이 방향 치수비 비교로 종횡비 오차 실측.

---

## 8. 미확정 항목

| # | 항목 | 영향 | 필요 조치 |
|---|---|---|---|
| 1 | **MBDLT25SM 리니어모터/full-closed 지원** | **설계 성립 여부** | Panasonic 기술지원 확인 |
| 2 | 리니어스케일 모델·분해능·출력 형식 | UPP 확정 | 스펙 확보 |
| 3 | 라인스캔 카메라 모델·라인레이트 | v_max 확정 | 선정 |
| 4 | 광학 배율 M (피치 5 µm의 근거) | 피치 미세보정 | 캘리브레이션 타깃 실측 |
| 5 | 리니어모터 최대속도·스트로크 | 택트 산출 | 스펙 확보 |
| 6 | 스캔 길이 / 요구 택트 | 속도 목표 | 사양 확정 |
| 7 | 리니어모터 full-closed 분주비 파라미터 | 파라미터 설정 | 매뉴얼 확인 |
| 8 | X4 / 카메라 Control I/O 핀 배열 | 오결선 위험 | 매뉴얼 대조 |

**1번이 해결되기 전에는 부품 발주를 진행하지 마십시오.**

---

## 부록. 기존 TDI 장비 대비 개선점

기존 VT-16K5X-H140A-256 장비의 블러 원인 조사에서 확인된 사항을 신규 설계에 반영했습니다.

| 기존 문제 | 신규 설계 대응 |
|---|---|
| 위치 동기 트리거 경로 미구현 (`CAjinTrigger` 미인스턴스화) | periodic mode로 하드웨어 트리거 경로 명시 |
| 소프트웨어 `Sleep(100)` 토글 트리거 | HW 위치주기 비교기 — 소프트웨어 개입 없음 |
| `StartTrigger()` 최대 10발 (버퍼 오버플로 존재) | 버퍼 미사용 — 트리거 개수 무제한 |
| 피치 양자화 미검토 | UPP를 피치의 정수 약수로 설계 단계에서 확정 |
| 트리거 펄스 폭 미확인 | 2 µs 명시 (카메라 최소 1 µs) |
| 엔코더 전송 노이즈 내성 | 차동(HPC4L) 채택 |
