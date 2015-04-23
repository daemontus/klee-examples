
KFLAGS=--optimize

klee: function.o
	klee $(KFLAGS) function.o

function.o:
	llvm-gcc --emit-llvm -c -g function.c

