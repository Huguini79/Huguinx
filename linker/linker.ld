OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

SECTIONS {
	# KERNEL
	. = 0x100000;

	# DEFINE THE SECTIONS
	.text : {*(.text)}
	.data : {*(.data)}
	.bss : {*(.bss)}
	.asm ALIGN(4096) : {
		*(.asm)
	}

}
