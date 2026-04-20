# Sorting Vector — Basic Test Pass/Fail Rules

## 1. Test Item Structure

`basic_test`의 각 테스트 항목은 `replay.c`에 정의된 `test_func_list item_list[]` 배열을 기반으로 한다.

```c
// common_test.h
typedef int (*CommonTestFunction)(void *ctx);

typedef struct {
    uint32_t          function_id;
    CommonTestFunction pfunc;
    const char        *function_name;
    struct test_ctx_args args;
} test_func_list;
```

`item_list[]`는 ID 1~43번 항목을 포함하며, 테스트 실행 루프(`replay.c:3193`)에서 아래와 같이 호출된다.

```c
ret = item_list[i].pfunc(&item_list[i]);
// non-zero → PASS,  0 / false → FAIL
snprintf(result_string, ..., ret ? "PASS" : "FAIL", ...);
```

---

## 2. Return Value Convention

모든 `CommonTestFunction`은 `int`를 반환하며, 실행 루프의 판정 기준은 다음과 같다.

| 반환값 | 판정 |
|--------|------|
| non-zero (`1`, `true`) | **PASS** |
| `0` / `false` | **FAIL** |
| `< 0` (음수 에러 코드) | **FAIL** (`!ret`가 false인 경우 포함) |

> 주의: `!ret`는 `ret == 0`일 때만 true이므로 음수(-EINVAL 등)는 현재 PASS로 잘못 판정될 수 있음.  
> → **음수 반환 시에도 FAIL 처리되도록 함수 내부에서 `return false`로 변환하는 것을 권장.**

---

## 2-1. Data Compare가 있는 Case

데이터 전송 후 source와 destination을 비교하는 함수들:

- `rbdma_common_test_func`, `rbdma_dram_2_shm`, `rbdma_shm_2_shm`
- `ldudma_*`, `lpudma_*`, `studma_*`
- `dram_harsh_stress_test`, `dram_all_array_test`

**규칙:** 비교 결과가 일치하면 `return 1` (PASS), 불일치 시 `return false` (FAIL).  
비교 함수(`basic_test_compare`, `memcmp` 등)의 반환값이 직접 pass/fail을 결정한다.

---

## 2-2. Data Compare가 없는 Case — 검토

데이터 비교 없이 HW 초기화 / 동작 확인만 하는 함수들:

| 함수 | 판정 기준 |
|------|-----------|
| `rdsn_config_test` | `rdsn_init()` 반환값 < 0 → FAIL |
| `tsync_test` | `posted_write_test()` 반환값 < 0 → FAIL |
| `shm_tpg_test` | `shm_init()` 반환값 < 0 → FAIL |
| `sp_tpg_test` | `dnc_sp_mode_test()`, `dnc_clear_sp_all()` 반환값 < 0 → FAIL |
| `dcl_stress_test` | 내부 stress loop 완료 여부 |
| `rbdma_report_dump` | 덤프 동작 완료 여부 |

### 검토 사항

**문제점:** 위 함수들은 하위 함수의 반환 코드만 확인하므로,  
테스트 수행 중 **비동기적으로 exception handler가 동작**하더라도 함수는 `1` (PASS)을 반환할 수 있다.

예시: `shm_tpg_test` → `shm_init()` 성공 반환 (`RL_OK`) →  
그러나 동시에 `shm_error_handler`가 single error(`intr_serr`) 감지 →  
handler 내부에서 `skip = 0` 세팅 + `[FAIL]` 로그 출력 →  
**그러나 `shm_tpg_test`는 이를 모르고 PASS 반환**

**권장 대응:**
- exception handler에서 공유 에러 플래그(`g_test_exception_flag` 등)를 세팅하고,
- data-compare 없는 테스트 함수에서 반환 직전 해당 플래그를 확인:
  ```c
  if (g_test_exception_flag)
      return false;
  return 1;
  ```

---

## 2-3. Exception Handler에 의한 FAIL 처리

