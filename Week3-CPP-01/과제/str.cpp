#include "str.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

Str :: Str(int leng){
	len = leng;
}

Str :: Str(char *neyong){
	len = strlen(neyong);
	str = new char [len+1];
	strcpy(str, neyong);	
}

Str :: ~Str(void) {
	delete[] str;
	return;
}

int Str :: length(void) {
	return len;
}

char* Str :: contents(void) {
	return str;
}

int Str :: compare(class Str& a){
	return strcmp(str, a.str);
}

int Str :: compare(char *a){
	return strcmp(str, a);
}

void Str :: operator = (char *a){
	delete[] str;
	len = strlen(a);
	str = new char [len+1];
	strcpy(str, a);
}

void Str :: operator = (class Str& a) {
	delete[] str;
	len = strlen(a.str);
	str = new char [len+1];
	strcpy(str, a.str);
}
