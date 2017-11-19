/********* Automatically generated file - don't edit **********/
/**** entire family of ilog_u functions for each arg size *****/

#include "ilog.h"

#define __ILOG2_uint64_t_00_00(X)	0
#define __ILOG2_uint64_t_01_01(X)	1
#define __ILOG2_uint64_t_00_01(X)	(((X) <= (1ULL<<0)) ? __ILOG2_uint64_t_00_00(X) : __ILOG2_uint64_t_01_01(X))
#define __ILOG2_uint64_t_02_02(X)	2
#define __ILOG2_uint64_t_00_02(X)	(((X) <= (1ULL<<1)) ? __ILOG2_uint64_t_00_01(X) : __ILOG2_uint64_t_02_02(X))
#define __ILOG2_uint64_t_03_03(X)	3
#define __ILOG2_uint64_t_04_04(X)	4
#define __ILOG2_uint64_t_03_04(X)	(((X) <= (1ULL<<3)) ? __ILOG2_uint64_t_03_03(X) : __ILOG2_uint64_t_04_04(X))
#define __ILOG2_uint64_t_00_04(X)	(((X) <= (1ULL<<2)) ? __ILOG2_uint64_t_00_02(X) : __ILOG2_uint64_t_03_04(X))
#define __ILOG2_uint64_t_05_05(X)	5
#define __ILOG2_uint64_t_06_06(X)	6
#define __ILOG2_uint64_t_05_06(X)	(((X) <= (1ULL<<5)) ? __ILOG2_uint64_t_05_05(X) : __ILOG2_uint64_t_06_06(X))
#define __ILOG2_uint64_t_07_07(X)	7
#define __ILOG2_uint64_t_08_08(X)	8
#define __ILOG2_uint64_t_07_08(X)	(((X) <= (1ULL<<7)) ? __ILOG2_uint64_t_07_07(X) : __ILOG2_uint64_t_08_08(X))
#define __ILOG2_uint64_t_05_08(X)	(((X) <= (1ULL<<6)) ? __ILOG2_uint64_t_05_06(X) : __ILOG2_uint64_t_07_08(X))
#define __ILOG2_uint64_t_00_08(X)	(((X) <= (1ULL<<4)) ? __ILOG2_uint64_t_00_04(X) : __ILOG2_uint64_t_05_08(X))
#define __ILOG2_uint64_t_09_09(X)	9
#define __ILOG2_uint64_t_10_10(X)	10
#define __ILOG2_uint64_t_09_10(X)	(((X) <= (1ULL<<9)) ? __ILOG2_uint64_t_09_09(X) : __ILOG2_uint64_t_10_10(X))
#define __ILOG2_uint64_t_11_11(X)	11
#define __ILOG2_uint64_t_12_12(X)	12
#define __ILOG2_uint64_t_11_12(X)	(((X) <= (1ULL<<11)) ? __ILOG2_uint64_t_11_11(X) : __ILOG2_uint64_t_12_12(X))
#define __ILOG2_uint64_t_09_12(X)	(((X) <= (1ULL<<10)) ? __ILOG2_uint64_t_09_10(X) : __ILOG2_uint64_t_11_12(X))
#define __ILOG2_uint64_t_13_13(X)	13
#define __ILOG2_uint64_t_14_14(X)	14
#define __ILOG2_uint64_t_13_14(X)	(((X) <= (1ULL<<13)) ? __ILOG2_uint64_t_13_13(X) : __ILOG2_uint64_t_14_14(X))
#define __ILOG2_uint64_t_15_15(X)	15
#define __ILOG2_uint64_t_16_16(X)	16
#define __ILOG2_uint64_t_15_16(X)	(((X) <= (1ULL<<15)) ? __ILOG2_uint64_t_15_15(X) : __ILOG2_uint64_t_16_16(X))
#define __ILOG2_uint64_t_13_16(X)	(((X) <= (1ULL<<14)) ? __ILOG2_uint64_t_13_14(X) : __ILOG2_uint64_t_15_16(X))
#define __ILOG2_uint64_t_09_16(X)	(((X) <= (1ULL<<12)) ? __ILOG2_uint64_t_09_12(X) : __ILOG2_uint64_t_13_16(X))
#define __ILOG2_uint64_t_00_16(X)	(((X) <= (1ULL<<8)) ? __ILOG2_uint64_t_00_08(X) : __ILOG2_uint64_t_09_16(X))
#define __ILOG2_uint64_t_17_17(X)	17
#define __ILOG2_uint64_t_18_18(X)	18
#define __ILOG2_uint64_t_17_18(X)	(((X) <= (1ULL<<17)) ? __ILOG2_uint64_t_17_17(X) : __ILOG2_uint64_t_18_18(X))
#define __ILOG2_uint64_t_19_19(X)	19
#define __ILOG2_uint64_t_20_20(X)	20
#define __ILOG2_uint64_t_19_20(X)	(((X) <= (1ULL<<19)) ? __ILOG2_uint64_t_19_19(X) : __ILOG2_uint64_t_20_20(X))
#define __ILOG2_uint64_t_17_20(X)	(((X) <= (1ULL<<18)) ? __ILOG2_uint64_t_17_18(X) : __ILOG2_uint64_t_19_20(X))
#define __ILOG2_uint64_t_21_21(X)	21
#define __ILOG2_uint64_t_22_22(X)	22
#define __ILOG2_uint64_t_21_22(X)	(((X) <= (1ULL<<21)) ? __ILOG2_uint64_t_21_21(X) : __ILOG2_uint64_t_22_22(X))
#define __ILOG2_uint64_t_23_23(X)	23
#define __ILOG2_uint64_t_24_24(X)	24
#define __ILOG2_uint64_t_23_24(X)	(((X) <= (1ULL<<23)) ? __ILOG2_uint64_t_23_23(X) : __ILOG2_uint64_t_24_24(X))
#define __ILOG2_uint64_t_21_24(X)	(((X) <= (1ULL<<22)) ? __ILOG2_uint64_t_21_22(X) : __ILOG2_uint64_t_23_24(X))
#define __ILOG2_uint64_t_17_24(X)	(((X) <= (1ULL<<20)) ? __ILOG2_uint64_t_17_20(X) : __ILOG2_uint64_t_21_24(X))
#define __ILOG2_uint64_t_25_25(X)	25
#define __ILOG2_uint64_t_26_26(X)	26
#define __ILOG2_uint64_t_25_26(X)	(((X) <= (1ULL<<25)) ? __ILOG2_uint64_t_25_25(X) : __ILOG2_uint64_t_26_26(X))
#define __ILOG2_uint64_t_27_27(X)	27
#define __ILOG2_uint64_t_28_28(X)	28
#define __ILOG2_uint64_t_27_28(X)	(((X) <= (1ULL<<27)) ? __ILOG2_uint64_t_27_27(X) : __ILOG2_uint64_t_28_28(X))
#define __ILOG2_uint64_t_25_28(X)	(((X) <= (1ULL<<26)) ? __ILOG2_uint64_t_25_26(X) : __ILOG2_uint64_t_27_28(X))
#define __ILOG2_uint64_t_29_29(X)	29
#define __ILOG2_uint64_t_30_30(X)	30
#define __ILOG2_uint64_t_29_30(X)	(((X) <= (1ULL<<29)) ? __ILOG2_uint64_t_29_29(X) : __ILOG2_uint64_t_30_30(X))
#define __ILOG2_uint64_t_31_31(X)	31
#define __ILOG2_uint64_t_32_32(X)	32
#define __ILOG2_uint64_t_31_32(X)	(((X) <= (1ULL<<31)) ? __ILOG2_uint64_t_31_31(X) : __ILOG2_uint64_t_32_32(X))
#define __ILOG2_uint64_t_29_32(X)	(((X) <= (1ULL<<30)) ? __ILOG2_uint64_t_29_30(X) : __ILOG2_uint64_t_31_32(X))
#define __ILOG2_uint64_t_25_32(X)	(((X) <= (1ULL<<28)) ? __ILOG2_uint64_t_25_28(X) : __ILOG2_uint64_t_29_32(X))
#define __ILOG2_uint64_t_17_32(X)	(((X) <= (1ULL<<24)) ? __ILOG2_uint64_t_17_24(X) : __ILOG2_uint64_t_25_32(X))
#define __ILOG2_uint64_t_00_32(X)	(((X) <= (1ULL<<16)) ? __ILOG2_uint64_t_00_16(X) : __ILOG2_uint64_t_17_32(X))
#define __ILOG2_uint64_t_33_33(X)	33
#define __ILOG2_uint64_t_34_34(X)	34
#define __ILOG2_uint64_t_33_34(X)	(((X) <= (1ULL<<33)) ? __ILOG2_uint64_t_33_33(X) : __ILOG2_uint64_t_34_34(X))
#define __ILOG2_uint64_t_35_35(X)	35
#define __ILOG2_uint64_t_36_36(X)	36
#define __ILOG2_uint64_t_35_36(X)	(((X) <= (1ULL<<35)) ? __ILOG2_uint64_t_35_35(X) : __ILOG2_uint64_t_36_36(X))
#define __ILOG2_uint64_t_33_36(X)	(((X) <= (1ULL<<34)) ? __ILOG2_uint64_t_33_34(X) : __ILOG2_uint64_t_35_36(X))
#define __ILOG2_uint64_t_37_37(X)	37
#define __ILOG2_uint64_t_38_38(X)	38
#define __ILOG2_uint64_t_37_38(X)	(((X) <= (1ULL<<37)) ? __ILOG2_uint64_t_37_37(X) : __ILOG2_uint64_t_38_38(X))
#define __ILOG2_uint64_t_39_39(X)	39
#define __ILOG2_uint64_t_40_40(X)	40
#define __ILOG2_uint64_t_39_40(X)	(((X) <= (1ULL<<39)) ? __ILOG2_uint64_t_39_39(X) : __ILOG2_uint64_t_40_40(X))
#define __ILOG2_uint64_t_37_40(X)	(((X) <= (1ULL<<38)) ? __ILOG2_uint64_t_37_38(X) : __ILOG2_uint64_t_39_40(X))
#define __ILOG2_uint64_t_33_40(X)	(((X) <= (1ULL<<36)) ? __ILOG2_uint64_t_33_36(X) : __ILOG2_uint64_t_37_40(X))
#define __ILOG2_uint64_t_41_41(X)	41
#define __ILOG2_uint64_t_42_42(X)	42
#define __ILOG2_uint64_t_41_42(X)	(((X) <= (1ULL<<41)) ? __ILOG2_uint64_t_41_41(X) : __ILOG2_uint64_t_42_42(X))
#define __ILOG2_uint64_t_43_43(X)	43
#define __ILOG2_uint64_t_44_44(X)	44
#define __ILOG2_uint64_t_43_44(X)	(((X) <= (1ULL<<43)) ? __ILOG2_uint64_t_43_43(X) : __ILOG2_uint64_t_44_44(X))
#define __ILOG2_uint64_t_41_44(X)	(((X) <= (1ULL<<42)) ? __ILOG2_uint64_t_41_42(X) : __ILOG2_uint64_t_43_44(X))
#define __ILOG2_uint64_t_45_45(X)	45
#define __ILOG2_uint64_t_46_46(X)	46
#define __ILOG2_uint64_t_45_46(X)	(((X) <= (1ULL<<45)) ? __ILOG2_uint64_t_45_45(X) : __ILOG2_uint64_t_46_46(X))
#define __ILOG2_uint64_t_47_47(X)	47
#define __ILOG2_uint64_t_48_48(X)	48
#define __ILOG2_uint64_t_47_48(X)	(((X) <= (1ULL<<47)) ? __ILOG2_uint64_t_47_47(X) : __ILOG2_uint64_t_48_48(X))
#define __ILOG2_uint64_t_45_48(X)	(((X) <= (1ULL<<46)) ? __ILOG2_uint64_t_45_46(X) : __ILOG2_uint64_t_47_48(X))
#define __ILOG2_uint64_t_41_48(X)	(((X) <= (1ULL<<44)) ? __ILOG2_uint64_t_41_44(X) : __ILOG2_uint64_t_45_48(X))
#define __ILOG2_uint64_t_33_48(X)	(((X) <= (1ULL<<40)) ? __ILOG2_uint64_t_33_40(X) : __ILOG2_uint64_t_41_48(X))
#define __ILOG2_uint64_t_49_49(X)	49
#define __ILOG2_uint64_t_50_50(X)	50
#define __ILOG2_uint64_t_49_50(X)	(((X) <= (1ULL<<49)) ? __ILOG2_uint64_t_49_49(X) : __ILOG2_uint64_t_50_50(X))
#define __ILOG2_uint64_t_51_51(X)	51
#define __ILOG2_uint64_t_52_52(X)	52
#define __ILOG2_uint64_t_51_52(X)	(((X) <= (1ULL<<51)) ? __ILOG2_uint64_t_51_51(X) : __ILOG2_uint64_t_52_52(X))
#define __ILOG2_uint64_t_49_52(X)	(((X) <= (1ULL<<50)) ? __ILOG2_uint64_t_49_50(X) : __ILOG2_uint64_t_51_52(X))
#define __ILOG2_uint64_t_53_53(X)	53
#define __ILOG2_uint64_t_54_54(X)	54
#define __ILOG2_uint64_t_53_54(X)	(((X) <= (1ULL<<53)) ? __ILOG2_uint64_t_53_53(X) : __ILOG2_uint64_t_54_54(X))
#define __ILOG2_uint64_t_55_55(X)	55
#define __ILOG2_uint64_t_56_56(X)	56
#define __ILOG2_uint64_t_55_56(X)	(((X) <= (1ULL<<55)) ? __ILOG2_uint64_t_55_55(X) : __ILOG2_uint64_t_56_56(X))
#define __ILOG2_uint64_t_53_56(X)	(((X) <= (1ULL<<54)) ? __ILOG2_uint64_t_53_54(X) : __ILOG2_uint64_t_55_56(X))
#define __ILOG2_uint64_t_49_56(X)	(((X) <= (1ULL<<52)) ? __ILOG2_uint64_t_49_52(X) : __ILOG2_uint64_t_53_56(X))
#define __ILOG2_uint64_t_57_57(X)	57
#define __ILOG2_uint64_t_58_58(X)	58
#define __ILOG2_uint64_t_57_58(X)	(((X) <= (1ULL<<57)) ? __ILOG2_uint64_t_57_57(X) : __ILOG2_uint64_t_58_58(X))
#define __ILOG2_uint64_t_59_59(X)	59
#define __ILOG2_uint64_t_60_60(X)	60
#define __ILOG2_uint64_t_59_60(X)	(((X) <= (1ULL<<59)) ? __ILOG2_uint64_t_59_59(X) : __ILOG2_uint64_t_60_60(X))
#define __ILOG2_uint64_t_57_60(X)	(((X) <= (1ULL<<58)) ? __ILOG2_uint64_t_57_58(X) : __ILOG2_uint64_t_59_60(X))
#define __ILOG2_uint64_t_61_61(X)	61
#define __ILOG2_uint64_t_62_62(X)	62
#define __ILOG2_uint64_t_61_62(X)	(((X) <= (1ULL<<61)) ? __ILOG2_uint64_t_61_61(X) : __ILOG2_uint64_t_62_62(X))
#define __ILOG2_uint64_t_63_63(X)	63
#define __ILOG2_uint64_t_64_64(X)	64
#define __ILOG2_uint64_t_63_64(X)	(((X) <= (1ULL<<63)) ? __ILOG2_uint64_t_63_63(X) : __ILOG2_uint64_t_64_64(X))
#define __ILOG2_uint64_t_61_64(X)	(((X) <= (1ULL<<62)) ? __ILOG2_uint64_t_61_62(X) : __ILOG2_uint64_t_63_64(X))
#define __ILOG2_uint64_t_57_64(X)	(((X) <= (1ULL<<60)) ? __ILOG2_uint64_t_57_60(X) : __ILOG2_uint64_t_61_64(X))
#define __ILOG2_uint64_t_49_64(X)	(((X) <= (1ULL<<56)) ? __ILOG2_uint64_t_49_56(X) : __ILOG2_uint64_t_57_64(X))
#define __ILOG2_uint64_t_33_64(X)	(((X) <= (1ULL<<48)) ? __ILOG2_uint64_t_33_48(X) : __ILOG2_uint64_t_49_64(X))
#define __ILOG2_uint64_t_00_64(X)	(((X) <= (1ULL<<32)) ? __ILOG2_uint64_t_00_32(X) : __ILOG2_uint64_t_33_64(X))