테스트 동작 중 아래 exception이 발생하면 해당 테스트는 **FAIL**로 간주한다.

### 2-3-a. `shm_error_handler` (shm_if.c)

SHM exception IRQ가 발생하면 호출되는 핸들러.  
`shm_init()` 내부에서 `gic_irq_connect`로 등록된다.

| 에러 종류 | 동작 | 판정 |
|-----------|------|------|
| `intr_serr` (single error) | `skip = 0`, `[FAIL]` 로그 출력 | FAIL (비동기, 현재 미전파) |
| `intr_derr` (double error) | `[FAIL]` 로그 + `rl_abort_event(ERR_SHM)` | FAIL (즉시 abort) |
| `intr_wstt` / `intr_rstt` / `intr_malf` | `[FAIL]` 로그 출력 | FAIL (비동기, 현재 미전파) |

> `SORT_MODE`에서는 `intr_derr` 발생 시에도 `rl_abort_event` 를 호출하지 않음 (`#ifndef SORT_MODE` 조건).  
> sort mode에서는 에러를 기록하되 테스트를 계속 진행한다.

**현재 구현 한계:**  
`skip = 0`은 `shm_if.c` 내부에서만 참조되며, 테스트 함수의 return값에 반영되지 않는다.  
`intr_derr` 이상은 abort로 처리되지만, `intr_serr` 등 경미한 에러는 테스트 결과에 미반영.

### 2-3-b. `dnc_enable_exception_irq` — DNC Exception IRQ 설정 (dnc_if.c)

`dnc_task_prepare()` 에서 호출되어 DNC exception interrupt mask를 설정한다.  
non-SORT_MODE에서 더 많은 exception이 unmask되어 IRQ가 발생한다.

| 항목 | SORT_MODE | 일반(non-SORT) |
|------|-----------|----------------|
| `INTR_MASK2` (SP timeout) | masked (0x3f0000) | unmasked (0x0) |
| `INTR_MASK3` (SP_ce, DBUS_ce, CBUS_ce) | masked (0xfffffff8) | unmasked (0xffffffff) |
| `ABORT_MASK0~3` | all masked (0xffffffff) | 부분 unmasked |
| `AEH_MASK0~3` | all masked (0xffffffff) | 부분 unmasked |

DNC exception IRQ가 발생하면 해당 핸들러에서 `rl_abort_event(ERR_DNC)`가 호출될 수 있으며,  
이는 테스트 전체 abort로 이어진다 → **FAIL** 처리.

### 2-3-c. `rbdma_error_handler` (rbdma_if.c)

RBDMA error IRQ가 발생하면 호출되는 핸들러.
`rbdma_init()` 내부에서 `gic_irq_connect`로 등록된다.

| 동작 | 판정 |
|------|------|
| `ERR_INTR_FIFO` 읽어서 에러 bit별 `[FAIL]` 로그 출력 | FAIL |
| `ERR_INTR_INFO_APP0/1` 읽어서 에러 상세 정보 출력 | — |
| `rbdma_reg_dump()` → RBDMA 레지스터 전체 덤프 | — |
| `rl_abort_cur_ctx(ERR_RBDMA)` → 시스템 abort | FAIL (즉시 abort) |

핸들러는 `err_fifo.bits`의 각 에러 비트를 순회하며 에러 종류별 로그를 출력한 후,
`rl_abort_cur_ctx(ERR_RBDMA)` → `rl_abort_event(ERR_RBDMA)` → abort를 수행한다.

> `shm_error_handler`와 달리 조건부 abort가 아닌 **무조건 abort**이므로,
> 비SORT_MODE에서는 이미 테스트 중단으로 이어진다.
> SORT_MODE에서의 동작은 `rl_abort_cur_ctx` 내부 분기에 의존한다.

---

## 3. 정리: Pass/Fail 판정 흐름

