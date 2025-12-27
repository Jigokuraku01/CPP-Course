#ifndef MY_VECTOR_IMPL_H_
#define MY_VECTOR_IMPL_H_

#include <type_traits>
#include <iostream>
#include <algorithm>

template <typename T>
containers::my_vector<T>::my_vector()
{
	size_ = 0;
	capacity_ = 0;
	array_ = static_cast<T *>(operator new(sizeof(T) * capacity_));
}

template <typename T>
containers::my_vector<T>::my_vector(std::size_t n)
{
	if (n <= 0)
		throw("not posivibe size exception");

	static_assert(std::is_default_constructible_v<T>);
	size_ = n;
	capacity_ = 1;
	while (capacity_ < n)
		capacity_ *= 2;
	array_ = static_cast<T *>(operator new(sizeof(T) * capacity_));
	for (std::size_t i = 0; i < size_; ++i)
		new (&array_[i]) T();
}

template <typename T>
containers::my_vector<T>::my_vector(const my_vector<T> &other) : capacity_(other.capacity()), size_(other.size())
{
	if (other.array_)
	{
		array_ = static_cast<T *>(operator new(sizeof(T) * capacity_));
		for (std::size_t i = 0; i < size_; ++i)
			new (&array_[i]) T(static_cast<T>(other.array_[i]));
	}
	else
		array_ = nullptr;
}

template <typename T>
template <typename U>
containers::my_vector<T>::my_vector(const my_vector<U> &other) : capacity_(other.capacity()), size_(other.size())
{
	static_assert(!std::is_convertible_v<U, T>);
	if (other.array_)
	{
		array_ = static_cast<T *>(operator new(sizeof(T) * capacity_));
		for (std::size_t i = 0; i < size_; ++i)
			new (&array_[i]) T(static_cast<T>(other.array_[i]));
	}
	else
		array_ = nullptr;
}

template <typename T>
template <typename U>
containers::my_vector<T> &containers::my_vector<T>::operator=(const my_vector<U> &other)
{
	if(this == &other)
		return *this;
	static_assert(std::is_convertible_v<std::decay_t<T>, std::decay_t<U>>);
	if (array_)
		delete_array();
	if (other.array_)
	{
		capacity_ = other.capacity_;
		size_ = other.size_;
		array_ = static_cast<T *>(operator new(sizeof(T) * capacity_));
		for (std::size_t i = 0; i < size_; ++i)
			new (&array_[i]) T(static_cast<T>(other.array_[i]));
	}
	else
		array_ = nullptr;
	return *this;
}

template <typename T>
containers::my_vector<T> &containers::my_vector<T>::operator=(my_vector<T>& other)
{
	if(this == &other)
		return *this;
	if (array_)
		delete_array();
	if (other.array_)
	{
		capacity_ = other.capacity_;
		size_ = other.size_;
		array_ = static_cast<T *>(operator new(sizeof(T) * capacity_));
		for (std::size_t i = 0; i < size_; ++i)
			new (&array_[i]) T(static_cast<T>(other.array_[i]));
	}
	else
		array_ = nullptr;
	return *this;
	
}

template <typename T>
containers::my_vector<T>::~my_vector()
{
	if (array_)
	{
		delete_array();
	}
}

template <typename T>
void containers::my_vector<T>::delete_array()
{
	for (std::size_t i = 0; i < size_; ++i)
		array_[i].~T();
	operator delete(array_);
}

template <typename T>
std::size_t containers::my_vector<T>::size() const
{
	return size_;
}

template <typename T>
std::size_t containers::my_vector<T>::capacity() const
{
	return capacity_;
}

template <typename T>
bool containers::my_vector<T>::empty() const
{
	return size_ == 0;
}

template <typename T>
void containers::my_vector<T>::resize(std::size_t n)
{
	static_assert(std::is_default_constructible_v<T>);
	if (n <= size_)
	{
		for (std::size_t i = n; i < size_; ++i)
			array_[i].~T();
		size_ = n;
		return;
	}
	if (n <= capacity_)
	{
		for (std::size_t i = size_; i < n; ++i)
			new (&array_[i]) T();
		size_ = n;
		return;
	}
	std::size_t tmp_capacity = capacity_;
	if (tmp_capacity == 0)
		tmp_capacity = 1;
	while (tmp_capacity < n)
		tmp_capacity *= 2;
	T *tmp_array = static_cast<T *>(operator new(sizeof(T) * tmp_capacity));
	for (std::size_t i = 0; i < n; ++i)
		if (i < size_)
			new (&tmp_array[i]) T(array_[i]);
		else
			new (&tmp_array[i]) T();
	delete_array();
	array_ = tmp_array;
	capacity_ = tmp_capacity;
	size_ = n;
	return;
}

template <typename T>
void containers::my_vector<T>::reserve(std::size_t n)
{
	if (n <= capacity_)
		return;
	std::size_t tmp_capacity = capacity_;
	if (tmp_capacity == 0)
		tmp_capacity = 1;
	while (tmp_capacity < n)
		tmp_capacity *= 2;
	T *tmp_array = static_cast<T *>(operator new(sizeof(T) * tmp_capacity));
	for (std::size_t i = 0; i < size_; ++i)
		new (&tmp_array[i]) T(array_[i]);
	delete_array();
	array_ = tmp_array;
	capacity_ = tmp_capacity;
}

template <typename T>
T &containers::my_vector<T>::operator[](std::size_t index)
{
	return array_[index];
}

template <typename T>
const T &containers::my_vector<T>::operator[](std::size_t index) const{
	return array_[index];
}

template <typename T>
void containers::my_vector<T>::push_back(const T& t)
{
	if (size_ < capacity_)
	{
		new (&array_[size_]) T(t);
		size_++;
		return;
	}
	capacity_ *= 2;
	if (capacity_ == 0)
		capacity_ = 1;
	T *tmp_array = static_cast<T *>(operator new(sizeof(T) * capacity_));
	for (std::size_t i = 0; i < size_; ++i)
		new (&tmp_array[i]) T(array_[i]);
	new (&tmp_array[size_]) T(t);
	delete_array();
	array_ = tmp_array;
	size_++;
}

template <typename T>
void containers::my_vector<T>::pop_back()
{
	if (size_ == 0)
		throw("zero size and pop back exception");
	(array_[size_ - 1]).~T();
	size_--;
}

template <typename T>
void containers::my_vector<T>::clear()
{
	for (std::size_t i = 0; i < size_; ++i)
		(array_[i]).~T();
	size_ = 0;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const containers::my_vector<T> &array)
{
	for (std::size_t i = 0; i < array.size() - 1; ++i)
		os << array[i] << " ";
	os << array[array.size() - 1];
	return os;
}

#endif // MY_VECTOR_IMPL_H_