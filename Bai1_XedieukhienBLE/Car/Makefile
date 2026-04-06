# ================= TOOLCHAIN =================
BUILD_DIR = Output
TARGET    = Xedieukhien_BLE
PREFIX    = ./Tools/Cygwin/GNU_Arm_ToolChain/10_2021_10/bin/arm-none-eabi-

CC      = $(PREFIX)gcc
AS      = $(PREFIX)gcc
OBJCOPY = $(PREFIX)objcopy
SIZE    = $(PREFIX)size

# ================= MCU =================
CPU = -mcpu=cortex-m3 -mthumb

CFLAGS  = $(CPU) -Wall -O0 -g3
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -std=gnu11
CFLAGS += -DSTM32F10X_MD
CFLAGS += -DUSE_STDPERIPH_DRIVER

LDFLAGS  = $(CPU)
LDFLAGS += -TLinker/linker.ld          # <-- Đảm bảo file này tồn tại
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map
LDFLAGS += -Wl,--print-memory-usage    # <-- Thêm cái này rất hữu ích
LDFLAGS += --specs=nano.specs


# ================= INCLUDE =================
INCLUDES = \
-IInc \
-ISrc \
-IApplication \
-IBsp \
-IDriver \
-IMiddleware \
-ILib/STM32F10x_StdPeriph_Driver/inc \
-ILib/CMSIS/CM3/CoreSupport \
-ILib/CMSIS/CM3/DeviceSupport/ST/STM32F10x

# ================= SOURCES =================
SRC = \
$(wildcard Src/*.c) \
$(wildcard Application/*.c) \
$(wildcard Bsp/*.c) \
$(wildcard Driver/*.c) \
$(wildcard Middleware/*.c) \
$(wildcard Lib/STM32F10x_StdPeriph_Driver/src/*.c) \
Lib/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c

STARTUP = Startup/startup_stm32f103c8.c     # hoặc Startup/startup.c

OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))
OBJ += $(BUILD_DIR)/startup.o

BIN = $(BUILD_DIR)/$(TARGET).bin
ELF = $(BUILD_DIR)/$(TARGET).elf
HEX = $(BUILD_DIR)/$(TARGET).hex

# ================= BUILD =================
all: $(ELF)

$(ELF): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@
	$(OBJCOPY) -O ihex $@ $(HEX)
	$(OBJCOPY) -O binary $@ $(BIN)
	$(SIZE) $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/startup.o: $(STARTUP)
	@mkdir -p $(BUILD_DIR)
	$(AS) $(CPU) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

# ================= FLASH =================
STLINK = ./Tools/STM32_ST-LINK_Utility/ST-LINK_Utility/ST-LINK_CLI.exe

flash: $(BIN)
	$(STLINK) -P "$(shell cygpath -w $(CURDIR))/$(BIN)" 0x08000000 -Rst

.PHONY: all clean flash