#define __ILOG2_uint32_t_00_00(X)	0
#define __ILOG2_uint32_t_01_01(X)	1
#define __ILOG2_uint32_t_00_01(X)	(((X) <= (1UL<<0)) ? __ILOG2_uint32_t_00_00(X) : __ILOG2_uint32_t_01_01(X))
#define __ILOG2_uint32_t_02_02(X)	2
#define __ILOG2_uint32_t_00_02(X)	(((X) <= (1UL<<1)) ? __ILOG2_uint32_t_00_01(X) : __ILOG2_uint32_t_02_02(X))
#define __ILOG2_uint32_t_03_03(X)	3
#define __ILOG2_uint32_t_04_04(X)	4
#define __ILOG2_uint32_t_03_04(X)	(((X) <= (1UL<<3)) ? __ILOG2_uint32_t_03_03(X) : __ILOG2_uint32_t_04_04(X))
#define __ILOG2_uint32_t_00_04(X)	(((X) <= (1UL<<2)) ? __ILOG2_uint32_t_00_02(X) : __ILOG2_uint32_t_03_04(X))
#define __ILOG2_uint32_t_05_05(X)	5
#define __ILOG2_uint32_t_06_06(X)	6
#define __ILOG2_uint32_t_05_06(X)	(((X) <= (1UL<<5)) ? __ILOG2_uint32_t_05_05(X) : __ILOG2_uint32_t_06_06(X))
#define __ILOG2_uint32_t_07_07(X)	7
#define __ILOG2_uint32_t_08_08(X)	8
#define __ILOG2_uint32_t_07_08(X)	(((X) <= (1UL<<7)) ? __ILOG2_uint32_t_07_07(X) : __ILOG2_uint32_t_08_08(X))
#define __ILOG2_uint32_t_05_08(X)	(((X) <= (1UL<<6)) ? __ILOG2_uint32_t_05_06(X) : __ILOG2_uint32_t_07_08(X))
#define __ILOG2_uint32_t_00_08(X)	(((X) <= (1UL<<4)) ? __ILOG2_uint32_t_00_04(X) : __ILOG2_uint32_t_05_08(X))
#define __ILOG2_uint32_t_09_09(X)	9
#define __ILOG2_uint32_t_10_10(X)	10
#define __ILOG2_uint32_t_09_10(X)	(((X) <= (1UL<<9)) ? __ILOG2_uint32_t_09_09(X) : __ILOG2_uint32_t_10_10(X))
#define __ILOG2_uint32_t_11_11(X)	11
#define __ILOG2_uint32_t_12_12(X)	12
#define __ILOG2_uint32_t_11_12(X)	(((X) <= (1UL<<11)) ? __ILOG2_uint32_t_11_11(X) : __ILOG2_uint32_t_12_12(X))
#define __ILOG2_uint32_t_09_12(X)	(((X) <= (1UL<<10)) ? __ILOG2_uint32_t_09_10(X) : __ILOG2_uint32_t_11_12(X))
#define __ILOG2_uint32_t_13_13(X)	13
#define __ILOG2_uint32_t_14_14(X)	14
#define __ILOG2_uint32_t_13_14(X)	(((X) <= (1UL<<13)) ? __ILOG2_uint32_t_13_13(X) : __ILOG2_uint32_t_14_14(X))
#define __ILOG2_uint32_t_15_15(X)	15
#define __ILOG2_uint32_t_16_16(X)	16
#define __ILOG2_uint32_t_15_16(X)	(((X) <= (1UL<<15)) ? __ILOG2_uint32_t_15_15(X) : __ILOG2_uint32_t_16_16(X))
#define __ILOG2_uint32_t_13_16(X)	(((X) <= (1UL<<14)) ? __ILOG2_uint32_t_13_14(X) : __ILOG2_uint32_t_15_16(X))
#define __ILOG2_uint32_t_09_16(X)	(((X) <= (1UL<<12)) ? __ILOG2_uint32_t_09_12(X) : __ILOG2_uint32_t_13_16(X))
#define __ILOG2_uint32_t_00_16(X)	(((X) <= (1UL<<8)) ? __ILOG2_uint32_t_00_08(X) : __ILOG2_uint32_t_09_16(X))
#define __ILOG2_uint32_t_17_17(X)	17
#define __ILOG2_uint32_t_18_18(X)	18
#define __ILOG2_uint32_t_17_18(X)	(((X) <= (1UL<<17)) ? __ILOG2_uint32_t_17_17(X) : __ILOG2_uint32_t_18_18(X))
#define __ILOG2_uint32_t_19_19(X)	19
#define __ILOG2_uint32_t_20_20(X)	20
#define __ILOG2_uint32_t_19_20(X)	(((X) <= (1UL<<19)) ? __ILOG2_uint32_t_19_19(X) : __ILOG2_uint32_t_20_20(X))
#define __ILOG2_uint32_t_17_20(X)	(((X) <= (1UL<<18)) ? __ILOG2_uint32_t_17_18(X) : __ILOG2_uint32_t_19_20(X))
#define __ILOG2_uint32_t_21_21(X)	21
#define __ILOG2_uint32_t_22_22(X)	22
#define __ILOG2_uint32_t_21_22(X)	(((X) <= (1UL<<21)) ? __ILOG2_uint32_t_21_21(X) : __ILOG2_uint32_t_22_22(X))
#define __ILOG2_uint32_t_23_23(X)	23
#define __ILOG2_uint32_t_24_24(X)	24
#define __ILOG2_uint32_t_23_24(X)	(((X) <= (1UL<<23)) ? __ILOG2_uint32_t_23_23(X) : __ILOG2_uint32_t_24_24(X))
#define __ILOG2_uint32_t_21_24(X)	(((X) <= (1UL<<22)) ? __ILOG2_uint32_t_21_22(X) : __ILOG2_uint32_t_23_24(X))
#define __ILOG2_uint32_t_17_24(X)	(((X) <= (1UL<<20)) ? __ILOG2_uint32_t_17_20(X) : __ILOG2_uint32_t_21_24(X))
#define __ILOG2_uint32_t_25_25(X)	25
#define __ILOG2_uint32_t_26_26(X)	26
#define __ILOG2_uint32_t_25_26(X)	(((X) <= (1UL<<25)) ? __ILOG2_uint32_t_25_25(X) : __ILOG2_uint32_t_26_26(X))
#define __ILOG2_uint32_t_27_27(X)	27
#define __ILOG2_uint32_t_28_28(X)	28
#define __ILOG2_uint32_t_27_28(X)	(((X) <= (1UL<<27)) ? __ILOG2_uint32_t_27_27(X) : __ILOG2_uint32_t_28_28(X))
#define __ILOG2_uint32_t_25_28(X)	(((X) <= (1UL<<26)) ? __ILOG2_uint32_t_25_26(X) : __ILOG2_uint32_t_27_28(X))
#define __ILOG2_uint32_t_29_29(X)	29
#define __ILOG2_uint32_t_30_30(X)	30
#define __ILOG2_uint32_t_29_30(X)	(((X) <= (1UL<<29)) ? __ILOG2_uint32_t_29_29(X) : __ILOG2_uint32_t_30_30(X))
#define __ILOG2_uint32_t_31_31(X)	31
#define __ILOG2_uint32_t_32_32(X)	32
#define __ILOG2_uint32_t_31_32(X)	(((X) <= (1UL<<31)) ? __ILOG2_uint32_t_31_31(X) : __ILOG2_uint32_t_32_32(X))
#define __ILOG2_uint32_t_29_32(X)	(((X) <= (1UL<<30)) ? __ILOG2_uint32_t_29_30(X) : __ILOG2_uint32_t_31_32(X))
#define __ILOG2_uint32_t_25_32(X)	(((X) <= (1UL<<28)) ? __ILOG2_uint32_t_25_28(X) : __ILOG2_uint32_t_29_32(X))
#define __ILOG2_uint32_t_17_32(X)	(((X) <= (1UL<<24)) ? __ILOG2_uint32_t_17_24(X) : __ILOG2_uint32_t_25_32(X))
#define __ILOG2_uint32_t_00_32(X)	(((X) <= (1UL<<16)) ? __ILOG2_uint32_t_00_16(X) : __ILOG2_uint32_t_17_32(X))

