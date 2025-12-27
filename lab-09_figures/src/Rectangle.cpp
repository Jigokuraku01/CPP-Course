#include "Rectangle.hpp"

// TODO

Rectangle::Rectangle(int id, int x, int y, int width, int height):Figure(id, x, y){
	if(width < 0 || height < 0)
		throw("negative height or width exception");
	width_ = width;
	height_ = height;
}

Rectangle::~Rectangle(){}

void Rectangle::print() const{
	std::cout << "Rectangle " << id << ": x = " << x << " y = " << y << " width = " << width_ << " height = " << height_ << "\n";
}

void Rectangle::zoom(int factor){
	if(factor < 0)
		throw("negative factor exception");
	width_ *= factor;
	height_ *= factor;
}

bool Rectangle::is_inside(int x, int y) const{
	if(abs(this->x - x) * 2 <= width_ && abs(this->y - y) * 2 <= height_)
		return true;
	return false;
}