SRC_FILES := $(wildcard *.hs)

%.s : %.hs
	./bin/ghc -O0 -mavx512f -mavx2 -S $<

%.out : %.hs
	./bin/ghc -O0 -mavx512f -mavx2 $< -o $@
	chmod a+x $@

all: $(patsubst %.hs,%.s,$(SRC_FILES)) $(patsubst %.hs,%.out,$(SRC_FILES))

clean:
	rm *.s *.hi *.out
