# KERNELBUILD FILE

# ELIMINATE THE ISO FILE
rm -rf huguinx.iso

# CLEAR THE SCREEN
clear

# WELCOME MESSAGE
echo "WELCOME TO Huguinx, COMPILATION IS ON PROCESS..."

echo "Note: maybe you have to give the correct permissions to the build files with: chmod +x <build_file_name>.sh"

# CREATE THE DIRECTORY FOR THE BUILD FILES
mkdir build

# CALL THE COMPILE SCRIPTS
./scripts/compilevga.sh # COMPILE VGA DRIVER
# DISCOMMENT THIS LINE IF YOU WANT TO GENERATE AN ISO FILE WITH GRUB
./scripts/compilekernel.sh # COMPILE THE KERNEL
./scripts/compileio.sh # COMPILE THE I/O DRIVER
./scripts/compileserial.sh # COMPILE THE SERIAL PORTS DRIVER
./scripts/compilekeyboard.sh # COMPILE THE KEYBOARD DRIVER
# ./scripts/compileheap.sh # COMPILE THE HEAP IMPLEMENTATION
# ./scripts/compilepaging.sh # COMPILE THE PAGING IMPLEMENTATION
./scripts/compileidt.sh # COMPILE THE IDT IMPLEMENTATION
./scripts/compilegdt.sh # COMPILE THE GDT IMPLEMENTATION
./scripts/compiletss.sh # COMPILE THE TSS IMPLEMENTATION
./scripts/compileentry.sh # COMPILE THE ENTRY FROM GRUB AND THE C KERNEL
./scripts/compiledisk.sh # COMPILE THE ATA DISK DRIVER
./scripts/compilemouse.sh # COMPILE THE MOUSE DRIVER

./scripts/makeelf.sh

./BuildISO.sh

echo "BUILD FINISHED, NOW YOU CAN BOOT THE KERNEL WITH QEMU OR IN REAL HARDWARE, EXECUTE THE 'BuildISO.sh' FILE FOR MAKING THE ISO FILE"
echo "iso/boot/kernel"
echo "huguinx.iso"

# qemu-system-x86_64 -serial stdio huguinx.iso
qemu-system-i386   -drive file=programtest.bin,format=raw,index=0,media=disk   -cdrom huguinx.iso   -boot d   -serial stdio
