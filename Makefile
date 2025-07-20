OBJECTS = kernel.o terminal.o boot.o utils.o keyboard.o shell.o
SOURCES = boot.s kernel.c src/terminal.c src/utils.c src/keyboard.c src/shell.c

CC = i686-elf-gcc
AS = i686-elf-as

all:
	$(AS) boot.s -o boot.o
	$(CC) -c $(SOURCES) -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude
	$(CC) -T linker.ld -o vetraos.bin -ffreestanding -O2 -nostdlib $(OBJECTS) -lgcc
	cp vetraos.bin isodir/boot/vetraos.bin
	grub-mkrescue -o vetraos.iso isodir

clear:
	rm -f *.o
	rm -f vetraos.bin

run:
	qemu-system-i386 vetraos.iso

full:
	$(AS) boot.s -o boot.o
	$(CC) -c $(SOURCES) -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude
	$(CC) -T linker.ld -o vetraos.bin -ffreestanding -O2 -nostdlib $(OBJECTS) -lgcc
	cp vetraos.bin isodir/boot/vetraos.bin
	grub-mkrescue -o vetraos.iso isodir
	rm -f *.o
	rm -f vetraos.bin
	qemu-system-i386 vetraos.iso
