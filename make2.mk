#make -f make2.mk
preprocess:
	gcc -E forkinc.c -o forkinc.i
compile:
	gcc -S forkinc.c -o forkinc.s
assembly:
	gcc -c forkinc.c -o forkinc.o   

linker:
	gcc forkinc.c -o forkinc
default:
	gcc forkinc.c -o forkinc && ./forkinc
