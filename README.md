# VetraOS

**VetraOS** is a simple, lightweight and experimental operating system written in low-level C and Assembly,
built for performance, simplicity, and learning.
It runs directly on `x86_64` architecture, and its bootable with GRUB via QEMU or real hardware
(an .iso file its provided with every version, but you can
freely build the binary by yourself if you want to!).

---

## About

**VetraOS** is designed to explore low-level OS development.
It features direct VGA rendering, keyboard input, and a minimal
shell interface, all without relying on high-level libraries
or existing filesystems.

---

## How to use it?

as said before, in every version is provided a .iso file ready to boot in any x86 (32-bit) hardware or emulator,
but you can build it with some extra effort and tools, the recomended way to build it is by following this path (linux):

1. Install the needed tools:
  -i686-elf-gcc
  -i686-elf-as
  -grub-mkrescue
  -xorriso
  -mtools
  -qemu-system-i386 (optional, for running)

2. Make sure every tool is working.

3. run `make` to build the .iso

4. run `make clear` (optional, if you want to clear the .o and .bin files)

5. run `make run` if you want to test (qemu needed for this step!)

if you are on linux you can simply run this command to do everything:

debian or ubuntu:

`sudo apt update && sudo apt install -y build-essential qemu 
grub-pc-bin xorriso mtools gcc i686-elf-gcc binutils && make full`
