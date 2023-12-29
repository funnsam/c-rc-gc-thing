#include "lib.h"
#include <stdio.h>

#define print_obj(obj) \
	printf( \
		"\x1b[1mdata: %p, count: %li \x1b[0m(at line %u)\n", \
		obj.data, \
		obj.count, \
		__LINE__ \
	);

typedef struct LinkedList {
	int number;
	Rc* next;
	Rc* prev;
} LinkedList;

void walk_rev(LinkedList* list) {
	printf("I'm %i at %p!\n", list->number, list);
	if (list->prev != NULL) {
		walk_rev(list->prev->data);
	}
}

void walk(LinkedList* list) {
	printf("I'm %i at %p!\n", list->number, list);
	if (list->next != NULL) {
		walk(list->next->data);
	} else {
		printf("Reversing...\n");
		walk_rev(list);
	}
}

void drop(Rc* list) {
	if (((LinkedList*) (list->data))->next != NULL) {
		drop(((LinkedList*) (list->data))->next);
	}

	printf("Dropping %i\n", ((LinkedList*) (list->data))->number);
	drop_reference(list);
}

int main() {
	Rc ll_0 = new_object(sizeof(LinkedList));
	Rc ll_1 = new_object(sizeof(LinkedList));
	Rc ll_2 = new_object(sizeof(LinkedList));

	((LinkedList*) ll_0.data)->number = 1;
	((LinkedList*) ll_1.data)->number = 2;
	((LinkedList*) ll_2.data)->number = 3;

	((LinkedList*) ll_0.data)->next = reference(&ll_1);
	((LinkedList*) ll_1.data)->next = reference(&ll_2);
	((LinkedList*) ll_2.data)->next = NULL;

	((LinkedList*) ll_0.data)->prev = NULL;
	((LinkedList*) ll_1.data)->prev = weak_reference(&ll_0);
	((LinkedList*) ll_2.data)->prev = weak_reference(&ll_1);

	// they're now not directly used by the main body
	drop_reference(&ll_1);
	drop_reference(&ll_2);

	print_obj(ll_0);
	print_obj(ll_1);
	print_obj(ll_2);

	walk(ll_0.data);

	// done with the list
	drop(&ll_0);

	print_obj(ll_0);
	print_obj(ll_1);
	print_obj(ll_2);

	return 0;
}
