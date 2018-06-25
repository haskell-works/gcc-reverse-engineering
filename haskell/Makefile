SRC_FILES := $(wildcard *.hs)

%.s : %.hs
	./bin/ghc -O2 -mavx512f -mavx2 -S $<

all: $(patsubst %.hs,%.s,$(SRC_FILES))

clean:
	rm *.s *.hi
