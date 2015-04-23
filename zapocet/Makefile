KARGS = --only-output-states-covering-new --libc=uclibc --posix-runtime
RARGS = --sym-args 0 2 4 --sym-files 2 10 --sym-stdout

klee: main
	klee $(KARGS) main.o $(RARGS)
main:
	llvm-gcc --emit-llvm -c -g -std=c99 main.c
