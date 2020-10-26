MEMORY
{
    rom (rx) : ORIGIN = 0x08000000, LENGTH = 64K
    ram (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

EXTERN(__Vectors)
ENTRY(Reset_Handler)

/* 20480 bytes = 20KB = 0x5000 */
_estack = 0x20005000;

/* Set minimum stack size */
/* Linker will generate error is not enough ram for stack */
_min_stack_size = 0x1000; /* 4096 bytes */

SECTIONS
{
    .text : 
    {
        KEEP(*(.vector_table .vector_table.*))
        *(.text*)
        . = ALIGN(4);
        *(.rodata*)
        . = ALIGN(4);
    } >rom
    /*  _sidata grabs memory section right after rodata,
        where the values for non-constant globals are
        stored. 
    */
    _sidata = .; 
    .data : AT(_sidata)
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        _edata = .;
        . = ALIGN(4);
    } >ram

    .bss : 
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } >ram

    .stack :
    {
        . = ALIGN(4);
        _sstack = .;
        . = . + _min_stack_size;
        . = ALIGN(4);
        _estack = .;
    } >ram
}