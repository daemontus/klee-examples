KFLAGS=--optimize

klee: gcd.o
	klee $(KFLAGS) gcd.o

gcd.o:
	llvm-gcc --emit-llvm -c -g gcd.c
