/* STM32F103C8T6 GCC Linker Script */

ENTRY(Reset_Handler)

/* Memories definition */
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
    SRAM  (xrw) : ORIGIN = 0x20000000, LENGTH = 20K
}

/* Top of stack */
_estack = ORIGIN(SRAM) + LENGTH(SRAM);

/* Heap and stack size */
_Min_Heap_Size  = 0x200;   /* 512 bytes */
_Min_Stack_Size = 0x800;   /* 2 KB */

SECTIONS
{
    /* Interrupt vector */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH

    /* Program code and read-only data */
    .text :
    {
        . = ALIGN(4);
        *(.text*)
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)
        KEEP(*(.init))
        KEEP(*(.fini))
        . = ALIGN(4);
        _etext = .;
    } > FLASH

    /* ARM exception tables */
    .ARM.extab :
    {
        *(.ARM.extab*)
    } > FLASH

    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } > FLASH

    /* Initialized data */
    _sidata = LOADADDR(.data);

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > SRAM AT > FLASH

    /* Uninitialized data */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > SRAM

    /* Heap */
    .heap (NOLOAD):
    {
        . = ALIGN(8);
        _sheap = .;
        . = . + _Min_Heap_Size;
        _eheap = .;
    } > SRAM

    /* Stack */
    .stack (NOLOAD):
    {
        . = ALIGN(8);
        _sstack = .;
        . = . + _Min_Stack_Size;
        _estack_section = .;
    } > SRAM

    . = ALIGN(4);
    _end = .;

    /* Discard unused standard library sections */
    /DISCARD/ :
    {
        *(.note*)
        *(.comment*)
    }

    /* RAM overflow check */
    ASSERT(_end <= ORIGIN(SRAM) + LENGTH(SRAM), "RAM overflow!")
}