#pragma once

/**** start of libc stuff ****/
#include <stdlib.h>
#include <stdint.h>
#define STD_MALLOC malloc // change allocators here
#define STD_FREE free
/****  end of libc stuff  ****/

typedef struct {
	void* data;
	intptr_t count;
} Rc;

Rc new_object(size_t size);
Rc* reference(Rc* obj);
Rc* weak_reference(Rc* obj);
void* drop_reference(Rc* obj);
