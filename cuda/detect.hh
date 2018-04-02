#ifndef __DETECT_H__
#define __DETECT_H__

#include <inttypes.h>
#include "transpose.hh"

struct Link {
	uint16_t len;
	union {
		uint16_t pos;
		uint16_t prev;
	} c;
};

namespace Match {
	class Detect {
	public:
		const char *d_ibuf;
		Link *d_obuf;
		Link *d_tobuf;
		Link *obuf;
		unsigned *d_nlink;
		unsigned *d_nlink_block;
		unsigned nlinkmax;
		int width;
		const char *err;
		char errbuf[512];
	public:
		Detect(const char *d_ibuf, Link *ob, int w);
		operator bool() const;
		~Detect();
		unsigned run();
	};
};

#endif // __DETECT_H__
