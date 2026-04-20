# 메모리 맵 (Rebel CP0 / replay_service 기준)

이 문서는 **현재 저장소의 링커 스크립트·주소 매크로**를 기준으로 정리했습니다. 
주소 체계는 **PA(물리)·VA(가상)·호스트 공유 영역**이 섞여 있으므로, 아래 **출처** 열을 함께 참고하세요.

| 출처 약어 | 의미 |
|-----------|------|
| `LD` | `osl/FreeRTOS/Source/FreeRTOS.ld` |
| `FW` | `osl/FreeRTOS/Source/services/replay_service/include/autogen/g_sysfw_addrmap.h` |
| `SYS` | `osl/FreeRTOS/Source/services/replay_service/include/autogen/g_sys_addrmap.h` (EVT0 헤더) |
| `RP` | `osl/FreeRTOS/Source/services/replay_service/include/replay.h` |
| `CT` | `osl/FreeRTOS/Source/services/replay_service/include/common_test.h` |
| `PTW` | `osl/FreeRTOS/Source/services/replay_service/include/hal/ptw.h` |

---

## 1. 링커 스크립트: FreeRTOS 펌웨어 이미지 (`FreeRTOS.ld`)

`MEMORY` 블록에 정의된 **로드/링크용 영역**입니다.
`dram0`의 **VA 시작**은 `0x10000200000`, `dram0_pa`는 **PA** `0x00000200000`로 동일 길이를 가집니다.

| 영역 이름 | 속성 | ORIGIN (시작) | LENGTH | 비고 |
|-----------|------|---------------|--------|------|
| `bl31` | !RWX | `0x0` | `0x200000` (2 MiB) | BL31 예약 |
| `dram0_pa` | RWX | `0x00000200000` | `0x10000000 - 0x400000` (= **0x0FC00000**, 252 MiB) | PA 측 텍스트 AT |
| `dram0` | RWX | `0x10000200000` | 동일 | 실행/데이터 주 배치 |
| `cs_q` | RW | `0x1000FC00000` | `0x200000` (2 MiB) | 주석: FW region 끝 2 MiB |
| `logbuf` | RWX | `0x10020000000` | `0x200000` (2 MiB) | `.logbuf` 섹션 |

### 1.1 링커에서 쓰는 크기 상수 (`FreeRTOS.ld`)

| 심볼 | 값 | 용도 |
|------|-----|------|
| `isr_stack_size` | `0x4000` | ISR 스택 (코어당 16 KiB) |
| `_stack_size` | `0x4000` | 태스크 스택 (코어당 16 KiB) |
| `mmu_page_size` | `0x1000` | 4 KiB 정렬 |
| `mmu_page_2mb` | `0x200000` | 2 MiB 정렬 |
| `dma_mcode_region_size` | `0x2000` | `.nocache_data` |
| `dma_reserved_size` | `0x1000` | `.dma_reserved` |
| `smmu_cte_size` / `smmu_cd_size` | 각 `0x1000` | SMMU CTE/CD |
| `smmu_cmdq_size` / `smmu_evtq_size` | 각 `0x8000` | SMMU 큐 |
| `dma_smmu_reserved_size` | `0x1000` | |
| `dyn_heap_size` | `0x200000` | `.dyn_heap` (2 MiB) |

### 1.2 주요 섹션 배치 (요약)

- `.text`, `.rodata`, `.data`, `.bss` → `dram0`
- `.nocache_data`, `.dma_reserved`, `.dma_smmu_region`, `.dma_smmu_reserved`, `.heap`, `.dyn_heap` → `dram0` (순서대로 누적)
- `.logbuf` → `logbuf` 메모리

`ENTRY(_start)`, `OUTPUT_ARCH(aarch64)` — ARMv8-A 64비트 이미지.

---

## 2. 시스템 FW 주소 (`g_sysfw_addrmap.h`)

DRAM/부트로더 관점의 **고정 오프셋** (일부는 BL31/CP 이미지 로드와 연동).

