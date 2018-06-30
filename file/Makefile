SRC_FILES := $(wildcard *.c)

%.s : %.c
	gcc -O2 -mavx2 -S $<

%.out : %.c
	gcc -O2 -mavx2 $< -o $@

all: $(patsubst %.c,%.s,$(SRC_FILES)) $(patsubst %.c,%.out,$(SRC_FILES))

clean:
	rm *.s *.out
