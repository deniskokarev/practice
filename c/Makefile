BINS = a b c d e f \
	alg/comb_test \
	alg/ilog_test \
	alg/heap_test \
	alg/par_test \
	draft/knapsack_test \
	draft/matmul_test \
	draft/lcs_test \

INCGT = ./googletest/googletest/include
LIBGT = ./libgt/googlemock/gtest/libgtest.a
LIBGTMAIN = ./libgt/googlemock/gtest/libgtest_main.a

CXXFLAGS += -std=c++11 -Wall -g -O0 -I$(INCGT) 
CFLAGS += -std=c99 -Wall -g -O
LINK.o = $(LINK.cc)
LDFLAGS =
EXTRA_LIBS = -lpthread

all: $(BINS)

$(LIBGTMAIN): $(LIBGT)
$(LIBGT):
	[ -d libgt ] || mkdir libgt
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
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(@) $(+) $(EXTRA_LIBS)

alg/ilog.c: alg/ilog.h

alg/ilog.h:  alg/genilog.sh
	cd alg && ./genilog.sh

alg/ilog_test.o: alg/ilog_test.cc alg/ilog.hh alg/ilog.h
	$(CXX) $(CXXFLAGS) -I$(INCGT) -o $(@) -c alg/ilog_test.cc

alg/ilog_test: alg/ilog_test.o alg/ilog.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(@) $(+) $(EXTRA_LIBS)

alg/heap_test.o: alg/heap.hh
alg/heap_test: alg/heap_test.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(@) $(+) $(EXTRA_LIBS)

alg/par.o: alg/par.hh
alg/par_test.o: alg/par.hh
alg/par_test: alg/par_test.o alg/par.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(@) $(+) $(EXTRA_LIBS)

alg/binomial_test.o: alg/binomial_test.cc alg/binomial.hh
	$(CXX) $(CXXFLAGS) -I$(INCGT) -o $(@) -c alg/binomial_test.cc

alg/binomial_test: alg/binomial_test.o alg/comb.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(@) $(+) $(EXTRA_LIBS)

draft/knapsack.o: draft/knapsack.hh
draft/knapsack_test: draft/knapsack_test.o draft/knapsack.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(@) $(+) $(EXTRA_LIBS)

draft/matmul.o: draft/matmul.hh
draft/matmul_test.o: draft/matmul.hh
draft/matmul_test: draft/matmul_test.o draft/matmul.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(@) $(+) $(EXTRA_LIBS)

draft/lcs_test.o: draft/lcs.hh
draft/lcs_test: draft/lcs_test.o $(LIBGTMAIN) $(LIBGT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(@) $(+) $(EXTRA_LIBS)


test: ./alg/comb_test ./alg/ilog_test ./alg/heap_test ./alg/par_test ./alg/binomial_test ./draft/knapsack_test ./draft/matmul_test
	./alg/comb_test
	./alg/ilog_test
	./alg/heap_test
	./alg/par_test
	./alg/binomial_test
	./draft/knapsack_test
	./draft/matmul_test


clean:
	rm -f alg/ilog.c alg/ilog.h
	for d in . alg draft; do rm -f $$d/*.o $$d/*~; done
	rm -rf libgt
	rm -f $(BINS)
	rm -rf Build
