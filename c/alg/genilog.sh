#!/bin/bash
# or
#!/bin/ksh
#
# render efficient ilog functions
# 3x faster than binary search in a loop
# 2x faster than int(ceil(log(n))) version
#

function render_ilog2 {
	itype="${1}" # e.g. uint64_t
	ctype="${2}" # e.g. ULL
	typeset -i f="${3}"
	typeset -i t="${4}"
	if [ "${f}" == "${t}" ]; then
		printf "#define __ILOG2_%s_%02d_%02d(X)	%d\n" "${itype}" "${f}" "${t}" "${f}"
	else
		typeset -i m=$(((t+f)/2))
		render_ilog2 "${itype}" "${ctype}" "${f}" "${m}"
		render_ilog2 "${itype}" "${ctype}" "$((m+1))" "${t}"
		printf "#define __ILOG2_%s_%02d_%02d(X)	(((X) <= (1%s<<%d)) ? __ILOG2_%s_%02d_%02d(X) : __ILOG2_%s_%02d_%02d(X))\n" "${itype}" "${f}" "${t}" "${ctype}" "${m}" "${itype}" "${f}" "${m}" "${itype}" "$((m+1))" "${t}"
	fi
}

function render_ilog10 {
	itype="${1}" # e.g. uint64_t
	ctype="${2}" # e.g. ULL
	typeset -i f="${3}"
	typeset -i t="${4}"
	if [ "${f}" == "${t}" ]; then
		printf "#define __ILOG10_%s_%02d_%02d(X)	%d\n" $itype $f $t $f
	else
		typeset -i m=$(((t+f)/2))
		render_ilog10 "${itype}" "${ctype}" "${f}" "${m}"
		render_ilog10 "${itype}" "${ctype}" "$((m+1))" "${t}"
		ds="1"
		for ((i=0;i<m;i++)); do
			ds="${ds}0"
		done
		printf "#define __ILOG10_%s_%02d_%02d(X)	(((X) <= %s%s) ? __ILOG10_%s_%02d_%02d(X) : __ILOG10_%s_%02d_%02d(X))\n" "${itype}" "${f}" "${t}" "${ds}" "${ctype}" "${itype}" "${f}" "${m}" "${itype}" "$((m+1))" "${t}"
	fi
}

# render .c file
gen_c() {
	cat <<'EOF'
/********* Automatically generated file - don't edit **********/
/**** entire family of ilog_u functions for each arg size *****/

#include "ilog.h"

EOF
	render_ilog2 uint64_t ULL 0 64
	echo
	render_ilog2 uint32_t UL 0 32
	echo 
	render_ilog2 uint16_t '' 0 16
	echo 
	render_ilog2 uint8_t '' 0 8
	cat <<'EOF'

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

EOF
	render_ilog10 uint64_t ULL 0 20
	echo 
	render_ilog10 uint32_t UL 0 10
	echo 
	render_ilog10 uint16_t '' 0 5
	echo 
	render_ilog10 uint8_t '' 0 3
	cat <<'EOF'

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
EOF

}

# render .h file
gen_h() {
	cat <<'EOF'
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
EOF
}

#
# MAIN
#

set -e

# C code
gen_h >ilog.h.new
gen_c >ilog.c.new
mv ilog.h.new ilog.h
mv ilog.c.new ilog.c
