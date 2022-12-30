	[bits 32]
	[extern start]
	[extern handle_keyboard_int]
	[extern div0Exception]
	call start
	jmp _exit__

global load_idt
load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	ret

global keyboard_handler
keyboard_handler:
	pushad
	cld
	call handle_keyboard_int
	popad
	iretd


global ioport_in
ioport_in:
	mov edx, [esp + 4]
	in al, dx
	ret

global ioport_out
ioport_out:
	mov edx, [esp + 4]
	mov eax, [esp + 8]
	out dx, al
	ret

global enable_interrupts
enable_interrupts:
	sti
	ret

global div0
div0:
	pushad
	cld
	call div0Exception
	popad
	iretd

_exit__:
	jmp $