#define __ILOG2_uint16_t_00_00(X)	0
#define __ILOG2_uint16_t_01_01(X)	1
#define __ILOG2_uint16_t_00_01(X)	(((X) <= (1<<0)) ? __ILOG2_uint16_t_00_00(X) : __ILOG2_uint16_t_01_01(X))
#define __ILOG2_uint16_t_02_02(X)	2
#define __ILOG2_uint16_t_00_02(X)	(((X) <= (1<<1)) ? __ILOG2_uint16_t_00_01(X) : __ILOG2_uint16_t_02_02(X))
#define __ILOG2_uint16_t_03_03(X)	3
#define __ILOG2_uint16_t_04_04(X)	4
#define __ILOG2_uint16_t_03_04(X)	(((X) <= (1<<3)) ? __ILOG2_uint16_t_03_03(X) : __ILOG2_uint16_t_04_04(X))
#define __ILOG2_uint16_t_00_04(X)	(((X) <= (1<<2)) ? __ILOG2_uint16_t_00_02(X) : __ILOG2_uint16_t_03_04(X))
#define __ILOG2_uint16_t_05_05(X)	5
#define __ILOG2_uint16_t_06_06(X)	6
#define __ILOG2_uint16_t_05_06(X)	(((X) <= (1<<5)) ? __ILOG2_uint16_t_05_05(X) : __ILOG2_uint16_t_06_06(X))
#define __ILOG2_uint16_t_07_07(X)	7
#define __ILOG2_uint16_t_08_08(X)	8
#define __ILOG2_uint16_t_07_08(X)	(((X) <= (1<<7)) ? __ILOG2_uint16_t_07_07(X) : __ILOG2_uint16_t_08_08(X))
#define __ILOG2_uint16_t_05_08(X)	(((X) <= (1<<6)) ? __ILOG2_uint16_t_05_06(X) : __ILOG2_uint16_t_07_08(X))
#define __ILOG2_uint16_t_00_08(X)	(((X) <= (1<<4)) ? __ILOG2_uint16_t_00_04(X) : __ILOG2_uint16_t_05_08(X))
#define __ILOG2_uint16_t_09_09(X)	9
#define __ILOG2_uint16_t_10_10(X)	10
#define __ILOG2_uint16_t_09_10(X)	(((X) <= (1<<9)) ? __ILOG2_uint16_t_09_09(X) : __ILOG2_uint16_t_10_10(X))
#define __ILOG2_uint16_t_11_11(X)	11
#define __ILOG2_uint16_t_12_12(X)	12
#define __ILOG2_uint16_t_11_12(X)	(((X) <= (1<<11)) ? __ILOG2_uint16_t_11_11(X) : __ILOG2_uint16_t_12_12(X))
#define __ILOG2_uint16_t_09_12(X)	(((X) <= (1<<10)) ? __ILOG2_uint16_t_09_10(X) : __ILOG2_uint16_t_11_12(X))
#define __ILOG2_uint16_t_13_13(X)	13
#define __ILOG2_uint16_t_14_14(X)	14
#define __ILOG2_uint16_t_13_14(X)	(((X) <= (1<<13)) ? __ILOG2_uint16_t_13_13(X) : __ILOG2_uint16_t_14_14(X))
#define __ILOG2_uint16_t_15_15(X)	15
#define __ILOG2_uint16_t_16_16(X)	16
#define __ILOG2_uint16_t_15_16(X)	(((X) <= (1<<15)) ? __ILOG2_uint16_t_15_15(X) : __ILOG2_uint16_t_16_16(X))
#define __ILOG2_uint16_t_13_16(X)	(((X) <= (1<<14)) ? __ILOG2_uint16_t_13_14(X) : __ILOG2_uint16_t_15_16(X))
#define __ILOG2_uint16_t_09_16(X)	(((X) <= (1<<12)) ? __ILOG2_uint16_t_09_12(X) : __ILOG2_uint16_t_13_16(X))
#define __ILOG2_uint16_t_00_16(X)	(((X) <= (1<<8)) ? __ILOG2_uint16_t_00_08(X) : __ILOG2_uint16_t_09_16(X))

