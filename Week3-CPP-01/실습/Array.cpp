#include <iostream>
#include "Array.h"

using namespace std;

Array :: Array(int size){
	if (size <= 0){
		cout<<"Error: Size Smaller than 1"<<endl;
	}
	else {
		data = new int[size];
		len = size;
	}
}

Array :: ~Array() {
	delete []data;
}


int Array :: length() const {
	return len;
}

int & Array :: operator [] (int i) {
	static int tmp;
	if ((i < len)&&(0 <= i)){
		return data[i];
	}
	else {
		cout<<"Array Bound Error!"<<endl;
		return tmp;
	}
}

int Array :: operator [] (int i) const {
	static int tmp;
	if ((i < len)&&(0 <= i)){
		return data[i];
	}
	else {
		cout<<"Array Bound Error!"<<endl;
		return 0;
	}
}

void Array :: print (void) {
	int j;
	cout<<"[";
	for (j=0; j<len; j++) {
		cout<<" "<<data[j];
	}
	cout<<"]"<<endl;
}
