#include "MyVector.h"
#include <iostream>

Vector::Vector(const Value* rawArray, const size_t size, float coef){
    _size = size;
    _capacity = size;
    _multiplicativeCoef = coef;
    _data = new Value[_size];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = rawArray[i];
    }
}

//деструктор
Vector::~Vector()             
{
    delete[] _data;
};

Vector::Vector(const Vector& other){
    _data = new Value [other._capacity];
    _capacity = other._capacity;
    insert(other._data, _capacity, 0);
}

Vector& Vector::operator=(const Vector& other){
    if(this == &other){
        return *this; 
    }
    else{
        delete[] _data;
        Value* _data = other._data;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;
        insert(other._data, other.size(), 0);
        return *this;
    }
}


Vector::Vector(Vector&& other) noexcept{
    Value* _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    _multiplicativeCoef = other._multiplicativeCoef;
    insert(other._data, other.size(), 0);
}
Vector& Vector::operator=(Vector&&other) noexcept{
    if (this == &other){
        return *this; 
    }
    else{
        Value*  _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;
        insert(other._data, other.size(), 0);
        other._data = nullptr;
        return *this;
    }
}

void Vector::pushBack(const Value& value){
    if (_data == nullptr) {
        _data = new Value[_capacity]; 
    }
    _size++;
    if (_size > _capacity) {
        _capacity = _capacity * _multiplicativeCoef;
    }
    Value* tmp = new Value[_capacity];
    for (size_t i = 0; i < _size; i++) {
        tmp[i] = _data[i];
    }
    delete[] _data;
    _data = tmp;
    _data[_size - 1] = value;
}

void Vector::pushFront(const Value& value){
    if (_data == nullptr) {
        _data = new Value[_capacity]; 
    }
    _size++;
    if (_size > _capacity) {
        _capacity = _capacity * _multiplicativeCoef;
    }
    Value* tmp = new Value[_capacity];
    tmp[0] = value;
    for (size_t i = 1; i < _size; i++) {
        tmp[i] = _data[i-1];
    }
    delete[] _data;
    _data = tmp;
}

void Vector::insert(const Value& value, size_t pos){
    if (_data == nullptr) {
        _data = new Value[_capacity]; 
    }
    if (pos == _size){
        pushBack(value);
    }
    else{
        _size++;
        if(_capacity <= _size){
            _capacity = _capacity * _multiplicativeCoef;
        }
        Value* tmp = new Value[_capacity];
        for (size_t i = 0; i < pos; i++) {
            tmp[i] = _data[i];
        }        
        tmp[pos] = value;
        for (size_t j = pos + 1; j < _size; j++){
            tmp[j] = _data[j - 1];
        }
        delete[] _data;
        _data = tmp;
    }
}

void Vector::insert(const Value* values, size_t size, size_t pos){
    if (_data == nullptr){
        _data = new Value[_capacity];
    }
    _size += size;
    if (_capacity < _size){
        _capacity = _capacity * _multiplicativeCoef;
    }
    Value* tmp = new Value[_capacity];
    for (size_t i = 0; i < pos; i++) {
        tmp[i] = _data[i];
    }
    for (size_t j = 0; j < size; j++){
        tmp[pos + j] = values[j];
    }
    for (size_t g = pos + size; g < _size; g++){
        tmp[g] = _data[g - size];
    }
    delete[] _data;
    _data = tmp;
}

void Vector::insert(const Vector& vector, size_t pos){
    insert(vector._data, vector.size(), pos);
}

void Vector::popBack(){
    _size--;
}

void Vector::popFront(){
    erase(0, 1);
} 
 
void Vector::erase(size_t pos, size_t count){
    if (_data == nullptr){
        _data = new Value[_capacity];
    }
    if (pos + count >= _size){
        count = _size - pos;
    }
    for (size_t i = pos + count; i < _size; i++){
        _data[i - count] = _data[i];
    }
    size_t size_ = _size - count;
    double lf = loadFactor();
    _size -= count;
    if (lf * _multiplicativeCoef > 1){
        reserve(_multiplicativeCoef * size_);    
    }
}

Value& Vector::operator[](size_t idx){
   return _data[idx];
}

const Value& Vector::operator[](size_t idx) const{
    return _data[idx];
}

void Vector::shrinkToFit(){
    if (_capacity > _size){
        _capacity = _size;
    }
    Value* tmp = new Value[_capacity];
    for (size_t i = 0; i < _size; i++){
        tmp[i] = _data[i];
    }
    delete[] _data;
    _data = tmp; 
}


long long Vector::find(const Value& value) const{
    for(long long i = 0; i < _size; i++){
        if(_data[i] == value){
            return i;
        }
    }
    return -1;
}

void Vector::reserve(size_t capacity){
    if (capacity > _size) {
        Value* tmp = new Value[capacity];
        _capacity = capacity;
        for (size_t i = 0; i < _size; i++) {
          tmp[i] = _data[i];
        }
        delete[] _data;
        _data = tmp;
    }
}

void Vector::eraseBetween(size_t beginPos, size_t endPos){
    erase(beginPos, endPos - beginPos);
}

size_t Vector::size() const
{
    return _size;
}

size_t Vector::capacity() const
{
    return _capacity;
}

double Vector::loadFactor() const
{
    return (double) _size / _capacity;
}
