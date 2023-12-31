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
		bool is_strong;

		Rc(RcInner<T>* inner, bool strong);

	public:
		Rc(T);
		Rc(const Rc<T>&);

		~Rc();

		T* operator*();

		Rc reference();
		Rc weak_reference();
		void drop_reference();

		intptr_t get_count();
};

#include "lib.impl.hpp"
