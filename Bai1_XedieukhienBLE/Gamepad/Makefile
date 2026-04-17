# ================================================
# Makefile for Xedieukhien_BLE - STM32F103
# ================================================

BUILD_DIR = Output
TARGET    = Xedieukhien_BLE

PREFIX = ./Tools/Cygwin/GNU_Arm_ToolChain/10_2021_10/bin/arm-none-eabi-

CC      = $(PREFIX)gcc
AS      = $(PREFIX)gcc
OBJCOPY = $(PREFIX)objcopy
SIZE    = $(PREFIX)size

# CPU flags
CPU = -mcpu=cortex-m3 -mthumb

# Compiler flags
CFLAGS  = $(CPU) -Wall -O0 -g3
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -std=gnu11
CFLAGS += -DSTM32F10X_MD
CFLAGS += -DUSE_STDPERIPH_DRIVER

# Linker flags
LDFLAGS  = $(CPU)
LDFLAGS += -T Linker/linker.ld
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map
LDFLAGS += -Wl,--print-memory-usage
LDFLAGS += --specs=nano.specs

# Include paths
INCLUDES = \
-IInc \
-IInc/Application \
-IInc/Ip \
-IInc/Middleware \
-ILib/STM32F10x_StdPeriph_Driver/inc \
-ILib/CMSIS/CM3/CoreSupport \
-ILib/CMSIS/CM3/DeviceSupport/ST/STM32F10x

# ==================== SOURCE FILES ====================

# Recursive wildcard function (tìm .c trong tất cả thư mục con)
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# Tìm tất cả file .c 
SRC = \
$(call rwildcard,Src,*.c) \
$(wildcard Proj/*.c) \
$(wildcard Lib/STM32F10x_StdPeriph_Driver/src/*.c) \
Lib/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c

# Startup file
STARTUP = Startup/startup_stm32f103c8.c

# Object files
OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))
OBJ += $(BUILD_DIR)/startup.o

# Output files
ELF = $(BUILD_DIR)/$(TARGET).elf
HEX = $(BUILD_DIR)/$(TARGET).hex
BIN = $(BUILD_DIR)/$(TARGET).bin

# ================================================
# Rules
# ================================================

all: $(ELF)

$(ELF): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@
	$(OBJCOPY) -O ihex $@ $(HEX)
	$(OBJCOPY) -O binary $@ $(BIN)
	$(SIZE) $@

# Compile C files (tạo thư mục tự động)
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile startup
$(BUILD_DIR)/startup.o: $(STARTUP)
	@mkdir -p $(BUILD_DIR)
	$(AS) $(CPU) -c $< -o $@

# ================================================
# Utility targets
# ================================================

clean:
	rm -rf $(BUILD_DIR)

# Flash bằng ST-LINK (dùng Cygwin path)
STLINK = ./Tools/STM32_ST-LINK_Utility/ST-LINK_Utility/ST-LINK_CLI.exe

flash: $(BIN)
	$(STLINK) -P "$(shell cygpath -w $(CURDIR))/$(BIN)" 0x08000000 -Rst

.PHONY: all clean flash