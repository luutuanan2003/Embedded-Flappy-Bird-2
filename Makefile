#--------------------------------------Makefile-------------------------------------

CFILES = $(wildcard ./src/*.c)
OFILES = $(CFILES:./src/%.c=./object/%.o)
GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib

mac: cleanMac kernel8.img runMac

win: cleanWin kernel8.img runWin



./object/boot.o: ./src/boot.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/boot.S -o ./object/boot.o

./object/%.o: ./src/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: ./object/boot.o $(OFILES)
	aarch64-none-elf-ld -nostdlib ./object/boot.o  $(OFILES) -T ./src/link.ld -o ./object/kernel8.elf
	aarch64-none-elf-objcopy -O binary ./object/kernel8.elf kernel8.img

cleanMac:
	rm -f .\object\kernel8.elf .\object\*.o *.img

# Run emulation with QEMU
runMac: 
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio

cleanWin:
	del .\object\kernel8.elf .\object\*.o *.img

# Run emulation with QEMU
runWin: 
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio