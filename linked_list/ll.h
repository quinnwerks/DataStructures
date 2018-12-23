#ifndef LL
#define LL
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
struct ll_elem{
	struct ll_elem * next;
	struct ll_elem * prev;
};

struct ll{
	struct ll_elem * head;
};

int list_add_front(struct ll * ll, struct ll_elem * new_elem);

int list_add_back(struct ll * ll, struct ll_elem * new_elem);

struct ll * ll_init();

#endif
