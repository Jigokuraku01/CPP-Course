#include <iostream>
#include <cstring>
#include "my_vector.hpp"
#include <cassert>

namespace product
{

	class Product
	{
	public:
		Product(const char *name, int quantity, double price) : quantity_(quantity), price_(price)
		{
			if (name == nullptr)
			{
				name_ = nullptr;
				return;
			}
			name_ = new char[strlen(name) + 1];
			std::strcpy(name_, name);
		}
		Product(const Product &p) : quantity_(p.quantity_), price_(p.price_)
		{
			if (p.name_ == nullptr)
			{
				name_ = nullptr;
				return;
			}
			name_ = new char[strlen(p.name_) + 1];
			name_[strlen(p.name_)] = 0;
			std::strcpy(name_, p.name_);
		}

		~Product()
		{
			delete[] name_;
		}

		friend std::ostream &operator<<(std::ostream &, const product::Product &);

	private:
		char *name_;
		int quantity_;
		double price_;
	};
	std::ostream &operator<<(std::ostream &, const product::Product &);
} // namespace product

std::ostream &product::operator<<(std::ostream &os, const product::Product &prod)
{
	os << prod.name_ << " " << prod.quantity_ << " " << prod.price_;
	return os;
}

template <typename T>
void test_my_vector_default_constructible(T x, T y)
{
	containers::my_vector<T> f, z;
	f.resize(100);
	assert(f.size() == 100);
	containers::my_vector<T> a, b(100);
	b.resize(100000);

	for(size_t i = 0; i < b.size(); ++i)
		b[i] = i + 100;
	z = b;
	b = b;
	assert(z.size() == b.size());
	for(size_t i = 0; i < z.size(); ++i)
		assert(z[i] == b[i]);
	b.resize(100);
	assert(a.empty());
	assert(!b.empty());
	b.push_back(y);
	a.push_back(x);
	assert(a.size() == 1);
	assert(b.size() == 101);
	a.push_back(y);
	b = a;
	assert(b.size() == 2);
	containers::my_vector<T> c(a);
	assert(c.size() == a.size());
	b.resize(4);
	assert(b.capacity() == 4);
	assert(b.size() == 4);
	c.reserve(256);
	assert(c.capacity() == 256);
	a.pop_back();
	assert(a.size() == 1);
	b.clear();
	assert(b.size() == 0);
}

template <typename T>
void test_my_vector(T x, T y)
{
	containers::my_vector<T> a, b;
	assert(a.empty());
	assert(b.empty());
	b.push_back(y);
	a.push_back(x);
	assert(a.size() == 1);
	assert(b.size() == 1);
	b = a;
	assert(b.size() == 1);
	containers::my_vector<T> c(a);
	assert(c.size() == 1);
	c.reserve(256);
	assert(c.capacity() == 256);
	a.pop_back();
	assert(a.size() == 0);
	b.clear();
	assert(b.size() == 0);
}

int main()
{
	containers::my_vector<int> v;
	v.push_back(2);
	const int n{3};
	v.push_back(n);
	containers::my_vector<int> d(v);
	d[0] = 100;
	std::cout << d << std::endl
			  << v << std::endl
			  << std::endl;

	v = d;
	v[1] = 9;
	v = v;
	containers::my_vector<int> k;
	k = d;
	std::cout << k << std::endl;
	std::cout << d << std::endl
			  << v << std::endl
			  << std::endl;
	product::Product x("as", 1, 1);
	std::cout << x;

	test_my_vector_default_constructible<int>(5, 10);
	test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));

	return 0;
}
