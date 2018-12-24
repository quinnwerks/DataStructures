#ifndef LL
#define LL
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

//a doubly linked list element
struct ll_elem{
	struct ll_elem * next;
	struct ll_elem * prev;
};

//head and tail of linked list structure
struct ll{
	struct ll_elem * head;
	struct ll_elem * tail;
};

//add an element to the front of the list
int ll_add_front(struct ll * ll, struct ll_elem * new_elem);

//add an element to the back of the list
int ll_add_back(struct ll * ll, struct ll_elem * new_elem);

//search the linked list for an element
//uses is_eq to compare list values to the element being searched for
struct ll_elem * ll_search(struct ll * ll, void * item, 
							int (*is_eq)(struct ll_elem *, void *));

//returns and removes an element from the front of the linked list
struct ll_elem * ll_remove_front(struct ll * ll);

//returns and removes an element from the back of the linked list
struct ll_elem * ll_remove_back(struct ll * ll);

//returns and removes an element equal to some item
struct ll_elem * ll_extract(struct ll * ll, void * item, 
								int (*is_eq)(struct ll_elem *, void *));

//reverse the linked list ll 
void ll_reverse(struct ll * ll);

//initialize the doubly linked list and return it
struct ll * ll_init();

#endif
