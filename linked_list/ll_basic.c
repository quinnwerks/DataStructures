#include <stdio.h>
#include "ll.h"



struct ll_int{
	int data;
	struct ll_elem ptr;
};

int ll_int_eq(int a, int b){
	return a == b;
}

int ll_int_eq_wrapper(struct  ll_elem * elem, void * v_integer){
	struct ll_int * container;
	int integer = *((int *)v_integer);
	container = __container_of(elem, struct ll_int, ptr);
	return ll_int_eq(container -> data, integer);
}

//DO NOT USE IN ANYTHING OTHER THAN INT_TEST!!!!
int int_test_remove(struct ll * ll, int search_num, int was_there){
	struct ll_elem * pp = ll_remove(ll, &search_num, &ll_int_eq_wrapper);
	struct ll_int * p_container = __container_of(pp, struct ll_int, ptr);
	if(was_there){
		if(p_container -> data != search_num) return 0;
	}
	if(!was_there){
		if(pp != NULL) return 0;
	}
	return 1;
}

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
	struct ll_int * p_container;
	int i = 0;
	while(p != NULL){
		p_container = __container_of(p, struct ll_int, ptr);
		if(i == p_container -> data){
			i++;
			p = p -> next;
		}
		else{
			goto failure_int;
		}
	}
	printf("\tOK\n");

	printf("Testing search and retrieval of a linked list item\n");
	int search_one = 0;
	int search_two = NUM_ELEMENTS - 1;
	int search_three = NUM_ELEMENTS / 2;
	int search_four = 0;
	int count_2 = 0;

	printf("1-Front Removal\n");
	count_2 += int_test_remove(ll, search_one, 1);
	printf("2-Back Removal\n");
	count_2 += int_test_remove(ll, search_two, 1);
	printf("3-Middle Removal\n");
	count_2 += int_test_remove(ll, search_three, 1);
	printf("4-Non-Existant Removal\n");
	count_2 += int_test_remove(ll, search_four, 0);

	if(count_2 == 4)
		printf("\tALL OK\n");
	else goto failure_int;

	printf("Now remove everything and test that head and tail are NULL\n");
	while(ll -> head != NULL){
		ll_remove_front(ll);
	}
	for(int ii = 0; ii < NUM_ELEMENTS; ii++){
		if(test_structs[2].ptr.prev != NULL && test_structs[2].ptr.prev != NULL) goto failure_int;
	}
	if (ll-> head == NULL && ll -> head == ll -> tail){
		printf("\tOK\n");
		printf("Success! int_test passed.\n");
		goto success_int;

	} 
	
	

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

int reverse_test(){
	printf("Starting reverse test\n");
	int exit_code = 0;
	const int NUM_ELEMENTS = 10000;
	struct ll * ll = ll_init();
	for(int i = 0; i < NUM_ELEMENTS; i++){
		struct ll_int * new_elem = (struct ll_int *) malloc(sizeof(struct ll_int));
		new_elem -> data = i;
		new_elem -> ptr.next = NULL;
		new_elem -> ptr.prev = NULL;
		ll_add_back(ll, &new_elem -> ptr);
	}
	ll_reverse(ll);
	int count = NUM_ELEMENTS - 1;
	struct ll_elem * p = ll -> head;
	while(p != NULL){
		struct ll_int * container = __container_of(p, struct ll_int, ptr);
		if(container -> data !=  count){
			printf("Container value %d != %d", container -> data, count);
			goto failure_reverse;
		}
		else{
			count--;
			p = p -> next;
		}
	}
	printf("\tOK\n");
	printf("Testing freeing of contianers after dynamic allocation\n");
	struct ll_int * p_container;
	while(ll -> tail != NULL){
		p_container = __container_of(ll_remove_back(ll), struct ll_int, ptr);
		if(p_container != NULL) free(p_container);
	}
	if (ll -> head == ll -> tail && ll-> head == NULL){
		printf("\tOK\n");
		printf("Success! reverse_test passed.\n");
		goto success_reverse;
	} 

	failure_reverse:
	printf("\tFAIL\n\tStopping...\n");
	exit_code = 1;
	success_reverse:
	free(ll);
	return exit_code;
}

int main(){
	int exit_code = 0;
	int count = basic_test() + int_test() + reverse_test();
	if(count != 0) exit_code = 1; 
	return exit_code;
}