#define __ILOG2_uint8_t_00_00(X)	0
#define __ILOG2_uint8_t_01_01(X)	1
#define __ILOG2_uint8_t_00_01(X)	(((X) <= (1<<0)) ? __ILOG2_uint8_t_00_00(X) : __ILOG2_uint8_t_01_01(X))
#define __ILOG2_uint8_t_02_02(X)	2
#define __ILOG2_uint8_t_00_02(X)	(((X) <= (1<<1)) ? __ILOG2_uint8_t_00_01(X) : __ILOG2_uint8_t_02_02(X))
#define __ILOG2_uint8_t_03_03(X)	3
#define __ILOG2_uint8_t_04_04(X)	4
#define __ILOG2_uint8_t_03_04(X)	(((X) <= (1<<3)) ? __ILOG2_uint8_t_03_03(X) : __ILOG2_uint8_t_04_04(X))
#define __ILOG2_uint8_t_00_04(X)	(((X) <= (1<<2)) ? __ILOG2_uint8_t_00_02(X) : __ILOG2_uint8_t_03_04(X))
#define __ILOG2_uint8_t_05_05(X)	5
#define __ILOG2_uint8_t_06_06(X)	6
#define __ILOG2_uint8_t_05_06(X)	(((X) <= (1<<5)) ? __ILOG2_uint8_t_05_05(X) : __ILOG2_uint8_t_06_06(X))
#define __ILOG2_uint8_t_07_07(X)	7
#define __ILOG2_uint8_t_08_08(X)	8
#define __ILOG2_uint8_t_07_08(X)	(((X) <= (1<<7)) ? __ILOG2_uint8_t_07_07(X) : __ILOG2_uint8_t_08_08(X))
#define __ILOG2_uint8_t_05_08(X)	(((X) <= (1<<6)) ? __ILOG2_uint8_t_05_06(X) : __ILOG2_uint8_t_07_08(X))
#define __ILOG2_uint8_t_00_08(X)	(((X) <= (1<<4)) ? __ILOG2_uint8_t_00_04(X) : __ILOG2_uint8_t_05_08(X))

