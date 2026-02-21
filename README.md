# STM32_TouchGFX-Based_Smart_Switch_Controller-SwitchBot-

STM32F429I-DISC1 보드 기반

TouchGFX GUI, FreeRTOS, RTC, 서보모터 PWM 통합 임베디드 프로젝트

터치 GUI로 물리 스위치를 제어하고,

RTC 예약 기능을 통해 지정된 시간에 자동 동작하는 스마트 스위치 시스템입니다.

---

## 프로젝트 이미지

<table>
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/6faaac99-e3c6-4650-939a-ccd28a87cea5" width="400"/>
      <br/>
      <b>MAIN_OFF</b>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/ae2fbf24-dd94-43d5-a6fe-8c87df7774dc" width="400"/>
      <br/>
      <b>MAIN_ON</b>
    </td>
  </tr>
</table>
<table>
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/f77c941b-2123-43be-bd50-6d5f87dfe63d" width="260"/>
      <br/>
      <b>TIMER_OFF</b>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/775fd939-8d5d-4b46-b7f5-6feea0c7a60c" width="260"/>
      <br/>
      <b>TIMER_SET_TIME</b>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/85425911-0c0b-4606-97ef-a0afdca6fac2" width="260"/>
      <br/>
      <b>TIMER_ON</b>
    </td>
  </tr>
</table>
<table>
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/dbebf624-42d2-4a9d-9f95-b287b5de745b" width="400"/>
      <br/>
      <b>MAIN_RTC</b>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/a0611e43-b721-4af8-8d3d-9f570f1306f6" width="400"/>
      <br/>
      <b>TIMER_RTC</b>
    </td>
  </tr>
</table>

---

## 프로젝트 개요

본 프로젝트는 **The SSEN 임베디드 스쿨** 커리큘럼에서 학습한 내용을 바탕으로,

TouchGFX GUI 프레임워크와 FreeRTOS 멀티태스킹 환경에서 하드웨어 제어를 통합·구현하기 위해 진행한 개인 프로젝트입니다.

GUI 터치 입력, RTOS 태스크 간 통신, RTC 기반 시간 관리, PWM 서보모터 제어까지

임베디드 시스템의 다양한 요소를 하나의 프로젝트로 완성하는 것을 목표로 하였습니다.

---

## 개발 환경

| 항목 | 내용 |
|------|------|
| **MCU** | STM32F429I-DISC1 (STM32F429ZIT6) |
| **Language** | C / C++ |
| **IDE** | STM32CubeIDE 1.16.0 |
| **GUI** | TouchGFX Designer 4.24.0 |
| **RTOS** | FreeRTOS (CMSIS_V2) |
| **Configuration** | STM32CubeMX (.ioc 포함) |

---

## 하드웨어 구성

| 부품 | 비고 |
|------|------|
| **STM32F429I-DISC1** | MCU + ILI9341 LCD(240×320) 내장 |
| **SG90 서보모터** | 50Hz PWM 제어 |
| **점퍼 와이어** | 서보 연결용 |

---

## 주요 기능

### 1. 터치 GUI 기반 스위치 ON/OFF 제어

- TouchGFX 기반 터치 인터페이스로 ON/OFF 버튼 조작
- 버튼 입력 시 서보모터가 물리 스위치를 올리거나 내림
- Container 기반 화면 토글로 ON/OFF 상태를 시각적으로 표시

### 2. RTC 기반 실시간 시계

- RTC를 통해 현재 시간을 실시간 갱신
- MAIN 화면과 TIMER 화면 모두에서 시계 표시
- Backup Register를 활용한 초기 시간 보존

### 3. 예약 타이머 기능

- TIMER 화면에서 시/분 설정
- ON 또는 OFF 동작 선택 후 SET 버튼으로 예약 저장
- Model::tick()에서 매초 RTC 시간과 예약 시간을 비교
- 시간 일치 시 자동으로 서보모터 동작 (1회 실행 후 비활성화)

### 4. 화면 전환 기능

- 터치 인터페이스로 MAIN 화면 <-> TIMER 화면 전환

### 5. FreeRTOS 멀티태스킹

- GUI_Task: TouchGFX 화면 렌더링 및 터치 입력 처리
- defaultTask: 서보모터 PWM 제어 전담
- 전역 플래그(`gServoOn`, `gServoOff`)를 통한 태스크 간 통신

---

## PIN MAP

| Module | Peripheral | STM32 Pin | Mode | Description |
|--------|-----------|-----------|------|-------------|
| 서보모터 (SG90) | TIM4_CH2 | PB7 | AF Push-Pull | PWM 서보 신호 출력 |
| LCD (ILI9341) | SPI5 | PF7(SCK), PF8(MISO), PF9(MOSI) | AF | LCD SPI 통신 |
| LCD CS | GPIO | PC2 | Output | LCD Chip Select |
| LCD D/C | GPIO | PD13 | Output | LCD Data/Command |
| RTC | RTC | - | Internal | 날짜 및 시간 관리 |
| 터치 입력 | LTDC + STMPE811 | I2C3 | AF | 터치스크린 입력 |
| 전원 | - | - | - | 서보 VCC(5V), GND(공통) |

---

## Peripheral Configuration Summary

### TIM4 (서보모터 PWM)