| 매크로 | 값 | 비고 |
|--------|-----|------|
| `DRAM_SYSTEM_MEMORY_BASE` | `0x000000000` | |
| `BL31_CP0_BASE` | `0x000000000` | |
| `FW_CP0_BASE` | `0x000200000` | CP0 FW 로드 기준 (`LD`의 `dram0_pa` 시작과 정합) |
| `PLATFORM_LOAD_IMAGE_BASE` | `0x00FE00000` | |
| `QUAD_CL_BOOTDONE_MASK` | `0x00FE00000` | |
| `LOG_BUF_BASE` | `0x020000000` | 로그 버퍼 베이스 (`rp` `logbuf_init`에서 chiplet 오프셋과 더함) |
| `DEVICE_COMMUNICATION_SPACE_BASE` | `0x010200000` | |
| `BOOTLOADER_LOG_DUMP` | `0x0102FE000` | |
| `CORE_DUMP` | `0x0102FF000` | |
| `VSERIAL` | `0x010300000` | |
| `MMU_PT_BASE` | `0x010400000` | |
| `SMMU_PCIE_PT_BASE` | `0x014000000` | |
| `BL31_CP1_BASE` | `0x014100000` | |
| `FW_CP1_BASE` | `0x014200000` | |
| `HOST_READ_ONLY_REGION_BASE` | `0x03E000000` | |
| `ROT_RESERVED_BASE` | `0x03F000000` | |
| `DRAM_USER_BASE` | `0x040000000` | |

---

## 3. 칩셋/칩렛 공간 (`g_sys_addrmap.h` — EVT0)

### 3.1 칩렛 PA (연속 128 GiB 간격)

| 매크로 | 값 |
|--------|-----|
| `REBEL_H_CHIPLET0_PHYSICAL_START` | `0x0` |
| `REBEL_H_CHIPLET0_PHYSICAL_LIMIT` | `0x2000000000` (128 GiB) |
| `REBEL_H_CHIPLET1_PHYSICAL_START` | `0x2000000000` |
| `REBEL_H_CHIPLET2_PHYSICAL_START` | `0x4000000000` |
| `REBEL_H_CHIPLET3_PHYSICAL_START` | `0x6000000000` |

`replay.c`의 `cl_base[]`는 위 칩렛 시작 주소를 사용합니다.

### 3.2 DCL SP/SHM (칩렛 기준 오프셋, `apply_cl_base`와 결합)

`common_test.h`에서 `cl_base[cur_cl_id] + 오프셋` 형태로 사용합니다.

| 매크로 (`SYS`) | 값 |
|----------------|-----|
| `DCL0_SP_MEM_BASE` | `0x1FE0000000` |
| `DCL1_SP_MEM_BASE` | `0x1FE2000000` |
| `DCL0_SH_MEM_BASE` | `0x1FE4000000` |
| `DCL1_SH_MEM_BASE` | `0x1FE6000000` |

`CT`의 테스트용 데이터 창 (칩렛 `x`):

| 매크로 | 오프셋 (칩렛 베이스 대비) |
|--------|---------------------------|
| `DATA_CMD_BASE_ADDR_CL(x)` | `+ 0x54200000` |
| `DATA_MEM_BASE_ADDR_CL(x)` | `+ 0x60000000` |
| `DATA_OUT_BASE_ADDR_CL(x)` | `+ 0x80000000` |

`MEM_DATA_SIZE` = `0x8000000`, `CMD_DATA_SIZE` = `0x20000`.

### 3.3 칩렛 간격 (소프트웨어)

| 매크로 | 값 | 출처 |
|--------|-----|------|
| `CHIPLET_INTERVAL` | `0x2000000000` (128 GiB) | `PTW` |

`replay.c` 등에서는 `CHIPLET_OFFSET` 이름으로 **동일 간격**을 사용합니다.
정의는 `portable/GCC/ARM_CA73/startup.S`에 `0x2000000000`로 있으며, **C 헤더와 동일 값**을 전제로 합니다.

---

## 4. Replay / 호스트 인터페이스 (`replay.h`)

호스트·테스트 벡터와 **HDMA** 관련 **고정 주소** (replay 루틴에서 `cpu_inv_dcache_range` 등에 사용).

