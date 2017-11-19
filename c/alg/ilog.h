/********* Automatically generated file - don't edit **********/
/**** entire family of ilog_u functions for each arg size *****/

#ifndef __ILOG_H__
#define __ILOG_H__

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Find upper estimate for log2(n) so that (1<<ilog2(n)) >= n
 * @return (n==0)?0:int(ceil(log2(n)))
 */
int ilog2_u64(uint64_t n);
int ilog2_u32(uint32_t n);
int ilog2_u16(uint16_t n);
int ilog2_u8(uint8_t n);

/**
 * Find upper estimate for log10(n) so that (10**ilog10(n)) >= n
 * @return (n==0)?0:int(ceil(log10(n)))
 */
int ilog10_u64(uint64_t n);
int ilog10_u32(uint32_t n);
int ilog10_u16(uint16_t n);
int ilog10_u8(uint8_t n);

#ifdef __cplusplus
}
#endif
#endif /* __ILOG_H_ */