| 설정 | 값 |
|------|-----|
| Channel | CH2 (PB7) |
| Prescaler | 89 (90MHz / 90 = 1MHz) |
| Counter Period | 19999 (1MHz / 20000 = 50Hz) |
| Counter Mode | Up |
| Pulse | 1500 (1.5ms) |

### 서보모터 각도 매핑

| 동작 | Pulse 값 | 펄스 폭 | 각도 |
|------|----------|---------|------|
| ON (스위치 올림) | 500 | 0.5 ms | 0° |
| 중립 (대기) | 1500 | 1.5 ms | 90° |
| OFF (스위치 내림) | 2500 | 2.5 ms | 180° |

### RTC

- 내부 RTC 사용 (LSI 클럭)
- 24시간 형식
- Backup Register(BKP_DR0)로 초기 설정 여부 판별

### FreeRTOS

| 태스크 | Stack Size | 역할 |
|--------|-----------|------|
| GUI_Task | 8192 × 4 | TouchGFX 렌더링 + 터치 입력 |
| defaultTask | 128 × 4 | 서보모터 PWM 제어 |

---

## System Flow Diagram

### 수동 제어

```
[터치 ON 버튼]
      ↓
[MAINView::turnOn()]
(화면 전환 + gServoOn = 1)
      ↓
[defaultTask 감지]
      ↓
[서보 0° 이동]
      ↓
[1초 대기]
      ↓
[서보 90° 복귀]
```

### 예약 제어

```
[TIMER 화면]
      ↓
[시/분 설정 + ON/OFF 선택]
      ↓
[SET 버튼 → gSchedule 저장]
      ↓
[Model::tick() 매초 RTC 비교]
      ↓
[시간 일치 → gServoOn 또는 gServoOff = 1]
      ↓
[defaultTask → 서보 동작]
      ↓
[gSchedule.active = 0 (1회 실행 후 비활성화)]
```

---

## 프로젝트 구조

```
SwitchBot/
├── Core/Src/
│   └── main.c                          # 타이머/PWM 초기화, FreeRTOS 태스크
│
├── TouchGFX/gui/
│   ├── include/gui/
│   │   ├── common/
│   │   │   └── TimerSchedule.hpp       # 예약 데이터 구조체
│   │   ├── main_screen/
│   │   │   ├── MAINView.hpp
│   │   │   └── MAINPresenter.hpp
│   │   ├── timer_screen/
│   │   │   ├── TIMERView.hpp
│   │   │   └── TIMERPresenter.hpp
│   │   └── model/
│   │       ├── Model.hpp
│   │       └── ModelListener.hpp
│   └── src/
│       ├── main_screen/
│       │   ├── MAINView.cpp            # ON/OFF GUI + 서보 플래그 세팅
│       │   └── MAINPresenter.cpp
│       ├── timer_screen/
│       │   ├── TIMERView.cpp           # 예약 시간 설정 + gSchedule
│       │   └── TIMERPresenter.cpp
│       └── model/
│           └── Model.cpp               # RTC 읽기 + 예약 시간 체크
│
├── TouchGFX/generated/                 # TouchGFX Designer 자동 생성
├── Middlewares/ST/touchgfx/            # TouchGFX 라이브러리
└── STM32CubeIDE/                       # IDE 프로젝트 설정
```

---

## 트러블슈팅

## 트러블슈팅

| # | 문제 | 원인 | 해결 |
|---|------|------|------|
| 1 | `main()` while문에 작성한 HAL 함수 미실행 | FreeRTOS `osKernelStart()` 이후 while문 도달 불가 | `StartDefaultTask` 태스크 내부로 코드 이동 |
| 2 | TIM2 활성화 시 LCD 흰색 화면 | TIM2 핀이 LCD/SDRAM(FMC)과 하드웨어 충돌 | 충돌 없는 TIM4 CH2 (PB7)로 변경 |
| 3 | CubeMX Generate 후 PWM Init 코드 누락 | Channe2이 PWM Generation으로 설정되지 않음 | PWM Generation CH 재선택 + Internal Clock 체크 후 재생성 |
| 4 | 서보가 한쪽으로만 계속 회전 | TIM Counter Mode가 Down (듀티 반전) | Counter Mode를 Up으로 변경 |
| 5 | 서보가 멈추지 않고 반복 동작 | for 루프에 osDelay 없어 CPU 100% 점유 | 루프 끝에 `osDelay(10)` 추가 |
| 6 | 서보 회전 각도가 매우 좁음 | Pulse 1000~2000 범위 사용 (이론값) | SG90 실측 기반 500~2500으로 확장 |
| 7 | GUI 태스크에서 서보 제어 시 화면 멈춤 | TouchGFX 태스크 내 osDelay로 GUI 블로킹 | 전역 플래그로 별도 태스크에 서보 제어 위임 |
---

## 요약

STM32F429I-DISC1 기반으로 **TouchGFX GUI, FreeRTOS, RTC, PWM 서보모터 제어**를 통합하여

터치 인터페이스로 물리 스위치를 제어하고, 예약 타이머로 자동화하는 스마트 스위치 컨트롤러를 구현한 프로젝트입니다.

TouchGFX 프레임워크를 통한 직관적인 GUI 설계, FreeRTOS 멀티태스킹 환경에서의 태스크 간 통신,

RTC 기반 실시간 예약 시스템, 그리고 PWM 서보모터의 정밀 제어까지

임베디드 시스템의 핵심 동작 흐름을 하나의 프로젝트로 완성하였습니다.
