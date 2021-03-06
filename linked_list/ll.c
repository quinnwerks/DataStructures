#include "ll.h"

struct ll * ll_init(){
	struct ll * new_ll = NULL;

	new_ll = (struct ll *)malloc(sizeof(struct ll));
	if(new_ll == NULL){
		perror("ERROR: not enough memory for creation of ll\n");
		return NULL;
	}

	new_ll -> head = NULL;
	new_ll -> tail = NULL;

	return new_ll;
}

int ll_add_front(struct ll * ll, struct ll_elem * new_elem){
	struct ll_elem * next_elem = NULL;
	if(ll -> head != NULL){ 
		next_elem = ll -> head;
		next_elem -> prev = new_elem;
	}
	ll -> head = new_elem;
	if(ll -> tail == NULL) ll -> tail = new_elem;

	new_elem -> next = next_elem;
	new_elem -> prev = NULL;
	
	return 1;
}

int ll_add_back(struct ll * ll, struct ll_elem * new_elem){
	struct ll_elem * prev_elem = NULL;
	if (ll -> tail != NULL){
		prev_elem = ll -> tail;
		prev_elem -> next = new_elem;
	}
	ll -> tail = new_elem;
	if(ll -> head == NULL) ll -> head = new_elem;

	new_elem -> prev = prev_elem;
	new_elem -> next = NULL;

	return 1;
}

struct ll_elem * ll_search(struct ll * ll, void * item, int (*is_eq)(struct ll_elem *, void *)){
	struct ll_elem * p = ll -> head;
	while(p != NULL){
		if(is_eq(p , item)) 
			return p;
		p = p -> next;
	}

	return NULL;
}

struct ll_elem * ll_remove_front(struct ll * ll){
	struct ll_elem * p = ll -> head;
	if(ll -> head == NULL) return NULL;
	else if(ll -> head == ll -> tail){
		ll -> head = NULL;
		ll -> tail = NULL;
	}
	else{
		ll -> head = ll -> head -> next;
		p -> next -> prev = NULL;
	}
	
	p -> prev = NULL;
	p -> next = NULL;

	return p;
}

struct ll_elem * ll_remove_back(struct ll * ll){
	struct ll_elem * p = ll -> tail;
	if(ll -> tail == NULL) return NULL;
	else if(ll -> tail == ll -> head){
		ll -> head = NULL;
		ll -> tail = NULL;
	}
	else{
		ll-> tail = ll -> tail -> prev;
		p -> prev -> next = NULL;
	}
	p -> next = NULL;
	p -> prev = NULL;

	return p;
}

struct ll_elem * ll_remove(struct ll * ll, void * item, int (*is_eq)(struct ll_elem *, void *)){
	struct ll_elem * extract_this = ll_search(ll, item, is_eq);
	if(extract_this == NULL) return NULL;

	struct ll_elem * next_elem = extract_this -> next;
	struct ll_elem * prev_elem = extract_this -> prev;

	if(extract_this == ll -> head) extract_this = ll_remove_front(ll);
	else if(extract_this == ll -> tail) extract_this = ll_remove_back(ll);
	else{
		next_elem -> prev = prev_elem;
		prev_elem -> next = next_elem;
	}

	extract_this -> next = NULL;
	extract_this -> prev = NULL;
	
	return extract_this;
}

void ll_reverse(struct ll * ll){
	struct ll_elem * p = ll -> head;
	struct ll_elem * swap = NULL;
	if(p == NULL) return;

	while(p != NULL){
		struct ll_elem * next_reverse = p -> next;
		__swap(p -> next, p -> prev, swap);
		p = next_reverse;
	}

	__swap(ll -> head, ll -> tail, swap);
}




