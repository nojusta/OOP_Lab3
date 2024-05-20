#include "myVector.h"

extern "C" MyVector<int>* createAndFillMyVector() {
    MyVector<int>* vec = new MyVector<int>();
    vec->push_back(1);
    vec->push_back(2);
    vec->push_back(3);
    return vec;
}