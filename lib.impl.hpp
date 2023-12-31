#pragma once

#include "lib.hpp"

#ifdef DEBUG
#include "stdio.h"
#endif

template<typename T> Rc<T>::Rc(T data) {
	this->inner = new RcInner<T>;
	this->inner->data = data;
	this->inner->count = 1;

#ifdef DEBUG
	printf("%p: rc constructed\n", this->inner);
#endif
}

template<typename T> Rc<T>::Rc(const Rc<T>& cpy) {
#ifdef DEBUG
	printf("%p: ref copied increased to %li\n", cpy.inner, cpy.inner->count);
#endif

	cpy.inner->count += 1;
	this->inner = cpy.inner;
}

template<typename T> Rc<T>::Rc(RcInner<T>* inner) : inner(inner) {
}

template<typename T> Rc<T>::~Rc() {
	this->inner->count -= 1;

#ifdef DEBUG
	printf("%p: ref decreased to %li\n", this->inner, this->inner->count);
#endif

	if (this->inner->count <= 0) {
		delete this->inner;

#ifdef DEBUG
		printf("%p: rc freed\n", this->inner);
#endif
	}
}

template<typename T> inline Rc<T> Rc<T>::operator&() {
	this->inner->count += 1;

#ifdef DEBUG
	printf("%p: ref increased to %li\n", this->inner, this->inner->count);
#endif

	return Rc(this->inner);
}

template<typename T> T* Rc<T>::operator*() {
#ifdef DEBUG
	printf("%p: weak ref\n", this->inner);
#endif

	return &this->inner->data;
}

template<typename T> inline intptr_t Rc<T>::get_count() {
	return this->inner->count;
}
