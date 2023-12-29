#include "lib.h"

Rc new_object(size_t size) {
	Rc obj;
	obj.data = STD_MALLOC(size);
	obj.count = 1;
	return obj;
}

inline Rc* reference(Rc* obj) {
	obj->count += 1;
	return weak_reference(obj);
}

inline Rc* weak_reference(Rc* obj) {
	return obj;
}

inline void* drop_reference(Rc* obj) {
	obj->count -= 1;
	if (obj->count <= 0) {
		STD_FREE(obj->data);
	}
}