| 매크로 | 값 | 설명 |
|--------|-----|------|
| `TC_INFO_ADDR` | `0x7FDF00000` | 테스트 컨트롤 `tc_info` |
| `ITER_RESULT_ADDR` | `0x7FDE00000` | 반복 결과 |
| `HDMA_DESC_BASE_ADDR` | `0x7FE000000` | HDMA descriptor 베이스 |
| `HDMA_DESC_OFFSET_INCR` | `0x100000` | 채널당 디스크립터 영역 간격 |
| `REPLAY_BASE_ADDR` | `0x780000000` | 리플레이 덤프 등 (주석: CP1 미사용, `FW_CP1_BASE` 계열) |
| `RBDMA_UCIE_STRESS_SRC/DST`(x) | `cl_base[x] + 0x600000000` / `+ 0x700000000` | UCIe stress |

### 4.1 HDMA 레지스터 (MMIO)

| 매크로 | 값 |
|--------|-----|
| `HDMA_EN_CH_WRCH_BASE` | `0x1D80380000` |
| `HDMA_DOORBELL_WRCH_TRIGGER_BASE` | `0x1D80380004` |
| `HDMA_CHANNEL_OFFSET_INCR` | `0x1000` |

채널 `idx`에 대해 `BASE + idx * 0x1000` (주석에 RDCH는 `0x800` 오프셋 등 예시).

---

## 5. 로그 버퍼 (`replay.c` / `g_sysfw_addrmap.h`)

- `LOG_BUF_BASE` = `0x020000000` (`FW`)
- chiplet `cl_id`마다 `LOG_BUF_BASE + cl_id * CHIPLET_OFFSET` (`replay` `logbuf_init`)
- 초기화 시 `SZ_2M` 범위 클리어 (코드상 `rl_sizes.h`의 `SZ_2M`)

---

## 6. 덤프/버퍼 크기 (`replay.h`)

| 매크로 | 값 |
|--------|-----|
| `TOTAL_DUMP_SIZE` | `SZ_1M * 128` (128 MiB) |
| `TOTAL_UNITS` | `4 * HW_SPEC_DNC_COUNT + 1 + 1` |
| `UNIT_DUMP_SIZE` | `(TOTAL_DUMP_SIZE / TOTAL_UNITS)` 8바이트 정렬 |

---

## 7. 정리 / 주의

1. **`FreeRTOS.ld`의 `dram0` (0x1000…)** 과 **`replay.h`의 0x7F… / 0x1D…** 은 **서로 다른 주소 공간**입니다. 전자는 링커가 배치하는 FW 이미지, 후자는 **테스트/호스트 공유·MMIO**로 보입니다 (MMU 매핑 전제).
2. **`g_sys_addrmap.h`** 는 저장소 EVT0 헤더(`_G_SYS_ADDRMAP_EVT0_H_`)입니다. EVT1 빌드 시 **autogen**이 바뀌면 이 문서의 숫자도 **같은 파일을 다시 확인**해야 합니다.
3. 링크된 **실제 심볼 배치**는 빌드 산출물 맵 파일(`*.map`)으로 검증하는 것이 가장 정확합니다.

---

## 8. 요약 표 (사용 영역 | 시작 주소 | 크기)

아래는 이 문서에서 다룬 **주요 영역**만 한눈에 본 것입니다. 주소는 **표기된 매크로/링커 정의** 기준이며, 일부는 VA/PA·MMU 매핑에 따라 달라질 수 있습니다.

