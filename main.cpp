#include "MyVector.h"
#include "MyVector.h"
#include <iostream>

Vector::Vector(const Value* rawArray, const size_t size, float coef){
    _data = new Value[_size];
    _size = size;
    _capacity = size;
    _multiplicativeCoef = coef;
}
//деструктор
Vector::~Vector()             
{
    delete[] _data;
};
//
void Vector::pushBack(const Value& value){
    if (_size >= _capacity){
        _capacity = _capacity * 2;
        Value* tmp = _data;
        _data = new Value[_capacity];
        for (size_t i = 0; i < _size; ++i){
            _data[i] = tmp[i];
        }
        delete[] tmp; 
    }
    _data[_size + 1] = value;
}

void Vector::pushFront(const Value& value){
        _capacity = _capacity * 2;
        Value* tmp = _data;
        _data = new Value[_capacity];
        for (size_t i = 0; i < _size; ++i){
            if (i = 0) {
                _data[i] = value;
            }
            _data[i] = tmp[i];
        }
        delete[] tmp; 
}

void Vector::insert(const Value& value, size_t pos){
    _capacity = _capacity * 2;
    Value* tmp = _data;
    _data = new Value[_capacity];
    for (size_t i = 0; i < _size; ++i){
        if (i = pos) {
            _data[i] = value;
            i += 1;
        }
        _data[i] = tmp[i];
    }
    delete[] tmp; 
}

void Vector::insert(const Value* values, size_t size, size_t pos){
    _capacity = _capacity * 2;
    Value* tmp = _data;
    _data = new Value[_capacity];
    for (size_t i = 0; i < _size; ++i){
        if (i = pos) {
            while(size > 0){
                _data[i] = *values;
                i += 1;
                size -= 1;
            }
        }
        _data[i] = tmp[i];
    }
    delete[] tmp;
}

void Vector::insert(const Vector& vector, size_t pos){
    _capacity = _capacity * 2;
    Value* tmp = _data;
    _data = new Value[_capacity];
    for (size_t i = 0; i < _size; ++i){
        if (i = pos) {
            for(size_t j = 0; j < vector.size(); j++){
                _data[j] = vector[j];
                i = j;
            }
        }
        _data[i] = tmp[i];
    }
    delete[] tmp;
}



/*
void Vector::popBack(){
    _size--;  
}
*/
size_t Vector::size() const
{
    return _size;
}

size_t Vector::capacity() const
{
    return _capacity;
}

double Vector::loadFactor() const{
    return _size / _capacity;
}

int main(){
    std::cout << "Hello, world";
}
