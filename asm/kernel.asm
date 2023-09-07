[bits 32]
[extern main]
	call main 

; global load_idt
; global keyboard_handler
; global ioport_in
; global ioport_out
; global enable_interrupts
; global div0

; load_idt:
	; mov edx, [esp + 4]
	; lidt [edx]
	; ret
; 
; keyboard_handler:
	; pushad
	; cld
	; call handle_keyboard_int
	; popad
	; iretd
; 
; ioport_in:
	; mov edx, [esp + 4]
	; in al, dx
	; ret
; 
; ioport_out:
	; mov edx, [esp + 4]
	; mov eax, [esp + 8]
	; out dx, al
	; ret
; 
; enable_interrupts:
	; sti
	; ret
; 
; global div0
; div0:
	; pushad
	; cld
	; call div0Exception
	; popad
	; iretd