```
[test function 호출]
        │
        ├─ 데이터 비교 있음 → compare 결과 → return 1 (PASS) / false (FAIL)
        │
        ├─ 데이터 비교 없음 → 하위 함수 반환값 < 0 → return false (FAIL)
        │                  └─ 성공 → (exception flag 확인 필요) → return 1 (PASS)
        │
        └─ 테스트 수행 중 exception 발생 → g_test_exception_occurred = true
                ├─ shm_error_handler (intr_serr/derr/wstt/rstt/malf)
                │       └─ flag 세팅 + (intr_derr 시 rl_abort_event)
                ├─ dnc_get_exception_intrpt_status (DNC exception IRQ)
                │       └─ flag 세팅 + rl_abort_cur_ctx(ERR_DNC)
                └─ rbdma_error_handler (RBDMA error IRQ)
                        └─ flag 세팅 + rl_abort_cur_ctx(ERR_RBDMA)
```

---

## 3-1. `replay_routine` Chiplet0 전용 호출 검토

### 호출 경로

```
[PCIe doorbell] → mailbox IRQ → mailbox_event_notify() (ISR)
    → vTaskNotifyGiveFromISR(task_handle)
    → replay_task() (FreeRTOS task, ulTaskNotifyTake)
        → process_mailbox_event()
            → replay_routine()
```

doorbell은 PCIe를 통해 **chiplet0에만** 전달되므로, `replay_routine`은 사실상 chiplet0 전용이다.

### 내부 함수별 chiplet0 보호 현황

| tc->type | 호출 함수 | chiplet0 guard | 비고 |
|----------|-----------|----------------|------|
| `DATA_TC_TYPE_STC` | `common_test_start` | ❌ 없음 | `cur_cl_id` 기반 동작, init에서 `get_chiplet_id()`로 설정 |
| `DATA_TC_TYPE_UNIT_TEST` | `basic_test_all_chiplet` | ✅ `get_chiplet_id() != 0` → return 0 | 명시적 guard 있음 |
| `DATA_TC_TYPE_UCIE_STC` | `ucie_stc_test` | ❌ 없음 | |
| `DATA_TC_TYPE_UCIE_STRESS` | `ucie_stress_test` | ❌ 없음 | |
| `DATA_TC_TYPE_UCIE_QUAD_REPLAY_TEST` | `ucie_quad_replay_test` | ❌ 없음 | |
| `DATA_TC_TYPE_UCIE_AF_STC_POWER` | `ucie_af_stc_test` | ❌ 없음 | |

### 검토 결과

`replay_routine` 자체에는 chiplet0 guard가 **없다**.
현재는 doorbell이 PCIe를 통해 chiplet0만 호출하므로 문제가 되지 않으나,
CLI 등 다른 경로에서 호출될 가능성을 방어하려면 함수 진입부에 guard를 추가하는 것을 권장:

```c
void replay_routine(void)
{
    if (get_chiplet_id() != 0) {
        printf("[ERROR] replay_routine is only allowed on chiplet0\r\n");
        return;
    }
    /* ... 기존 로직 ... */
}
```

---

## 3-2. 테스트 결과 Timeout 시나리오 검토

### 현재 문제

`replay_routine`의 tc type별 함수 호출(line 6342~6366)에서 test 함수가 hang되면
`test_result`가 영원히 반환되지 않는다. 현재 timeout 메커니즘이 **없다**.

### Hang 가능 지점

| 함수 | Hang 원인 |
|------|-----------|
| `common_test_start` → `run_common_test` | DNC/RBDMA done 대기 무한루프, HW stall |
| `basic_test_all_chiplet` → `ici_message_receive_polling` | `while (entry.message_valid != 0)` 무한 busy-wait (다른 chiplet 미응답 시) |
| `basic_test` inner loop | `rbdma_done_acc_count`, `dnc_done_accumulate_count` 등 HW completion 대기 |
| UCIE 계열 테스트 | 링크 학습 실패, 원격 chiplet 무응답 |

