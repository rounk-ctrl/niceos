C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h)
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

CC = i686-elf-gcc
GDB = i686-elf-gdb
CFLAGS = -g -ffreestanding -Wall -Wextra -fno-exceptions -m32

niceos.bin: boot/bootsect.bin kernel.bin
	cat $^ > niceos.bin

kernel.bin: boot/kernel_entry.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary --allow-multiple-definition

kernel.elf: boot/kernel_entry.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --allow-multiple-definition

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf *.img
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o
image:
	dd if=/dev/zero of=niceos.img bs=1024 count=1440
	dd if=niceos.bin of=niceos.img conv=notrunc
