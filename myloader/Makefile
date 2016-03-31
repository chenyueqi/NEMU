CC = gcc
CFLAGS = -m32 -O2 -Wall -Werror -fno-builtin -Wno-unused-result
CFLAGS += -I./include  
                   
ASFLAGS = -m32
 
CSRC = $(shell find src/ -name "*.c")  
 
OBJS = $(CSRC:.c=.o)  
 
loader: $(CSRC)
	$(CC) -c $(CFLAGS) $(CSRC)
	mv *.o src/
	$(CC) -m32 -c src/start.S -o src/start.o
	ld -o loader -e start -Ttext 0x100000 -m elf_i386 src/start.o $(OBJS)
 
clean:
		-rm -f $(shell find ./ -name "*.[od]") loader