`ici_message_receive_polling`은 특히 위험: `mdelay(100)` 간격으로 무한 polling하며,
타 chiplet이 crash/hang된 경우 chiplet0도 함께 hang된다.

### Timeout 구현 시나리오

#### 방안 A — FreeRTOS Software Timer (권장)

테스트 함수 호출 전에 타이머를 시작하고, 타이머 만료 시 abort를 트리거한다.
기존 `rl_abort_event` 인프라를 재사용할 수 있어 구현 비용이 낮다.

```c
#include "timers.h"

#define TEST_TIMEOUT_MS    (60 * 1000)  /* 60초, tc type별 조정 가능 */

static TimerHandle_t test_timeout_timer;

static void test_timeout_callback(TimerHandle_t xTimer)
{
    g_test_exception_occurred = true;
    RLOG_ERR("[TIMEOUT] Test did not complete within %d ms\r\n",
             TEST_TIMEOUT_MS);
    rl_abort_event(ERR_UNKNOWN);
}

void replay_routine(void)
{
    /* ... 기존 파싱 로직 ... */

    /* 타이머 생성 (1회성) */
    test_timeout_timer = xTimerCreate("test_timeout",
                                       pdMS_TO_TICKS(TEST_TIMEOUT_MS),
                                       pdFALSE,  /* auto-reload 비활성 */
                                       NULL,
                                       test_timeout_callback);

    xTimerStart(test_timeout_timer, 0);

    /* tc type별 테스트 호출 */
    if (tc->type == (uint32_t)DATA_TC_TYPE_STC) {
        test_result = common_test_start(argc, argv);
    } else if (...) {
        ...
    }

    /* 정상 완료 시 타이머 취소 */
    xTimerStop(test_timeout_timer, 0);
    xTimerDelete(test_timeout_timer, 0);

    /* ... 이하 결과 처리 ... */
}
```

**장점:** FreeRTOS 기본 기능, 별도 HW 불필요, 기존 abort 인프라 활용
**단점:** `rl_abort_event`가 시스템을 halt시키므로 graceful return은 불가.
abort 대신 flag만 세팅하고, 내부 polling 루프에서 flag를 체크하는 방식으로 확장 가능.

#### 방안 B — polling 루프 내 timeout 추가 (개별 함수 수정)

각 무한 대기 지점에 timeout을 직접 추가한다.
`ici_message_receive_polling`이 대표적인 대상:

```c
/* 현재: 무한 polling */
do {
    ipm_samsung_read(...);
    polling_index++;
    mdelay(100);
} while (entry.message_valid != 0);

/* 개선: timeout 추가 */
#define ICI_POLLING_TIMEOUT_MS  (30 * 1000)
uint32_t elapsed = 0;

do {
    ipm_samsung_read(...);
    polling_index++;
    mdelay(100);
    elapsed += 100;
    if (elapsed >= ICI_POLLING_TIMEOUT_MS) {
        RLOG_ERR("[TIMEOUT] chiplet %d did not respond within %d ms\r\n",
                 tgt_cl_id, ICI_POLLING_TIMEOUT_MS);
        g_test_exception_occurred = true;
        return;  /* 또는 에러 코드 반환 */
    }
} while (entry.message_valid != 0);
```

**장점:** 정밀한 위치별 timeout 제어, graceful error return 가능
**단점:** 수정 지점이 다수 (모든 무한 대기 루프), 함수 시그니처 변경 필요할 수 있음

#### 권장 적용 순서

1. **즉시 적용 (방안 A):** `replay_routine`에 FreeRTOS timer 기반 전체 timeout.
   worst case(시스템 hang)를 일단 방어.
2. **단계적 적용 (방안 B):** `ici_message_receive_polling` 등 주요 무한 대기 루프에
   개별 timeout 추가. 이 경우 방안 A의 전체 timeout과 함께 이중 방어.

---

