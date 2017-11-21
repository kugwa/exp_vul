obj-m += vul.o

all: vul.ko exp
	
vul.ko: vul.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

exp: exp.h exp.c exp_a.o
	gcc -o exp exp.c exp_a.o

exp_a.o: exp.asm
	nasm -f elf64 -o exp_a.o exp.asm

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f exp *.o
