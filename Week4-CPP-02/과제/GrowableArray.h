#ifndef __GROWABLEARRAY__
#define __GROWABLEARRAY__
#include "Array.h"

template <class T>
class GrowableArray:public Array<T> {
    public:
        GrowableArray(int size) : Array<T> (size){

        }
        ~GrowableArray(){

        }

        virtual T & operator[] (int i){
            if (this->len <= i){
                int newlen = i*2;
                T* temp;
                temp = new T[newlen] {0};

                for (int j = 0; j <this->len; j++){
                    temp[j] = (this->data)[j];
                }

                delete[] (this->data);
                this->data = temp;
                this->len = newlen;
            }
            return Array<T>::operator[](i);
        }

        virtual T operator[] (int i) const {
            return Array<T>::operator[](i);  
        }
};

#endif