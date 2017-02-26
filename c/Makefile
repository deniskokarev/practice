BINS = a b c d e f \
	alg/comb_test \
	alg/heap_test \
	draft/lcs_test \

CXXFLAGS += -std=c++11 -Wall -g -O0
CFLAGS += -std=c99 -Wall
LINK.o = $(LINK.cc)

INCGT = ./googletest/googletest/include
LIBGT = ./libgt/googlemock/gtest/libgtest.a
LIBGTMAIN = ./libgt/googlemock/gtest/libgtest_main.a

all: $(BINS)

$(LIBGTMAIN): $(LIBGT)
$(LIBGT):
	mkdir libgt
	cd libgt && cmake ../googletest && $(MAKE)

libgt: $(LIBGTMAIN)

# codeforces bins
cf: a b c d e f

a: a.o
b: b.o
c: c.o
d: d.o
e: e.o
f: f.o

alg/comb_test.o: alg/comb_test.cc
	$(CXX) $(CXXFLAGS) -I$(INCGT) -o $(@) -c $(?)
alg/comb_test: alg/comb.o alg/comb_test.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) -o $(@) $(+)
alg/heap_test.o: alg/heap_test.cc
	$(CXX) $(CXXFLAGS) -I$(INCGT) -o $(@) -c $(?)
alg/heap_test: alg/heap_test.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) -o $(@) $(+)
draft/lcs_test.o: draft/lcs_test.cc draft/lcs.hh
	$(CXX) $(CXXFLAGS) -I$(INCGT) -o $(@) -c draft/lcs_test.cc
draft/lcs_test: draft/lcs_test.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) -o $(@) $(+)

test: ./alg/comb_test ./alg/heap_test
	./alg/comb_test
	./alg/heap_test

clean:
	for d in . alg draft; do rm -f $$d/*.o $$d/*~; done
	rm -rf libgt
	rm -f $(BINS)
	rm -rf Build
