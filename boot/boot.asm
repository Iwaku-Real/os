[bits 16]
[org 0x7c00]

cli
cld
xor ax, ax
mov es, ax
mov ds, ax

mov bp, 7c00h
mov sp, bp
mov ss, sp

mov ax, 0013h
int 10h
mov ax, 0002h
int 10h

mov ah, 2
mov al, 9
mov ch, 0
mov cl, 2
mov dh, 0
mov bx, 0x1000
int 13h
jc disk_error

lgdt [gdt_desc]

in al, 0x92
or al, 2
out 0x92, al

mov eax, cr0
or eax, 1
mov cr0, eax

jmp codeseg:pmode

[bits 32]

pmode:

mov ax, dataseg
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax

jmp 0x1000
jmp $

[bits 16]

puts:
  pusha
  mov ah, 0x0e
  .puts_loop:
    lodsb
    cmp al, 0
    jz .puts_done
    int 10h
    jmp .puts_loop
  .puts_done:
  popa
  ret

disk_error:
  mov si, error
  call puts
  jmp $

error: db "Error reading disk!",0

gdt_nulldesc:
    dd 0x0
    dd 0x0

gdt_code: 
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

gdt_desc:
    dw gdt_end - gdt_nulldesc - 1
    dd gdt_nulldesc
codeseg equ gdt_code - gdt_nulldesc
dataseg equ gdt_data - gdt_nulldesc

times 510-($-$$) db 0
dw 0xaa55
