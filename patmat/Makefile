BINS = actcomp actmatch actfgrep uuidgrep uuidgsp

CXXFLAGS = -g -Wall -O2 -pthread -std=c++11
CFLAGS = -g -Wall -O2 -std=c99

LINK.o = $(LINK.cc)

all: $(BINS)

actcomp.o: act.h

actcomp: actcomp.o

act.o: act.h

actmatch.o: act.h

actmatch: act.o actmatch.o

actfgrep.o: act.h

actfgrep: act.o actfgrep.o

uuidgrep.o: uuidmatch.h
uuidmatch.o: uuidmatch.h

uuidgrep: uuidgrep.o uuidmatch.o

uuidgsp: uuidgsp.o uuidmatch.o die.o

test: test_uuidgrep test_act

test_uuidgrep: uuidgrep
	@echo "You should see 2 UUIDs detected:"
	echo "2FF7B47D-A232-4A3B-9C5A-7B0D218B00BA-A232-4A3B-9C5A-7B0D218B00BA" | ./uuidgrep
	@echo "You should see 1 UUID detected:"
	echo "7B0D218B00BA-A232-4A3B-9C5A-7B0D218B00BA" | ./uuidgrep

test_act: actcomp actfgrep
	@echo '*** You should see "a" "ab" "abc" "abcd" "efgh" "fgh" "gh" "h" detected:'
	echo "abcdefgh" | ./actcomp -v -g pat1.txt /dev/null
	@echo '*** You should see "a" "at" "t" "t" "att.com" "om" "m" detected:'
	echo "att.com" | ./actcomp -v -g pat3.txt /dev/null
	@echo '*** Volume test, you should see 52220 matches'
	./actcomp pat5.txt /tmp/pat5.bin
	./actfgrep /tmp/pat5.bin <pat5.txt | wc -l
	rm /tmp/pat5.bin

clean:
	rm -f *.o
	rm -f $(BINS)
