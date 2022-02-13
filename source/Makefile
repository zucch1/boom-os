BIN = boom.elf
ARCH = x86_64
CC = /usr/local/cross/bin/$(ARCH)-elf-gcc
INC = -I./include -Iinclude/kernel -Iinclude/kernel/memory -Iinclude/kernel/util -Iinclude/arch/$(ARCH)
DEFCFLAGS := -I. -c -nostdlib -ffreestanding -fno-stack-protector -fno-pic -fpie -mno-80387 -mno-mmx -mno-3dnow -mno-sse -mno-sse2 -mno-red-zone
DEFLDFLAGS := 			\
		-fno-pic -fpie	\
		-Wl,-static,-pie,--no-dynamic-linker,-ztext	\
		-static-pie		\
		-nostdlib		\
		-Tlinker.ld		\
		-z max-page-size=0x1000
CFLAGS = -Wall  -Wextra -O2 -pipe $(DEFCFLAGS) $(INC) -D$(ARCH)
LDFLAGS = $(DEFLDFLAGS)
KCFILES := $(shell find kernel -type f -name '*.cpp')
# ACFILES := $(shell find arch/$(ARCH) -type f -name '*.cpp')
CFILES =  $(shell find  -type f -name '*.cpp') #KCFILE ACFILES

KOBJS = $(KCFILES:.cpp=.o)
AOBJS = $(ACFILES:.cpp=.o)
OBJS = $(CFILES:.cpp=.o)

.PHONY: all clean disk kernel run

all: kernel disk run

kernel: $(OBJS)
	@echo =================-Linking Objects-=================
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN)
	@echo =================-Link Successful-=================

%.o: %.cpp
	@echo --------Compiling $<
	$(CC) $(CFLAGS) $< -o $@

disk: $(BIN)
	@dd if=/dev/zero bs=10M count=0 seek=64 of=boom.img
	@parted -s boom.img mklabel gpt
	@parted -s boom.img mkpart ESP fat32 2048s 100%
	@parted -s boom.img set 1 esp on
	@limine-install boom.img
	$(eval USED_LOOPBACK = $(shell sudo losetup -Pf --show boom.img))
	@sudo mkfs.fat -F 32 $(USED_LOOPBACK)p1
	@mkdir -p img_mount
	@sudo mount $(USED_LOOPBACK)p1 img_mount
	@sudo mkdir -p img_mount/EFI/BOOT
	@sudo mkdir -p img_mount/boot
	@sudo cp -v $(BIN) limine/limine.sys img_mount/ 
	@sudo cp -v limine/limine.cfg img_mount/boot/
	@sudo cp -v limine/BOOTX64.EFI img_mount/EFI/BOOT/
	@sync
	@sudo umount img_mount
	@sudo losetup -d ${USED_LOOPBACK}
	@rmdir img_mount

run: boom.img
	qemu-system-x86_64 -hda boom.img -m 256M -machine pc -cpu qemu64

clean:
	rm -rf $(BIN) $(OBJS)
	