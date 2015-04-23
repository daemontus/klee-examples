KFLAGS=--only-output-states-covering-new --libc=uclibc --posix-runtime
RFLAGS=--sym-arg 2 --sym-files 1 10

klee: main
	klee $(KFLAGS) main.o $(RFLAGS)

main:
	llvm-gcc --emit-llvm -c -g -std=c99 main.c > /dev/null