/**
 * Find upper estimate for log2(n) so that (1<<ilog2(n)) >= n
 * @return (n==0)?0:int(ceil(log2(n)))
 */
int ilog2_u64(uint64_t n) {
	return __ILOG2_uint64_t_00_64(n);
}

int ilog2_u32(uint32_t n) {
	return __ILOG2_uint32_t_00_32(n);
}

int ilog2_u16(uint16_t n) {
	return __ILOG2_uint16_t_00_16(n);
}

int ilog2_u8(uint8_t n) {
	return __ILOG2_uint8_t_00_08(n);
}

#define __ILOG10_uint64_t_00_00(X)	0
#define __ILOG10_uint64_t_01_01(X)	1
#define __ILOG10_uint64_t_00_01(X)	(((X) <= 1ULL) ? __ILOG10_uint64_t_00_00(X) : __ILOG10_uint64_t_01_01(X))
#define __ILOG10_uint64_t_02_02(X)	2
#define __ILOG10_uint64_t_00_02(X)	(((X) <= 10ULL) ? __ILOG10_uint64_t_00_01(X) : __ILOG10_uint64_t_02_02(X))
#define __ILOG10_uint64_t_03_03(X)	3
#define __ILOG10_uint64_t_04_04(X)	4
#define __ILOG10_uint64_t_03_04(X)	(((X) <= 1000ULL) ? __ILOG10_uint64_t_03_03(X) : __ILOG10_uint64_t_04_04(X))
#define __ILOG10_uint64_t_05_05(X)	5
#define __ILOG10_uint64_t_03_05(X)	(((X) <= 10000ULL) ? __ILOG10_uint64_t_03_04(X) : __ILOG10_uint64_t_05_05(X))
#define __ILOG10_uint64_t_00_05(X)	(((X) <= 100ULL) ? __ILOG10_uint64_t_00_02(X) : __ILOG10_uint64_t_03_05(X))
#define __ILOG10_uint64_t_06_06(X)	6
#define __ILOG10_uint64_t_07_07(X)	7
#define __ILOG10_uint64_t_06_07(X)	(((X) <= 1000000ULL) ? __ILOG10_uint64_t_06_06(X) : __ILOG10_uint64_t_07_07(X))
#define __ILOG10_uint64_t_08_08(X)	8
#define __ILOG10_uint64_t_06_08(X)	(((X) <= 10000000ULL) ? __ILOG10_uint64_t_06_07(X) : __ILOG10_uint64_t_08_08(X))
#define __ILOG10_uint64_t_09_09(X)	9
#define __ILOG10_uint64_t_10_10(X)	10
#define __ILOG10_uint64_t_09_10(X)	(((X) <= 1000000000ULL) ? __ILOG10_uint64_t_09_09(X) : __ILOG10_uint64_t_10_10(X))
#define __ILOG10_uint64_t_06_10(X)	(((X) <= 100000000ULL) ? __ILOG10_uint64_t_06_08(X) : __ILOG10_uint64_t_09_10(X))
#define __ILOG10_uint64_t_00_10(X)	(((X) <= 100000ULL) ? __ILOG10_uint64_t_00_05(X) : __ILOG10_uint64_t_06_10(X))
#define __ILOG10_uint64_t_11_11(X)	11
#define __ILOG10_uint64_t_12_12(X)	12
#define __ILOG10_uint64_t_11_12(X)	(((X) <= 100000000000ULL) ? __ILOG10_uint64_t_11_11(X) : __ILOG10_uint64_t_12_12(X))
#define __ILOG10_uint64_t_13_13(X)	13
#define __ILOG10_uint64_t_11_13(X)	(((X) <= 1000000000000ULL) ? __ILOG10_uint64_t_11_12(X) : __ILOG10_uint64_t_13_13(X))
#define __ILOG10_uint64_t_14_14(X)	14
#define __ILOG10_uint64_t_15_15(X)	15
#define __ILOG10_uint64_t_14_15(X)	(((X) <= 100000000000000ULL) ? __ILOG10_uint64_t_14_14(X) : __ILOG10_uint64_t_15_15(X))
#define __ILOG10_uint64_t_11_15(X)	(((X) <= 10000000000000ULL) ? __ILOG10_uint64_t_11_13(X) : __ILOG10_uint64_t_14_15(X))
#define __ILOG10_uint64_t_16_16(X)	16
#define __ILOG10_uint64_t_17_17(X)	17
#define __ILOG10_uint64_t_16_17(X)	(((X) <= 10000000000000000ULL) ? __ILOG10_uint64_t_16_16(X) : __ILOG10_uint64_t_17_17(X))
#define __ILOG10_uint64_t_18_18(X)	18
#define __ILOG10_uint64_t_16_18(X)	(((X) <= 100000000000000000ULL) ? __ILOG10_uint64_t_16_17(X) : __ILOG10_uint64_t_18_18(X))
#define __ILOG10_uint64_t_19_19(X)	19
#define __ILOG10_uint64_t_20_20(X)	20
#define __ILOG10_uint64_t_19_20(X)	(((X) <= 10000000000000000000ULL) ? __ILOG10_uint64_t_19_19(X) : __ILOG10_uint64_t_20_20(X))
#define __ILOG10_uint64_t_16_20(X)	(((X) <= 1000000000000000000ULL) ? __ILOG10_uint64_t_16_18(X) : __ILOG10_uint64_t_19_20(X))
#define __ILOG10_uint64_t_11_20(X)	(((X) <= 1000000000000000ULL) ? __ILOG10_uint64_t_11_15(X) : __ILOG10_uint64_t_16_20(X))
#define __ILOG10_uint64_t_00_20(X)	(((X) <= 10000000000ULL) ? __ILOG10_uint64_t_00_10(X) : __ILOG10_uint64_t_11_20(X))

