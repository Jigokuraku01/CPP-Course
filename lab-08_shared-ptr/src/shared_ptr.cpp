// TODO

#include "shared_ptr.hpp"

shared_ptr::Storage::Storage(Matrix* mtx) {
	data_ = mtx;
	ref_count_ = 1;
}

shared_ptr::Storage::~Storage() {
	delete data_;
}

void shared_ptr::Storage::incr() {
	++ref_count_;
}

void shared_ptr::Storage::decr() {
	--ref_count_;
}

int shared_ptr::Storage::getCounter() const {
	return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
	return data_;
}

shared_ptr::shared_ptr(Matrix* obj) {
	if (obj == nullptr)
		storage_ = nullptr;
	else
		storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr& other) {
	if (other.isNull())
		storage_ = nullptr;
	else {
		storage_ = other.storage_;
		storage_->incr();
	}
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
	if (other.isNull()) {
		if (!isNull()) {
			deInit();
			storage_ = nullptr;
		}
	}
	else {
		if (!isNull())
			deInit();
		storage_ = other.storage_;
		storage_->incr();
	}
	return *this;
}

shared_ptr::~shared_ptr() {
	deInit();
}

Matrix* shared_ptr::ptr() const {
	if (isNull())
		return nullptr;
	return storage_->getObject();
}

bool shared_ptr::isNull() const {
	return storage_ == nullptr;
}

void shared_ptr::reset(Matrix* obj) {
	if (!isNull())
		deInit();
	if(obj != nullptr)
		storage_ = new Storage(obj);
	else
		storage_ = nullptr;
}

Matrix* shared_ptr::operator->() const {
	if (isNull())
		return nullptr;
	return storage_->getObject();
}

Matrix& shared_ptr::operator*() const {
	if (isNull())
		throw std::runtime_error("shared_ptr is null");
	return *(storage_->getObject());
}

void shared_ptr::deInit(){
	if (!isNull()) {
		storage_->decr();
		if (storage_->getCounter() == 0) 
			delete storage_;
		storage_ = nullptr;
	}
}