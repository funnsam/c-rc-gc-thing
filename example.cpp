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
	optional<Rc<struct LinkedList>> prev;
} LinkedList;

void walk_rev(Rc<LinkedList> list) {
	printf("I'm %i at %p!\n", (*list)->number, *list);
	if ((*list)->prev.has_value()) {
		walk_rev((*list)->prev->reference());
	}
}

void walk(Rc<LinkedList> list) {
	printf("I'm %i at %p!\n", (*list)->number, *list);
	if ((*list)->next.has_value()) {
		walk((*list)->next.value().reference());
	} else {
		printf("Reversing...\n");
		walk_rev(list.reference());
	}
}

Rc<LinkedList> construct() {
	Rc ll_0 = Rc(LinkedList {});
	Rc ll_1 = Rc(LinkedList {});
	Rc ll_2 = Rc(LinkedList {});

	(*ll_0)->number = 1;
	(*ll_1)->number = 2;
	(*ll_2)->number = 3;

	(*ll_0)->next = optional(ll_1.reference());
	(*ll_1)->next = optional(ll_2.reference());
	(*ll_2)->next = optional<Rc<LinkedList>>();

	(*ll_0)->prev = optional<Rc<LinkedList>>();
	(*ll_1)->prev = optional(ll_0.weak_reference());
	(*ll_2)->prev = optional(ll_1.weak_reference());

	print_obj(ll_0);
	print_obj(ll_1);
	print_obj(ll_2);

	return ll_0.reference();
}

int main() {
	Rc list = construct();

	walk(list.reference());

	print_obj(list);

	return 0;
}
