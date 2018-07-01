SRC_FILES := $(wildcard *.c)

%.s : %.c
	gcc -O2 -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-ssse3 -mno-sse4.1 -mno-sse4.2 -mno-sse4 -mno-avx -S $<

%.out : %.c
	gcc -O2 $< -o $@

all: $(patsubst %.c,%.s,$(SRC_FILES)) $(patsubst %.c,%.out,$(SRC_FILES))

clean:
	rm *.s *.out