#define __ILOG10_uint32_t_00_00(X)	0
#define __ILOG10_uint32_t_01_01(X)	1
#define __ILOG10_uint32_t_00_01(X)	(((X) <= 1UL) ? __ILOG10_uint32_t_00_00(X) : __ILOG10_uint32_t_01_01(X))
#define __ILOG10_uint32_t_02_02(X)	2
#define __ILOG10_uint32_t_00_02(X)	(((X) <= 10UL) ? __ILOG10_uint32_t_00_01(X) : __ILOG10_uint32_t_02_02(X))
#define __ILOG10_uint32_t_03_03(X)	3
#define __ILOG10_uint32_t_04_04(X)	4
#define __ILOG10_uint32_t_03_04(X)	(((X) <= 1000UL) ? __ILOG10_uint32_t_03_03(X) : __ILOG10_uint32_t_04_04(X))
#define __ILOG10_uint32_t_05_05(X)	5
#define __ILOG10_uint32_t_03_05(X)	(((X) <= 10000UL) ? __ILOG10_uint32_t_03_04(X) : __ILOG10_uint32_t_05_05(X))
#define __ILOG10_uint32_t_00_05(X)	(((X) <= 100UL) ? __ILOG10_uint32_t_00_02(X) : __ILOG10_uint32_t_03_05(X))
#define __ILOG10_uint32_t_06_06(X)	6
#define __ILOG10_uint32_t_07_07(X)	7
#define __ILOG10_uint32_t_06_07(X)	(((X) <= 1000000UL) ? __ILOG10_uint32_t_06_06(X) : __ILOG10_uint32_t_07_07(X))
#define __ILOG10_uint32_t_08_08(X)	8
#define __ILOG10_uint32_t_06_08(X)	(((X) <= 10000000UL) ? __ILOG10_uint32_t_06_07(X) : __ILOG10_uint32_t_08_08(X))
#define __ILOG10_uint32_t_09_09(X)	9
#define __ILOG10_uint32_t_10_10(X)	10
#define __ILOG10_uint32_t_09_10(X)	(((X) <= 1000000000UL) ? __ILOG10_uint32_t_09_09(X) : __ILOG10_uint32_t_10_10(X))
#define __ILOG10_uint32_t_06_10(X)	(((X) <= 100000000UL) ? __ILOG10_uint32_t_06_08(X) : __ILOG10_uint32_t_09_10(X))
#define __ILOG10_uint32_t_00_10(X)	(((X) <= 100000UL) ? __ILOG10_uint32_t_00_05(X) : __ILOG10_uint32_t_06_10(X))

