#include <stdio.h>
#include <optional>
#include "lib.hpp"

using namespace std;

#define print_obj(obj) \
	printf( \
		"\x1b[1mcount: %li \x1b[0m(at line %u)\n", \
		obj.get_count(), \
		__LINE__ \
	);

typedef struct LinkedList {
	int number;
	optional<Rc<struct LinkedList>> next;
	optional<struct LinkedList*> prev;
} LinkedList;

void walk_rev(LinkedList* list) {
	printf("I'm %i at %p!\n", list->number, list);
	if (list->prev.has_value()) {
		walk_rev(list->prev.value());
	}
}

void walk(Rc<LinkedList> list) {
	printf("I'm %i at %p!\n", (*list)->number, *list);
	if ((*list)->next.has_value()) {
		walk(&(*list)->next.value());
	} else {
		printf("Reversing...\n");
		walk_rev(*list);
	}
}

Rc<LinkedList> construct() {
	Rc ll_0 = Rc(LinkedList {});
	Rc ll_1 = Rc(LinkedList {});
	Rc ll_2 = Rc(LinkedList {});

	(*ll_0)->number = 1;
	(*ll_1)->number = 2;
	(*ll_2)->number = 3;

	(*ll_0)->next = optional(&ll_1);
	(*ll_1)->next = optional(&ll_2);
	(*ll_2)->next = optional<Rc<LinkedList>>();

	(*ll_0)->prev = optional<LinkedList*>();
	(*ll_1)->prev = optional(*ll_0);
	(*ll_2)->prev = optional(*ll_1);

	print_obj(ll_0);
	print_obj(ll_1);
	print_obj(ll_2);

	return ll_0;
}

int main() {
	Rc list = construct();

	walk(&list);

	print_obj(list);

	return 0;
}
