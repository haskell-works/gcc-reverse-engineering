SRC_FILES := $(wildcard *.c)

%.s : %.c
	gcc -O2 -mavx2 -S $<

all: $(patsubst %.c,%.s,$(SRC_FILES))

clean:
	rm *.s
