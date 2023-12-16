CSRCS = $(wildcard kernel/*.c cpu/*.c drivers/*.c)
HEADERS = $(wildcard include/*.h cpu/*.h drivers/*.h)

OBJ = $(CSRCS:.c=.o)

CC = gcc
CFLAGS = -m32 -Wall -ffreestanding -s -nostdlib -Os -fno-pie -fno-ident -fno-leading-underscore

LD = /i386-elf-binutils/i386-elf/bin/ld

os.img: boot/boot.bin kernel/kernel.bin boot/zero.bin
	cat $^ > os.img

kernel/kernel.bin: ${OBJ} kernel/entry.o
	${LD} -o $@ -Ttext 0x1000 --oformat binary $^ link.ld

run: os.img
	qemu-system-x86_64 os.img -monitor stdio

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm $< -felf32 -o $@

%.bin: %.asm
	nasm $< -fbin -o $@

clean:
	rm -rf *.bin *.o os.img kernel/*.o kernel/*.bin boot/*.bin boot/*.o cpu/*.o drivers/*.o