#define __ILOG10_uint16_t_00_00(X)	0
#define __ILOG10_uint16_t_01_01(X)	1
#define __ILOG10_uint16_t_00_01(X)	(((X) <= 1) ? __ILOG10_uint16_t_00_00(X) : __ILOG10_uint16_t_01_01(X))
#define __ILOG10_uint16_t_02_02(X)	2
#define __ILOG10_uint16_t_00_02(X)	(((X) <= 10) ? __ILOG10_uint16_t_00_01(X) : __ILOG10_uint16_t_02_02(X))
#define __ILOG10_uint16_t_03_03(X)	3
#define __ILOG10_uint16_t_04_04(X)	4
#define __ILOG10_uint16_t_03_04(X)	(((X) <= 1000) ? __ILOG10_uint16_t_03_03(X) : __ILOG10_uint16_t_04_04(X))
#define __ILOG10_uint16_t_05_05(X)	5
#define __ILOG10_uint16_t_03_05(X)	(((X) <= 10000) ? __ILOG10_uint16_t_03_04(X) : __ILOG10_uint16_t_05_05(X))
#define __ILOG10_uint16_t_00_05(X)	(((X) <= 100) ? __ILOG10_uint16_t_00_02(X) : __ILOG10_uint16_t_03_05(X))

#define __ILOG10_uint8_t_00_00(X)	0
#define __ILOG10_uint8_t_01_01(X)	1
#define __ILOG10_uint8_t_00_01(X)	(((X) <= 1) ? __ILOG10_uint8_t_00_00(X) : __ILOG10_uint8_t_01_01(X))
#define __ILOG10_uint8_t_02_02(X)	2
#define __ILOG10_uint8_t_03_03(X)	3
#define __ILOG10_uint8_t_02_03(X)	(((X) <= 100) ? __ILOG10_uint8_t_02_02(X) : __ILOG10_uint8_t_03_03(X))
#define __ILOG10_uint8_t_00_03(X)	(((X) <= 10) ? __ILOG10_uint8_t_00_01(X) : __ILOG10_uint8_t_02_03(X))

/**
 * Find upper estimate for log10(n) so that (10**ilog10(n)) >= n
 * @return (n==0)?0:int(ceil(log10(n)))
 */
int ilog10_u64(uint64_t n) {
	return __ILOG10_uint64_t_00_20(n);
}

int ilog10_u32(uint32_t n) {
	return __ILOG10_uint32_t_00_10(n);
}

int ilog10_u16(uint16_t n) {
	return __ILOG10_uint16_t_00_05(n);
}

int ilog10_u8(uint8_t n) {
	return __ILOG10_uint8_t_00_03(n);
}
