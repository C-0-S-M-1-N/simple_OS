[org 0x7c00]
[bits 16]
; [extern _start]
BOOTLOADER_LOCATION equ 0x1000

mov [BOOT_DISK], dl


mov     ax,2403h
int     15h
jb      disk_error
cmp     ah,0
jnz     disk_error
 
mov     ax,2402h
int     15h
jb     	disk_error 
cmp     ah,0
jnz     disk_error 


xor ax, ax

int 0x13

jc disk_error

mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp

mov bx, BOOTLOADER_LOCATION
mov dh, 20

mov ah, 0x02
mov al, dh
mov ch, 0x00
mov dh, 0x00
mov cl, 0x01
mov dl, [BOOT_DISK]
int 0x13

jc disk_error

;mov ah, 0x00
;mov al, 0x03
;int 0x10


CODE_SEG equ GDT_code - GDT_start
DATA_SEG equ GDT_data - GDT_start

cli
lgdt [GDT_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEG:start_protected_mode

disk_error:
	mov cl, ah	
	mov ah, 0x0e
	cmp cl, 0x0c
	je err1
	jmp else
err1:
	mov al, '1'
	jmp endif
else:
	mov al, '?'
endif:
	int 0x10


BOOT_DISK: db 0

GDT_start:
	GDT_null:
		dd 0x0
		dd 0x0
	GDT_code:
		dw 0xffff
		dw 0x0
		db 0x0
		db 0b10011010
		db 0b11001111
		db 0x0
	
	GDT_data:
		dw 0xffff
		dw 0x0
		db 0x0
		db 0b10010010
		db 0b11001111
		db 0x0
GDT_end:

GDT_descriptor:
	dw GDT_end - GDT_start - 1
	dd GDT_start

[bits 32]
start_protected_mode:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ebp, 0x90000
	mov esp, ebp
	jmp BOOTLOADER_LOCATION



times 510-($-$$) db 0
db 0x55, 0xaa