| 사용 영역 | 시작 주소 | 크기 |
|-----------|-----------|------|
| BL31 (`FreeRTOS.ld` `bl31`) | `0x000000000` | 2 MiB (`0x200000`) |
| FreeRTOS 이미지 PA (`dram0_pa`) | `0x00000200000` | 252 MiB (`0xFC00000`) |
| FreeRTOS 이미지 VA (`dram0`) | `0x10000200000` | 252 MiB (`0xFC00000`) |
| `cs_q` (LD) | `0x1000FC00000` | 2 MiB |
| `.logbuf` 링커 영역 (`logbuf`) | `0x10020000000` | 2 MiB |
| 동적 힙 (`.dyn_heap`, `dyn_heap_size`) | (`.dyn_heap`에 연속 배치) | 2 MiB |
| CP0 FW 로드 기준 (`FW_CP0_BASE`) | `0x000200000` | (상한·실크기는 링커 맵 참고) |
| 로그 버퍼 chiplet별 (`LOG_BUF_BASE` + `cl_id`×`CHIPLET_OFFSET`) | `0x020000000` + 오프셋 | 2 MiB/chiplet (`SZ_2M`, `logbuf_init`) |
| 테스트 컨트롤 + 벡터 무효화 범위 (`TC_INFO_ADDR`) | `0x07FDF00000` | 32 MiB (`SZ_4M×8`, `replay_routine`) |
| 반복 결과 (`ITER_RESULT_ADDR`) | `0x07FDE00000` | 2MB |
| HDMA descriptor (`HDMA_DESC_BASE_ADDR`) | `0x07FE000000` | 2 MiB (`SZ_2M`, `replay_routine`) |
| 리플레이 덤프 베이스 (`REPLAY_BASE_ADDR` + chiplet 오프셋) | `0x0780000000` + 오프셋 | 128 MiB (`TOTAL_DUMP_SIZE`) |
| HDMA WRCH enable/doorbell MMIO (`HDMA_EN_CH_WRCH` 등) | `0x1D80380000` / `0x1D80380004` | 채널당 stride `0x1000` |
| 칩렛0 PA (`REBEL_H_CHIPLET0_PHYSICAL_START` ~ `LIMIT`) | `0x0` | 128 GiB (`0x2000000000`) |
| 칩렛1 PA | `0x2000000000` | 128 GiB |
| 칩렛2 PA | `0x4000000000` | 128 GiB |
| 칩렛3 PA | `0x6000000000` | 128 GiB |
| DCL0 SP 메모리 (`DCL0_SP_MEM_BASE`) | `0x1FE0000000` | 32 MiB (다음 경계까지; `DCL1_SP` − 시작) |
| DCL1 SP (`DCL1_SP_MEM_BASE`) | `0x1FE2000000` | 32 MiB |
| DCL0 SHM (`DCL0_SH_MEM_BASE`) | `0x1FE4000000` | 32 MiB |
| DCL1 SHM (`DCL1_SH_MEM_BASE`) | `0x1FE6000000` | 32 MiB |
| STC 입력 데이터 창 (`DATA_MEM_BASE`, chiplet 오프셋 `+0x60000000`) | `cl_base[cur]` + `0x60000000` | 128 MiB (`MEM_DATA_SIZE` `0x8000000`) |
| STC 명령 데이터 (`DATA_CMD_BASE`, `+0x54200000`) | `cl_base[cur]` + `0x54200000` | 128 KiB (`CMD_DATA_SIZE` `0x20000`) |
| STC 출력 데이터 (`DATA_OUT_BASE`, `+0x80000000`) | `cl_base[cur]` + `0x80000000` | (테스트에서 `SZ_4M×` 등과 함께 사용) |

# workload models - llama3.3 70b
| kernel | `0x40a00000` + chiplet 오프셋 | 17GB over |
| init_0 | `0x45cc00000` + chiplet 오프셋 | 220MB |
| init_1 | `0x56fc00000` + chiplet 오프셋 | 174MB |
| input_0 | `0x46a200000` | 8MB |
| input_1 | `0x57a400000` | 16KB |
| output_0 | `0x46ac00000` | 256KB |
| output_1 | `0x57a600000` | 256KB |
| 리플레이 덤프 베이스 (`REPLAY_BASE_ADDR` + chiplet 오프셋) | `0x0780000000` + 오프셋 | 128 MiB (`TOTAL_DUMP_SIZE`) |
| pt_table | `0x11800000` + chiplet 오프셋 | 40MB |
# MLperf 4종 case에서 kernel은 `0x40000000` 근처에 위치.
---

*생성 기준: `osl/FreeRTOS/Source/FreeRTOS.ld`, `replay_service/include/replay.h`, `common_test.h`, `autogen/g_sys*.h`, `hal/ptw.h`.*
