#ifndef __RANGEARRAY__
#define __RANGEARRAY__

#include "Array.h"

class RangeArray : public Array {
	protected:
	int base;
	int end;

	public:
		RangeArray(int start, int finish);
		~RangeArray();
		
		int & operator [](int i);
		int operator [](int i) const;
		int baseValue();
		int endValue();

};

#endif
