#include "ilog.hh"
#include "ilog.h"
#include "gtest/gtest.h"
#include <cmath>
#include <climits>
#include <chrono>

TEST(ILog, ILog2_CPP) {
	EXPECT_EQ(0, ilog<2>(0));
	EXPECT_EQ(0, ilog<2>((char)1));
	EXPECT_EQ(1, ilog<2>((int)2));
	EXPECT_EQ(2, ilog<2>((long)3));
	EXPECT_EQ(2, ilog<2>((long long)4));
	EXPECT_EQ(3, ilog<2>((unsigned char)5));
	EXPECT_EQ(3, ilog<2>((unsigned int)6));
	EXPECT_EQ(3, ilog<2>((unsigned long)7));
	EXPECT_EQ(3, ilog<2>((unsigned long long)8));
	EXPECT_EQ(4, ilog<2>((short)9));
	EXPECT_EQ(4, ilog<2>((unsigned short)10));
	EXPECT_EQ(64, ilog<2>(ULLONG_MAX));
	for (auto i=1; i<100002; i++)
		EXPECT_EQ(int(ceil(log2(i))), ilog<2>(i));
}

TEST(ILog, ILog10_CPP) {
	EXPECT_EQ(0, ilog<10>(0));
	EXPECT_EQ(0, ilog<10>((int8_t)1));
	EXPECT_EQ(1, ilog<10>((int16_t)2));
	EXPECT_EQ(1, ilog<10>((int32_t)9));
	EXPECT_EQ(1, ilog<10>((int64_t)10));
	EXPECT_EQ(2, ilog<10>((signed char)11));
	EXPECT_EQ(18, ilog<10>(1000000000000000000ULL-1));
	EXPECT_EQ(18, ilog<10>(1000000000000000000ULL));
	EXPECT_EQ(19, ilog<10>(1000000000000000000ULL+1));
	EXPECT_EQ(20, ilog<10>(ULLONG_MAX));
	for (auto i=1; i<100002; i++)
		EXPECT_EQ(int(ceil(log10(i))), ilog<10>(i));
}

TEST(ILog, ILog2_C) {
	EXPECT_EQ(0, ilog2_u8(0));
	EXPECT_EQ(0, ilog2_u8((char)1));
	EXPECT_EQ(1, ilog2_u16((int)2));
	EXPECT_EQ(2, ilog2_u16((long)3));
	EXPECT_EQ(2, ilog2_u32((long long)4));
	EXPECT_EQ(3, ilog2_u32((unsigned char)5));
	EXPECT_EQ(3, ilog2_u32((unsigned int)6));
	EXPECT_EQ(3, ilog2_u32((unsigned long)7));
	EXPECT_EQ(3, ilog2_u32((unsigned long long)8));
	EXPECT_EQ(4, ilog2_u64((short)9));
	EXPECT_EQ(4, ilog2_u64((unsigned short)10));
	EXPECT_EQ(64, ilog2_u64(ULLONG_MAX));
	for (auto i=1; i<100002; i++)
		EXPECT_EQ(int(ceil(log2(i))), ilog2_u32(i));
}

TEST(ILog, ILog10_C) {
	EXPECT_EQ(0, ilog10_u32(0));
	EXPECT_EQ(0, ilog10_u32((int8_t)1));
	EXPECT_EQ(1, ilog10_u32((int16_t)2));
	EXPECT_EQ(1, ilog10_u32((int32_t)9));
	EXPECT_EQ(1, ilog10_u32((int64_t)10));
	EXPECT_EQ(2, ilog10_u32((signed char)11));
	EXPECT_EQ(18, ilog10_u64(1000000000000000000ULL-1));
	EXPECT_EQ(18, ilog10_u64(1000000000000000000ULL));
	EXPECT_EQ(19, ilog10_u64(1000000000000000000ULL+1));
	EXPECT_EQ(20, ilog10_u64(ULLONG_MAX));
	for (auto i=1; i<100002; i++)
		EXPECT_EQ(int(ceil(log10(i))), ilog10_u32(i));
}

TEST(ILog, Performance) {
	constexpr int sz = 1<<26;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	uint64_t cs_stock = 0;
	for (auto i=1; i<sz; i++)
		cs_stock += int(ceil(log2(i)));
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> stock = end-start;
	std::cerr << "[			 ] int(ceil(log2(i))) performance = " << stock.count() << std::endl;
	start = std::chrono::system_clock::now();
	uint64_t cs_c = 0;
	for (auto i=1; i<sz; i++)
		cs_c += ilog2_u32(i);
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> ours_c = end-start;
	std::cerr << "[			 ] our ilog2_u32(i) performance = " << ours_c.count() << std::endl;
	start = std::chrono::system_clock::now();
	uint64_t cs_cpp = 0;
	for (auto i=1; i<sz; i++)
		cs_cpp += ilog<2>(i);
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> ours_cpp = end-start;
	std::cerr << "[			 ] our ilog<2>(i) performance = " << ours_cpp.count() << std::endl;
	EXPECT_TRUE(stock.count() * 1.1 > ours_c.count());	// ours must be no slower than 10%
	EXPECT_TRUE(stock.count() * 1.1 > ours_cpp.count());	// ours must be no slower than 10%
	EXPECT_TRUE(cs_stock == cs_c); // checksum must match
	EXPECT_TRUE(cs_stock == cs_cpp); // checksum must match
}
