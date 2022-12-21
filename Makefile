# Run 'make SYS=<target>'; or, set a SYS env.
# var. to build for another target system.
SYS ?= atarixl

NULLDEV = /dev/null
DEL = $(RM)
RMDIR = $(RM) -r

ifdef CC65_HOME
  AS = $(CC65_HOME)/bin/ca65
  CC = $(CC65_HOME)/bin/cc65
  CL = $(CC65_HOME)/bin/cl65
  LD = $(CC65_HOME)/bin/ld65
else
  AS := $(if $(wildcard /usr/bin/ca65*),/usr/bin/ca65,ca65)
  CC := $(if $(wildcard /usr/bin/ca65*),/usr/bin/cc65,cc65)
  CL := $(if $(wildcard /usr/bin/ca65*),/usr/bin/cl65,cl65)
  LD := $(if $(wildcard /usr/bin/ca65*),/usr/bin/ld65,ld65)
endif
day: clean
	$(CL) -t atari -O  -o bin/solution src/day2.c 
clean:
	@$(DEL) bin/day*.* 2>$(NULLDEV)
dist: day 
	cp assets/disk.atr bin/aoc.atr
	tr '\12\11' '\233\177' < resources/data2.txt > bin/data.txt
	franny -A bin/aoc.atr add -i bin/data.txt -o DATA.TXT
	franny -A bin/aoc.atr add -i bin/solution -o AUTORUN.SYS
debug: clean
	$(CC) -t atari -O  -o bin/solution.s src/day1.c
test:
	$(CL) -t atari -O  -o bin/test src/day2.c
	cp assets/disk.atr bin/test.atr
	tr '\12\11' '\233\177' < resources/test_data2.txt > bin/data.txt
	franny -A bin/test.atr add -i bin/data.txt -o DATA.TXT
	franny -A bin/test.atr add -i bin/test -o AUTORUN.SYS