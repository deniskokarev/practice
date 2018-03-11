#ifndef __DETECT_H__
#define __DETECT_H__

#include <inttypes.h>
#include "transpose.hh"

struct Link {
	uint16_t len;
	uint16_t prev;
};

namespace Match {
	class Detect {
	public:
		const char *d_ibuf;
		Link *d_obuf;
		Link *obuf;
		unsigned *d_nlink;
		unsigned *d_nlink_block;
		unsigned nlinkmax;
		int width;
	public:
		Detect(const char *d_ibuf);
		int init(Link *ob, int w);
		~Detect();
		unsigned run();
	};
};

#endif // __DETECT_H__
