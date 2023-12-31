#pragma once

/**** start of libc stuff ****/
#include <stdlib.h>
#include <stdint.h>
/****  end of libc stuff  ****/

template<typename T> struct RcInner {
	T data;
	intptr_t count;
};

template<typename T> class Rc {
	private:
		RcInner<T>* inner;

		Rc(RcInner<T>* inner);

	public:
		Rc(T);
		Rc(const Rc<T>&);

		~Rc();

		T* operator*(); // weak reference
		Rc operator&(); // reference

		intptr_t get_count();
};

#include "lib.impl.hpp"
