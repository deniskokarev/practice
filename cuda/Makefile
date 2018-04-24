BINS = a acuda memtrans bandwidthtest match actcomp actmatch actfgrep cuuidgsp uuidgsp uuidfind
INCGT = ../c/googletest/googletest/include
LIBGT = ../c/libgt/googlemock/gtest/libgtest.a
LIBGTMAIN = ../c/libgt/googlemock/gtest/libgtest_main.a

CXXFLAGS += -std=c++11 -Wall -g -O -I$(INCGT) 
CFLAGS += -std=c99 -Wall -g -O
LINK.o = $(LINK.cc)
LDFLAGS = -L/usr/local/cuda/lib -lcuda -lcudart -rpath /usr/local/cuda/lib
EXTRA_LIBS = -lpthread


# nvcc
NVCC      := nvcc
NVCCFLAGS := -std=c++11
NVCCFLAGS += -O3
NVCCFLAGS += -gencode arch=compute_30,code=sm_30 \
             -gencode arch=compute_35,code=sm_35 \
             -gencode arch=compute_50,code=sm_50 \
             -gencode arch=compute_60,code=sm_60 \
             -gencode arch=compute_60,code=compute_60

%.o: %.cu
	$(NVCC) $< $(NVCCFLAGS) -c -o $@

all: $(BINS)

$(LIBGTMAIN): $(LIBGT)
$(LIBGT):
	[ -d libgt ] || mkdir libgt
	cd libgt && cmake ../googletest && $(MAKE)

libgt: $(LIBGTMAIN)

a: a.o

acuda: acuda.o

memtrans: memtrans.o

bandwidthtest: bandwidthtest.o

match.o: transpose.hh detect.hh die.h

transpose.o: transpose.hh transpose.cuh die.h

detect.o: detect.hh transpose.cuh die.h

match: match.o transpose.o detect.o die.o

trans: trans.o

actcomp.o: act.h

actcomp: actcomp.o
	$(LINK.cc) -o $(@) actcomp.o

act.o: act.h

actmatch.o: act.h

actmatch: act.o actmatch.o

actfgrep.o: act.h

actfgrep: act.o actfgrep.o

test: test_cuda test_act

test_cuda: match
	(echo "ab cd ef"; ./test.sh; echo "gh") | nvprof ./match

cuuidgsp: cuuidgsp.o uuidmatch.o die.o

uuidgsp: uuidgsp.o uuidmatch.o die.o

uuidfind: uuidfind.o uuidmatch.o die.o

test_act: actcomp actmatch
	./actcomp pat3.txt pat3.bin
	echo "you must see 0 1 3 4 5 6"
	echo "att.com" | ./actmatch pat3.bin

clean:
	rm -f *.o
	rm -f *~
	rm -rf libgt
	rm -f $(BINS)
	rm -f pat*.bin
	rm -rf Build
