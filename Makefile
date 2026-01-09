all:
	make clean
	./KernelBuild.sh

clean:
	rm -rf build/*.o
	rm -rf build/*.asm.o
