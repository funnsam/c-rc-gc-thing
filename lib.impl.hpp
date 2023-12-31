#pragma once

#include "lib.hpp"

#ifdef DEBUG
#include "stdio.h"
#endif

template<typename T> Rc<T>::Rc(T data) {
	this->inner = new RcInner<T>;
	this->inner->data = data;
	this->inner->count = 1;
	this->is_strong = true;

#ifdef DEBUG
	printf("%p: rc constructed\n", this->inner);
#endif
}

template<typename T> Rc<T>::Rc(const Rc<T>& cpy) {
	if (cpy.is_strong) cpy.inner->count += 1;
	this->inner = cpy.inner;
	this->is_strong = cpy.is_strong;
}

template<typename T> Rc<T>::Rc(RcInner<T>* inner, bool strong) : inner(inner), is_strong(strong) {
}

template<typename T> Rc<T>::~Rc() {
	if (this->is_strong) {
		this->inner->count -= 1;

#ifdef DEBUG
		printf("%p: ref decreased to %li\n", this->inner, this->inner->count);
#endif
	}

	if (this->is_strong && this->inner->count <= 0) {
		delete this->inner;

#ifdef DEBUG
		printf("%p: rc freed\n", this->inner);
#endif
	}
}

template<typename T> T* Rc<T>::operator*() {
	return &this->inner->data;
}

template<typename T> inline Rc<T> Rc<T>::reference() {
	this->inner->count += 1;

#ifdef DEBUG
	printf("%p: ref increased to %li\n", this->inner, this->inner->count);
#endif

	return Rc(this->inner, true);
}

template<typename T> inline Rc<T> Rc<T>::weak_reference() {
#ifdef DEBUG
	printf("%p: weak ref\n", this->inner);
#endif

	return Rc(this->inner, false);
}

template<typename T> inline intptr_t Rc<T>::get_count() {
	return this->inner->count;
}
