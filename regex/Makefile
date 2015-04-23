
KFLAGS=--only-output-states-covering-new --libc=uclibc --posix-runtime

klee: regexp
	klee $(KFLAGS) regexp.o

regexp:
	llvm-gcc --emit-llvm -c -g regexp.c
