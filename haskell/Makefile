SRC_FILES := $(wildcard *.hs)

%.s : %.hs
	./bin/ghc -mavx512f -S $<

all: $(patsubst %.hs,%.s,$(SRC_FILES))

clean:
	rm *.s *.hi
