#include "RangeArray.h"
#include <iostream>

using namespace std;

RangeArray :: RangeArray (int start, int finish) : Array (finish-start +1) {
	base = start;
	end = finish;
}

RangeArray :: ~RangeArray (void){
	
}

int & RangeArray :: operator [] (int i) {
	Array:: operator [] (i-base);
}

int RangeArray :: operator [] (int i) const {
	Array::operator [](i-base);
}

int RangeArray :: baseValue (void) {
	return base;
}

int RangeArray :: endValue (void) {
	return end;
}