## 4. 개선 필요 사항 (Action Items)

1. **음수 에러 코드 처리 통일:** ✅ 완료  
   하위 함수가 음수를 반환할 때 반드시 `return false`로 변환해야 한다.  
   테스트 실행 루프가 `!ret`로 판정하므로 음수(`-EINVAL`, `-EIO`, `-1` 등)는 `!ret = 0` → 잘못된 PASS로 처리된다.

   수정된 케이스:
   - `rbdma_common_test_func`: `return -EINVAL` × 2, `return -EIO`, `return ret(-1)` → 모두 `return false`로 변경
   - `lpudma_4MB_near_sp`: `return ret` (`dnc_test_result_cmp_all` 음수 결과) → `return false`로 변경

2. **Global exception flag 도입 — exception 발생 시 test result 반영:**

   ### 배경

   `shm_error_handler`, `dnc_get_exception_intrpt_status` (DNC exception IRQ handler),
   `rbdma_error_handler`는 비동기 IRQ로 동작하므로, 테스트 함수의 return 시점과 무관하게
   언제든 호출될 수 있다.
   현재는 호출 사실이 로그에만 남으며 테스트 함수의 pass/fail 판정에 반영되지 않는다.

   **shm_error_handler 현황:**
   - `intr_serr` (single error): `[FAIL]` 로그만 출력, 테스트 결과 미반영
   - `intr_derr` (double error): `rl_abort_event(ERR_SHM)` 호출 → 시스템 abort (비SORT_MODE만)
   - `intr_wstt`, `intr_rstt`, `intr_malf`: `[FAIL]` 로그만 출력, 테스트 결과 미반영
   - **SORT_MODE에서는 `intr_derr`도 abort 없이 로그만** → 모든 에러가 결과에 미반영

   **dnc_get_exception_intrpt_status 현황:**
   - `DEFINE_DNC_EXCEPTION_IRQ_HANDLER(x)` 매크로로 생성된 핸들러(`dnc_0~15_exception_handler`)에서 호출
   - 호출 후 `rl_abort_cur_ctx(ERR_DNC)` → abort (비SORT_MODE 포함)
   - SORT_MODE에서 ABORT_MASK가 전체 masked이면 IRQ 자체가 억제될 수 있음

   **rbdma_error_handler 현황:**
   - RBDMA error IRQ 발생 시 호출 (`rbdma_init()`에서 `gic_irq_connect`로 등록)
   - `ERR_INTR_FIFO` 에러 비트별 `[FAIL]` 로그 출력 후 `rl_abort_cur_ctx(ERR_RBDMA)` → abort
   - 무조건 abort를 수행하나, SORT_MODE에서의 abort 억제 시 flag만이 유일한 결과 전파 경로

   ### 요구사항

   - data-compare 유무에 관계없이, **테스트 함수 실행 구간(시작~종료) 내에 exception handler가
     한 번이라도 호출되면 해당 테스트를 FAIL로 판정**해야 한다.
   - SORT_MODE (abort 억제)에서도 flag를 통해 에러를 수집해야 한다.

   ### 구현 시나리오

   #### Step 1 — Global flag 선언

   `common_test.h` (또는 별도 `test_exception.h`)에 선언:

   ```c
   /* global exception flag: set by shm/dnc exception handlers during test */
   extern volatile bool g_test_exception_occurred;
   ```

   `replay.c`에 정의 및 초기화:

   ```c
   volatile bool g_test_exception_occurred = false;
   ```

   #### Step 2 — `shm_error_handler`에서 flag 세팅 (shm_if.c)

   ```c
   extern volatile bool g_test_exception_occurred;

   static void shm_error_handler(void *data)
   {
       uint32_t id = (uint64_t)data;
       union shm_reg_intr_vec intr_vec;
       union shm_reg_clear clear = { 0, };

       intr_vec.bits = SHM_READ(id, ADDR_OFFSET_SHM_REG_INTR_VEC);
       RLOG_ERR("shm%d val=0x%08x\r\n", id, intr_vec.bits);

       if (intr_vec.intr_serr) {
           g_test_exception_occurred = true;  /* ← 추가 */
           RLOG_ERR("[FAIL]shm%d single error detected\r\n", id);
       }
       if (intr_vec.intr_derr) {
           g_test_exception_occurred = true;  /* ← 추가 */
           RLOG_ERR("[FAIL]shm%d double error detected\r\n", id);
       }
       if (intr_vec.intr_wstt) {
           g_test_exception_occurred = true;  /* ← 추가 */
           RLOG_ERR("[FAIL]shm%d wstt error detected\r\n", id);
       }
       if (intr_vec.intr_rstt) {
           g_test_exception_occurred = true;  /* ← 추가 */
           RLOG_ERR("[FAIL]shm%d rstt error detected\r\n", id);
       }
       if (intr_vec.intr_malf) {
           g_test_exception_occurred = true;  /* ← 추가 */
           RLOG_ERR("[FAIL]shm%d malf error detected\r\n", id);
       }
       /* ... clear, abort 로직 동일 ... */
   }
   ```

   #### Step 3a — DNC exception handler에서 flag 세팅 (dnc_if.c)

   `dnc_get_exception_intrpt_status` 진입 시점에 flag를 세팅한다.
   이 함수는 `DEFINE_DNC_EXCEPTION_IRQ_HANDLER` 매크로의 핸들러(`dnc_0~15_exception_handler`)에서
   `rl_abort_cur_ctx` 직전에 호출되므로, 함수 상단에 flag 세팅을 추가한다:

   ```c
   /* dnc_if.c — common_test.h를 이미 include하므로 별도 extern 불필요 */
   static void dnc_get_exception_intrpt_status(int dnc_id)
   {
       g_test_exception_occurred = true;  /* ← 추가: handler 진입 즉시 세팅 */

       abort_other_cores();
       /* ... 이하 기존 로직 동일 ... */
   }
   ```

   매크로 핸들러 구조 참고:
   ```c
   /* 기존 매크로 (수정 불필요 — dnc_get_exception_intrpt_status 내부에서 세팅) */
   #define DEFINE_DNC_EXCEPTION_IRQ_HANDLER(x)              \
   void dnc_ ## x ##_exception_handler(void *data)          \
   {                                                         \
       RLOG_ERR("DNC %d exception!\r\n", x);                \
       dnc_get_exception_intrpt_status(x);  /* flag 세팅 */ \
       rl_abort_cur_ctx(ERR_DNC);                           \
   }
   ```

   #### Step 3b — RBDMA error handler에서 flag 세팅 (rbdma_if.c)

   `rbdma_error_handler` 진입 시점에 flag를 세팅한다.
   RBDMA error IRQ가 발생하면 호출되며, 에러 로그 출력 후 `rl_abort_cur_ctx(ERR_RBDMA)`를 수행한다.
   `rbdma_if.c`는 `common_test.h`를 포함하지 않으므로 직접 extern 선언을 추가한다:

   ```c
   /* rbdma_if.c 상단 */
   extern volatile bool g_test_exception_occurred;

   void rbdma_error_handler(void *data)
   {
       /* ... 기존 변수 선언 ... */

       g_test_exception_occurred = true;  /* ← 추가: handler 진입 즉시 세팅 */

       abort_other_cores();
       /* ... 이하 에러 로그, reg dump, rl_abort_cur_ctx(ERR_RBDMA) 동일 ... */
   }
   ```

   #### Step 4 — 테스트 실행 루프에서 flag를 clear/check (replay.c)

   각 테스트 시작 전 flag를 clear하고, 함수 반환 후 flag를 확인한다.
   **이 방식은 모든 테스트 함수를 수정할 필요 없이** 루프 한 곳에서 일괄 적용된다.

   ```c
   /* replay.c:3185 — basic_test 실행 루프 */
   for (int i = 1; i < num_of_test; i++) {
       int cnt = 0;

       for (cnt = 0; cnt < loop; cnt++) {
           g_test_exception_occurred = false;  /* ← 테스트 시작 전 clear */

           ret = item_list[i].pfunc(&item_list[i]);

           dsb();  /* memory barrier: IRQ handler의 flag write가 가시화되도록 */

           if (g_test_exception_occurred) {  /* ← exception 발생 여부 확인 */
               RLOG_ERR("[FAIL] Exception occurred during %s\r\n",
                        item_list[i].function_name);
               ret = false;
           }

           if (!ret)
               break;
       }
       /* ... 이하 결과 출력 로직 동일 ... */
   }
   ```

   단일 테스트 실행 경로(`else` branch, replay.c:3219)도 동일하게 적용:

   ```c
   for (cnt = 0; cnt < loop; cnt++) {
       g_test_exception_occurred = false;      /* ← clear */
       test_result = item_list[idx].pfunc(&item_list[idx]);
       dsb();
       if (g_test_exception_occurred) {        /* ← check */
           RLOG_ERR("[FAIL] Exception occurred during %s\r\n",
                    item_list[idx].function_name);
           test_result = false;
       }
       if (!test_result)
           break;
   }
   ```

