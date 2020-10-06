#ifndef __ARRAY__
#define __ARRAY__

#include <iostream>

using namespace std;

template <class T>
class Array {
	protected:
		T *data;
		int len;
	public:
		Array(int size){
			if (size <= 0){
				cout<<"Error: Size Smaller than 1"<<endl;
			}
			else {
				data = new T[size];
				len = size;
			}		
		}

		~Array(){
			delete []data;
		}

		int length() const{
			return len;
		}

		virtual T & operator [] (int i){
			static T tmp;
			if ((i < len)&&(0 <= i)){
				return data[i];
			}
			else {
				cout<<"Array Bound Error!"<<endl;
				return tmp;
			}
		}


		virtual T operator [] (int i) const{
			static T tmp;
			if ((i < len)&&(0 <= i)){
				return data[i];
			}
			else {
				cout<<"Array Bound Error!"<<endl;
				return 0;
			}
		}
		void print(){
			int j;
			cout<<"[";
			for (j=0; j<len; j++) {
				cout<<" "<<data[j];
			}
			cout<<"]"<<endl;
		}
};

#endif
