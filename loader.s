.set MAGIC, 0x1badb002; #Bootloader will not recognize the kernel without the magic number which is a hex number: 0x1BADB002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot ;# put this in the .o file
	.long MAGIC
	.long FLAGS
	.long CHECKSUM

.section .text
.extern kernelMain; #Here I tell the assembler that there is going to be a function called kernalmain (in kernel.cpp) we tell the assembler that the linker will take care of it
.extern callConstructors
.global loader

loader:
	mov $kernel_stack, %esp; #set the stack pointer to some pointer to some stack; esp stands for 32 bit stack pointer
	
	call callConstructors

	push %eax ; #Bootloader creates a structure and creates a pointer to the structure in the Ax register; quick note 16 bit register have ax and bx while 32 bit registers denote it as eax and ebx registers
	push %ebx ; #It copies the magic number to the Bx register
	call kernelMain; # currently it should be in an infinite loop because of the while(true) function since we do not want to the kernel's processes to stop

_stop:
	cli; #these 4 lines of code is to ensure that the kernel remains in an infinite loop, clear interrupt flag, interrupt halt state
	hlt
	jmp _stop

.section .bss
.space 2*1024*1024; #2 megabytes of space, since stack is pushed left we don't want overrite any data this blank space acts as a buffer
kernel_stack: ;#this is the pointer we set the esp register to