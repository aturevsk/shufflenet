# ==================================================================
#  Makefile — ShuffleNet V2 1.0x for STM32F746G-Discovery
#
#  Targets:
#    make host         Build for host (x86/ARM Mac/Linux) — testing
#    make arm          Build for STM32F746G (ARM Cortex-M7) — deployment
#    make clean        Remove all build artefacts
#    make run          Build and run on host
#    make size         Show ARM binary size breakdown
#
#  Prerequisites:
#    Host : gcc or clang
#    ARM  : arm-none-eabi-gcc (GNU Arm Embedded Toolchain)
# ==================================================================

# ---- Project files ------------------------------------------------
SRCS       = shufflenet_v2.c main.c
HEADERS    = shufflenet_v2.h

# ---- Output names -------------------------------------------------
HOST_BIN   = shufflenet_v2_host
ARM_BIN    = shufflenet_v2_arm
ARM_ELF    = $(ARM_BIN).elf
ARM_HEX    = $(ARM_BIN).hex
ARM_MAP    = $(ARM_BIN).map

# ---- Build directory ----------------------------------------------
BUILD_DIR  = build
HOST_DIR   = $(BUILD_DIR)/host
ARM_DIR    = $(BUILD_DIR)/arm

# ==================================================================
#  Host build (gcc / clang)
# ==================================================================

HOST_CC    = gcc
HOST_CFLAGS = \
    -std=c99 \
    -Wall -Wextra -Wpedantic \
    -O2 \
    -g \
    -DHOST_BUILD=1 \
    -ffast-math \
    -march=native

HOST_LDFLAGS = -lm

# ==================================================================
#  ARM cross-compilation (STM32F746G-Discovery)
# ==================================================================

ARM_CC     = arm-none-eabi-gcc
ARM_OBJCOPY = arm-none-eabi-objcopy
ARM_SIZE   = arm-none-eabi-size

# Cortex-M7 with single-precision FPU
ARM_CPU    = -mcpu=cortex-m7
ARM_FPU    = -mfpu=fpv5-sp-d16 -mfloat-abi=hard
ARM_ARCH   = -mthumb $(ARM_CPU) $(ARM_FPU)

# STM32F746 HAL/CMSIS include paths (adjust to your SDK installation)
STM32_SDK  ?= /opt/STM32CubeF7
CMSIS_INC  = $(STM32_SDK)/Drivers/CMSIS/Include
DEVICE_INC = $(STM32_SDK)/Drivers/CMSIS/Device/ST/STM32F7xx/Include
HAL_INC    = $(STM32_SDK)/Drivers/STM32F7xx_HAL_Driver/Inc

# Linker script (board-specific; adjust path as needed)
LDSCRIPT   ?= STM32F746NGHx_FLASH.ld

ARM_CFLAGS = \
    -std=c99 \
    -Wall -Wextra \
    -O2 \
    -g \
    $(ARM_ARCH) \
    -DSTM32F746xx \
    -DUSE_HAL_DRIVER \
    -I$(CMSIS_INC) \
    -I$(DEVICE_INC) \
    -I$(HAL_INC) \
    -ffunction-sections \
    -fdata-sections \
    -ffast-math \
    -fno-common \
    --specs=nano.specs

ARM_LDFLAGS = \
    $(ARM_ARCH) \
    -T$(LDSCRIPT) \
    -Wl,--gc-sections \
    -Wl,-Map=$(ARM_DIR)/$(ARM_MAP) \
    --specs=nano.specs \
    --specs=nosys.specs \
    -lm \
    -lc

# ==================================================================
#  Targets
# ==================================================================

.PHONY: all host arm clean run size help

all: host

help:
	@echo "ShuffleNet V2 1.0x Build System"
	@echo ""
	@echo "Targets:"
	@echo "  make host     Build for host (testing)"
	@echo "  make arm      Build for STM32F746G (deployment)"
	@echo "  make run      Build and run on host"
	@echo "  make clean    Remove build artefacts"
	@echo "  make size     Show ARM binary size"
	@echo ""
	@echo "Variables:"
	@echo "  STM32_SDK     Path to STM32CubeF7 SDK (default: /opt/STM32CubeF7)"
	@echo "  LDSCRIPT      Linker script path (default: STM32F746NGHx_FLASH.ld)"

# ---- Host build ---------------------------------------------------

host: $(HOST_DIR)/$(HOST_BIN)

$(HOST_DIR)/$(HOST_BIN): $(SRCS) $(HEADERS) | $(HOST_DIR)
	$(HOST_CC) $(HOST_CFLAGS) -o $@ $(SRCS) $(HOST_LDFLAGS)
	@echo ""
	@echo "==> Host binary built: $@"
	@echo "    Run with: $@ [weights.bin]"

$(HOST_DIR):
	mkdir -p $(HOST_DIR)

# ---- ARM build ----------------------------------------------------

arm: $(ARM_DIR)/$(ARM_ELF) $(ARM_DIR)/$(ARM_HEX)

$(ARM_DIR)/$(ARM_ELF): $(SRCS) $(HEADERS) | $(ARM_DIR)
	$(ARM_CC) $(ARM_CFLAGS) -o $@ $(SRCS) $(ARM_LDFLAGS)
	@echo ""
	@echo "==> ARM ELF built: $@"

$(ARM_DIR)/$(ARM_HEX): $(ARM_DIR)/$(ARM_ELF)
	$(ARM_OBJCOPY) -O ihex $< $@
	@echo "==> ARM HEX built: $@"

$(ARM_DIR):
	mkdir -p $(ARM_DIR)

# ---- Run on host --------------------------------------------------

run: host
	@echo ""
	@echo "--- Running ShuffleNet V2 on host ---"
	$(HOST_DIR)/$(HOST_BIN)

# ---- Size report (ARM) --------------------------------------------

size: $(ARM_DIR)/$(ARM_ELF)
	@echo ""
	@echo "--- ARM Binary Size ---"
	$(ARM_SIZE) -A -d $<
	@echo ""
	$(ARM_SIZE) -B -d $<

# ---- Clean --------------------------------------------------------

clean:
	rm -rf $(BUILD_DIR)
	@echo "Build directory cleaned."
