#include "Vector.h"
#include <iostream>

Vector::Vector(const Value* rawArray, const size_t size, float coef) {
    _size = size;
    _capacity = size;
    _multiplicativeCoef = coef;
    _data = new Value[_size];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = rawArray[i];
    }
}

Vector::~Vector()             
{
    delete[] _data;
};

Vector::Vector(const Vector& other {
    _data = new Value [other._size];
    _capacity = other._size;
    insert(other._data, other._size, 0);
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this; 
    }
    else {
        delete[] _data;
        _data = new Value[other._size]; 
        _capacity = other._size;
        _multiplicativeCoef = other._multiplicativeCoef;
        insert(other._data, other.size(), 0);
        return *this;
    }
}

Vector::Vector(Vector&& other) noexcept {
    _data = other._data;
    _size = other._size;
    _capacity = other._size;    
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    _multiplicativeCoef = 0;
}

Vector& Vector::operator=(Vector&&other) noexcept {
    if (this == &other) {
        return *this; 
    }
    else {
        delete[] _data;
        _data = other._data;
        _size = other._size;
        _capacity = other._size;    
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
        _multiplicativeCoef = 0;
        return *this;
    }
}

void Vector::pushBack(const Value& value) {
    if ((_data == nullptr) || (_capacity == 0)) {
        _capacity = _multiplicativeCoef;
        _data = new Value[_capacity]; 
    }
    _size++;
    if (_size > _capacity) {
        _capacity = _capacity * _multiplicativeCoef;
    }
    _data[_size - 1] = value;
}

void Vector::pushFront(const Value& value) {
    if ((_data == nullptr) || (_capacity == 0)) {
        _capacity = _multiplicativeCoef;
        _data = new Value[_capacity]; 
    }
    _size++;
    if (_size > _capacity) {
        _capacity = _capacity * _multiplicativeCoef;
    }
    for (size_t i = 1; i < _size; i++) {
        _data[i] = _data[i+1];
    }
}

void Vector::insert(const Value& value, size_t pos) {
    if ((_data == nullptr) || (_capacity == 0)) {
        _capacity = _multiplicativeCoef;
        _data = new Value[_capacity]; 
    }
    if (pos == _size) {
        pushBack(value);
    }
    else {
        _size++;
        while (_capacity < _size) {
            _capacity = _capacity * _multiplicativeCoef;
        }
        Value* tmp = new Value[_capacity];
        for (size_t i = 0; i < pos; i++) {
            tmp[i] = _data[i];
        }        
        tmp[pos] = value;
        for (size_t j = pos + 1; j < _size; j++) {
            tmp[j] = _data[j - 1];
        }
        delete[] _data;
        _data = tmp;
    }
}

void Vector::insert(const Value* values, size_t size, size_t pos) {
    if ((_data == nullptr) || (_capacity == 0)) {
        _capacity = _multiplicativeCoef;
        _data = new Value[_capacity];
    }
    _size += size;
    while (_capacity < _size) {
        _capacity = _capacity * _multiplicativeCoef;
    }
    Value* tmp = new Value[_capacity];
    for (size_t i = 0; i < pos; i++) {
        tmp[i] = _data[i];
    }
    for (size_t j = 0; j < size; j++) {
        tmp[pos + j] = values[j];
    }
    for (size_t g = pos + size; g < _size; g++) {
        tmp[g] = _data[g - size];
    }
    delete[] _data;
    _data = tmp;
}

void Vector::insert(const Vector& vector, size_t pos) {
    insert(vector._data, vector.size(), pos);
}

void Vector::popBack() {
    if (_size > 0) {
        _size--;
    }
    else {
		throw std::out_of_range("size = 0");
	}
}

void Vector::popFront(){
    erase(0, 1);
} 
 
void Vector::erase(size_t pos, size_t count) {
    if (pos >= _size) {
		throw std::out_of_range("pos >= _size");
		return;
	}
    if (pos + count >= _size){
        count = _size - pos;
    }
    _size -= count;
    for (size_t i = pos; i < _size; i++) {
		_data[i] = std::move(_data[i + count]);
	}
}

Value& Vector::operator[](size_t idx) {
   return _data[idx];
}

const Value& Vector::operator[](size_t idx) const {
    return _data[idx];
}

void Vector::shrinkToFit() {
    if (_capacity > _size) {
        _capacity = _size;
    }
    Value* tmp = new Value[_capacity];
    for (size_t i = 0; i < _size; i++) {
        tmp[i] = _data[i];
    }
    delete[] _data;
    _data = tmp; 
}

long long Vector::find(const Value& value) const {
    for (long long i = 0; i < _size; i++) {
        if (_data[i] == value){
            return i;
        }
    }
    return -1;
}

void Vector::reserve(size_t capacity) {
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

void Vector::eraseBetween(size_t beginPos, size_t endPos) {
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

Vector::Iterator::Iterator(Value* ptr) : _ptr(ptr){}
 
Value& Vector::Iterator::operator*() {
    return *_ptr;
}
    
const Value& Vector::Iterator::operator*() const {
    return *_ptr;
}
    
Value* Vector::Iterator::operator->() {
    return _ptr;
}
    
const Value* Vector::Iterator::operator->() const {
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++() {
    _ptr++;
    return *this;
}
    
Vector::Iterator Vector::Iterator::operator++(int) {
    Vector::Iterator tmp(*this);
    (*this)++;
    return tmp;
}
    
bool Vector::Iterator::operator==(const Iterator& other) const {
    return (_ptr == other._ptr);
}
    
bool Vector::Iterator::operator!=(const Iterator& other) const {
   return (_ptr != other._ptr);
}

Vector::Iterator Vector::begin() {
    Vector::Iterator begin(_data);
    return begin;
}

Vector::Iterator Vector::end() {
   Vector::Iterator end(_data + _size);
    return end;
}

