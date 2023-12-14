CC = gcc
PATHTOCC = /home/almorshidi0/arm-cross-compiler/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin
ifeq ($(CROSS_COMPILE),)
CC = gcc
else ifeq ($(CROSS_COMPILE), aarch64-none-linux-gnu-)
CC = $(PATHTOCC)/$(CROSS_COMPILE)gcc
endif

writer:
	$(CC) writer.c -o writer

clean:
	rm -rf writer
