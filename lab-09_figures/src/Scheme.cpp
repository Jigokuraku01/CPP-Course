#include "Scheme.hpp"

// TODO

Scheme::Scheme(int capacity) {
	if(capacity < 0)
		throw("negative capacity exception");
	capacity_ = capacity;
	size_ = 0;
	figures_ = new Figure* [capacity_];
}

Scheme::~Scheme() {
	for(size_t i = 0; i < size_; ++i)
		delete figures_[i];
	delete[] figures_;
}

void Scheme::push_back_figure(Figure* fg) {
	if (fg == nullptr)
		throw("nullptr figure exception");
	if (size_ == capacity_)
		throw("out of range");
	figures_[size_] = fg;
	size_++;
}

void Scheme::remove_figure(int id) {
	for (size_t i = 0; i < size_; ++i)
		if (figures_[i]->get_id() == id) {
			delete figures_[i];
			for (size_t j = i + 1; j < size_; ++j)
				figures_[j - 1] = figures_[j];
			size_ -= 1;
		}
}

void Scheme::print_all_figures() const {
	for (size_t i = 0; i < size_; ++i)
		figures_[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
	for (size_t i = 0; i < size_; ++i)
		if (figures_[i]->get_id() == id)
			figures_[i]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) const {
	for (size_t i = 0; i < size_; ++i)
		if (figures_[i]->is_inside(x, y))
			return figures_[i];
	return nullptr;

}

void Scheme::move(int id, int new_x, int new_y) {
	for (size_t i = 0; i < size_; ++i)
		if (figures_[i]->get_id() == id)
			figures_[i]->move(new_x, new_y);
}

size_t Scheme::size() const {
	return size_;
}

size_t Scheme::capacity() const {
	return capacity_;
}