3. **Exception 타이밍 이슈 — 비동기 IRQ의 지연 처리:**

   ### 문제

   IRQ는 HW가 에러를 감지한 시점에 발생하지만, CPU가 실제로 핸들러를 실행하는 시점은
   현재 명령 완료 후 interrupt entry이다. 테스트 함수가 return한 직후, 루프가 `dsb()`를
   실행하기 전에 IRQ가 pending 상태일 수 있다.

   ```
   [테스트 함수 실행]
        │
        │  ← HW에서 에러 감지, IRQ pending 상태
        │
   [return]   ← 함수는 이미 PASS를 반환함
        │
   [IRQ entry] ← 핸들러 실행: g_test_exception_occurred = true 세팅
        │
   [dsb() + flag check] ← 이 시점에 flag를 읽으면 catch 가능
   ```

   ### 대응 방안

   - **`dsb()` (Data Synchronization Barrier) 삽입:** 루프에서 `pfunc` 반환 직후 `dsb()`를
     실행하면, 해당 시점까지 pending된 IRQ가 처리된 후에 flag를 읽게 된다.
     FreeRTOS + GIC 환경에서 `dsb()`는 IRQ를 즉시 서비스하도록 강제하지는 않으나,
     이미 accept된 exception handler의 write visibility는 보장한다.

   - **IRQ 우선순위 설계:** SHM/DNC exception IRQ의 우선순위가 충분히 높아
     테스트 함수 반환 직후 즉시 서비스될 수 있도록 GIC 설정을 확인한다.

   - **SORT_MODE 특수 처리:** SORT_MODE에서는 ABORT_MASK로 인해 일부 DNC IRQ가
     억제되므로, `dnc_get_exception_intrpt_status`가 호출되지 않을 수 있다.
     이 경우 flag 세팅 경로가 없으므로 SORT_MODE 전용 polling 방식(exception 레지스터
     직접 읽기)을 추가로 고려해야 한다.

   ### 타이밍 커버리지 요약

   | 시나리오 | flag catch 가능 여부 |
   |----------|----------------------|
   | 테스트 함수 실행 중 IRQ 발생 → 핸들러 완료 후 함수 return | ✅ 가능 |
   | 테스트 함수 return 직후 IRQ pending → dsb() 이전 IRQ 처리 | ✅ 가능 (dsb() 삽입 시) |
   | 테스트 함수 return 후 루프 다음 단계에서 IRQ 처리 | ❌ 불가 (이미 clear됨) |
   | SORT_MODE에서 ABORT_MASK로 IRQ 억제 | ❌ 불가 (핸들러 미호출) |
