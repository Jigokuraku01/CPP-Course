#include "my_vector.hpp"


MyVector::MyVector(): _size(0), _capacity(2) {
    _data = new int[_capacity];
}

MyVector::MyVector(size_t init_capacity): _size(0), _capacity(init_capacity) {
    _data = new int[_capacity];
}

MyVector::~MyVector() {
    delete[] _data;
}

void MyVector::set(std::size_t index, int value) {
    if (index >= _size)
        throw std::runtime_error("incorrect index");
    _data[index] = value;
}

int MyVector::get(std::size_t index) {
    if (index >= _size)
        throw std::runtime_error("incorrect index");
    return _data[index];
}

std::size_t MyVector::size() {
    return _size;
}

std::size_t MyVector::capacity() {
    return _capacity;
}

void MyVector::push_back(int value) {
    if (_size < _capacity)
        _data[_size] = value;
    else
    {
        _capacity *= 2;
        int* tmp_data = new int[_capacity];
        std::memcpy(tmp_data, _data, _size * sizeof(int));
        delete[] _data;
        _data = tmp_data;
        _data[_size] = value;
    }
    _size++;
}

void MyVector::insert(std::size_t index, int value) {
    if (index == _size)
        push_back(value);
    else
    {
        int last_int = get(_size - 1);
        for (std::size_t i = _size - 1; i > index; --i)
            set(i, _data[i - 1]);
        set(index, value);
        push_back(last_int);
    }
}

void MyVector::erase(size_t index) {
    for (std::size_t i = index; i < _size; ++i)
        set(i, _data[i + 1]);
    _size--;
}

void MyVector::reserve(std::size_t new_capacity) {
    if (new_capacity <= _capacity)
        return;
    _capacity = new_capacity;
    int* tmp_data = new int[_capacity];
    std::memcpy(tmp_data, _data, _size * sizeof(int));
    delete[] _data;
    _data = tmp_data;
}

void MyVector::resize(std::size_t new_size) {
    if (new_size < _size)
        for (std::size_t i = new_size; i < _size; ++i)
            set(i, 0);

    else if (new_size > _capacity)
    {
        reserve(std::max(2 * _capacity, new_size));
        for(std::size_t i = _size; i < new_size; ++i)
            _data[i] = 0;
    }
    _size = new_size;
}

MyVector& MyVector::operator =(const MyVector& other) {
    resize(other._size);
    std::memcpy(_data, other._data, sizeof(int) * other._size);

    return *this;
}

MyVector::MyVector(const MyVector& other) {
    _size = 0;
    _capacity = 0;
    resize(other._size);
    std::memcpy(_data, other._data, sizeof(int) * other._size);
}