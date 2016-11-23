/* Linker script for Simple_OS on ARM Beagleboard */ 

/* Based on information available at http://balau82.wordpress.com/ */ 

/* fig_begin link_ld */ 
ENTRY(start)
SECTIONS
{
 . = 0x80000000; 
 .startup . : { obj/startup_arm_bb.o(.text) }
 .text : { *(.text) }
 .data : { *(.data) }
 .bss : { *(.bss) }
 . = . + 0x5000; 
 stack_bottom = .;
}
/* fig_end link_ld */ 
