#include "heap.hh"
#include "gtest/gtest.h"
#include <vector>
#include <memory>
#include <algorithm>

template<typename T> bool test_sort(T *begin, T *end) {
	std::vector<T> s(begin, end);
	heapsort(begin, end);
	std::sort(s.begin(), s.end(), std::greater<T>());
	return std::equal(s.begin(), s.end(), begin);
}

template<typename T> bool test_sort(T begin, T end) {
	std::vector<typename T::value_type> s(begin, end);
	heapsort(begin, end);
	std::sort(s.begin(), s.end(), std::greater<typename T::value_type>());
	return std::equal(s.begin(), s.end(), begin);
}

#define dim(X)	(sizeof(X)/sizeof(X[0]))

TEST(HeapTest, T1) {
	char a[] = {1, 2, 3, 4, 5};
	EXPECT_TRUE(test_sort(a, a+dim(a)));
}

TEST(HeapTest, T2) {
	std::vector<double> a = {1.0};
	EXPECT_TRUE(test_sort(a.begin(), a.end()));
}

TEST(HeapTest, T3) {
	long a[] = {5, 4, 3, 2, 1};
	EXPECT_TRUE(test_sort(a, a+dim(a)));
}

TEST(HeapTest, T4) {
	long a[] = {1, 2};
	EXPECT_TRUE(test_sort(a, a+dim(a)));
}

TEST(HeapTest, T5) {
	long a[] = {2, 1};
	EXPECT_TRUE(test_sort(a, a+dim(a)));
}

TEST(HeapTest, T6) {
	long a[] = {1};
	EXPECT_TRUE(test_sort(a, a+dim(a)));
}

TEST(HeapTest, Random) {
	for (int sz=1; sz<1024; sz++) {
		std::unique_ptr<long[]> a(new long[sz]);
		for (int i=0; i<sz; i++)
			a[i] = rand();
		EXPECT_TRUE(test_sort(&a[0], &a[sz]));
	}
}

TEST(HeapTest, Performance) {
	constexpr int sz = 1<<22;
	std::vector<int> b(sz);
	for (auto &bi:b)
		bi = rand();
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	std::make_heap(&b[0], &b[sz], std::greater<int>());
	std::sort_heap(&b[0], &b[sz], std::greater<int>());
	end = std::chrono::system_clock::now();
	EXPECT_TRUE(std::is_sorted(&b[0], &b[sz], std::greater<int>()));
	std::chrono::duration<double> stock = end-start;
	std::cerr << "[			 ] system heap sort performance = " << stock.count() << std::endl;
	for (auto &bi:b)
		bi = rand();
	start = std::chrono::system_clock::now();
	heapsort(&b[0], &b[sz]);
	end = std::chrono::system_clock::now();
	EXPECT_TRUE(std::is_sorted(&b[0], &b[sz], std::greater<int>()));
	std::chrono::duration<double> ours = end-start;
	std::cerr << "[			 ] our heap sort performance = " << ours.count() << std::endl;
	EXPECT_TRUE(stock * .9 > ours);	// ours must be no slower than 10%
}
