OBJECTS = kernel.o terminal.o boot.o
SOURCES = boot.s kernel.c src/terminal.c

CC = i686-elf-gcc
AS = i686-elf-as

all:
	$(AS) boot.s -o boot.o
	$(CC) -c $(SOURCES) -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude
	$(CC) -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib $(OBJECTS) -lgcc
	cp myos.bin isodir/boot/myos.bin
	grub-mkrescue -o myos.iso isodir

clear:
	rm -f *.o
	rm -f myos.bin

run:
	qemu-system-i386 myos.iso