#include "ll.h"


int list_add_front(struct ll * ll, struct ll_elem * new_elem){
	struct ll_elem * next_elem = NULL;
	//if non-empty list
	if(ll -> head != NULL){ 
		next_elem = ll -> head;
		next_elem -> prev = new_elem;
	}
	ll -> head = new_elem;
	new_elem -> next = next_elem;
	new_elem -> prev = NULL;
	
	return 1;
}

int list_add_back(struct ll * ll, struct ll_elem * new_elem){
	//struct prev_elem = NULL;
	//if (ll -> tail != NULL){
	//	prev_elem = ll -> tail;
	//}


		
	return 0;
}

struct ll * ll_init(){
	struct ll * new_ll = NULL;
	new_ll = (struct ll *)malloc(sizeof(struct ll));
	
	if(new_ll == NULL){
		perror("ERROR: not enough memory for creation of ll\n");
		return NULL;
	}
	new_ll -> head = NULL;

	return new_ll;
}


