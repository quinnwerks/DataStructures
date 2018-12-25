#include <stdio.h>
#include "ll.h"
#define offsetof(st, m) __builtin_offsetof(st, m)
#define container_of(ptr, type, member) ({ \
        const typeof( ((type *)0)->member ) *__mptr = (ptr); \
        (type *)( (char *)__mptr - offsetof(type,member) );})

struct ll_int{
	int data;
	struct ll_elem ptr;
};



int int_test(){
	printf("Running integer test\n");
	int exit_code = 0;
	const int NUM_ELEMENTS = 10;
	struct ll_int test_structs[NUM_ELEMENTS];
	struct ll * ll = ll_init();
	printf("Adding test structs to list\n");
	for(int i = 0; i < NUM_ELEMENTS; i++){
		test_structs[i].ptr.next = NULL;
		test_structs[i].ptr.prev = NULL;
		test_structs[i].data = i;
		ll_add_back(ll, &test_structs[i].ptr);
	}
	printf("Testing if structs can be retrived from ll traversal\n");
	struct ll_elem * p = ll -> head;
	int i = 0;
	while(p != NULL){
		struct ll_int * p_container;
		p_container = container_of(p, struct ll_int, ptr);
		if(i == p_container -> data){
			i++;
			p = p -> next;
		}
		else{
			goto failure_int;
		}
	}
	printf("\tOK\n");

	printf("Testing search and retrieval of a linked list item");



	goto success_int;

	failure_int:
	printf("\tFAIL\n\tStopping...\n");
	exit_code = 1;

	success_int:
	free(ll);
	return exit_code;
}

int basic_test(){
	printf("Running basic test\n");
	struct ll * ll = ll_init();
	int exit_code = 0;
	const int NUM_ELEMENTS = 1000;

	printf("Testing NULL removal\n");
	struct ll_elem * should_be_null[2];
	should_be_null[0] = ll_remove_front(ll);
	should_be_null[1] = ll_remove_back(ll);
	if(should_be_null[0] == NULL && should_be_null[1] == NULL)
		printf("\tOK\n");
	else goto failure_basic;

	printf("Checking to see if list adding works\n");
	for (int i = 0; i < NUM_ELEMENTS/2; i++){
		struct ll_elem * add_elem_front = (struct ll_elem *) malloc(sizeof(struct ll_elem));
		struct ll_elem * add_elem_back = (struct ll_elem *) malloc(sizeof(struct ll_elem));
		add_elem_front -> next = NULL;
		add_elem_front -> prev = NULL;
		add_elem_back -> next = NULL;
		add_elem_back -> prev = NULL;
		ll_add_front(ll, add_elem_front);
		ll_add_back(ll, add_elem_back);
	}
	int count = 0;
	struct ll_elem * p = ll -> head;
	while(p != NULL){
		count++;
		p = p -> next;
	} 
	if(count == NUM_ELEMENTS)
		printf("\tOK\n");
	else goto failure_basic;

	printf("Checking to see if removal works\n");
	int count_2 = 0;
	struct ll_elem * pp_front;
	struct ll_elem * pp_back;
	for(int ii = 0; ii < count/2; ii++){
		pp_front = ll_remove_front(ll);
		pp_back = ll_remove_back(ll);
		if(pp_front == NULL) goto failure_basic;
		if(pp_back == NULL) goto failure_basic;
		free(pp_front);
		free(pp_back);
		count_2++;
	}

	if(count/2 == count_2)
		printf("\tOK\n");
	else goto failure_basic; 

	printf("Checking to see if head and tail values are NULL\n");
	if(ll->head == ll->tail && ll -> head == NULL){
		printf("Success! basic_test passed.\n");
		goto success_basic;
	} 

	failure_basic:
	printf("\tFAIL\n\tStopping...\n");
	exit_code = 1;

	success_basic:
	free(ll);
	return exit_code;
}


int main(){
	return int_test();
}