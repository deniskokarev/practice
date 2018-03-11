BINS = a acuda memtrans bandwidthtest match
INCGT = ../c/googletest/googletest/include
LIBGT = ../c/libgt/googlemock/gtest/libgtest.a
LIBGTMAIN = ../c/libgt/googlemock/gtest/libgtest_main.a

CXXFLAGS += -std=c++11 -Wall -g -O0 -I$(INCGT) 
CFLAGS += -std=c99 -Wall -g -O0
LINK.o = $(LINK.cc)
LDFLAGS = -L/usr/local/cuda/lib -lcuda -lcudart -rpath /usr/local/cuda/lib
EXTRA_LIBS = -lpthread


# nvcc
NVCC      := nvcc
NVCCFLAGS := -std=c++11
NVCCFLAGS += -O
NVCCFLAGS += -gencode arch=compute_30,code=sm_30 \
             -gencode arch=compute_35,code=sm_35 \
             -gencode arch=compute_50,code=sm_50 \
             -gencode arch=compute_50,code=compute_50

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

transpose.o: transpose.hh die.h

detect.o: detect.hh die.h

match: match.o transpose.o detect.o die.o

trans: trans.o

test:
	(echo "ab cd ef"; ./test.sh; echo "gh") | nvprof ./match

clean:
	rm -f *.o
	rm -f *~
	rm -rf libgt
	rm -f $(BINS)
	rm -rf Build
