#include "Circle.hpp"

// TODO

Circle::Circle(int id, int x, int y, int radius, const char* label):Figure(id, x, y){
	if(label == nullptr)
		throw("nullptr label exception");
	if(radius < 0)
		throw("negative radius exception");
	radius_ = radius;
	size_t len = strlen(label);
	label_ = new char[len + 1];
	strcpy(label_, label);
}

Circle::~Circle(){
	delete[] label_;
}

void Circle::print() const{
	std::cout << "Circle " << id << ": x = " << x << " y = " << y << " radius = " << radius_ << " label = " << label_ << "\n";
}

bool Circle::is_inside(int x, int y) const{
	if((x - this->x) * (x - this->x) + (y - this->y) * (y - this->y) <= radius_ * radius_)
		return true;
	return false;
}

void Circle::zoom(int factor){
	if(factor < 0)
		throw("negative factor exception");
	radius_ *= factor;
}