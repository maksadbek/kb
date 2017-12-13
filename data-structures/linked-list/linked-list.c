#include <stdlib.h>
#include <stdio.h>

typedef struct list {
	int item;
	struct list *next;
} list;

list* search_list(list *l, int x) {
	if (l == NULL) {
		return NULL;
	}
	
	if (l->item == x) {
		return l;
	} else {
		return search_list(l->next, x);
	}
}

void insert_list(list **l, int x) {
	list* p;
	
	p = (list*)malloc(sizeof(list));

	p->item = x;

	p->next = *l;

	*l = p;
}

list *predecessor_list(list *l, int x) {
	if ((l == NULL) || (l->next == NULL)) {
		printf("Error: predecessor sought on null list.\n");
		return NULL;
	}

	if ((l->next)->item == x) {
		return l;
	} else {
		return predecessor_list(l->next, x);
	}
}

void delete_list(list **l, int x) {
	list *p;
	list *pred;


	p = search_list(*l, x);

	if(p != NULL) {
		pred = predecessor_list(*l, x);
		if (pred == NULL) {
			*l = p->next;
		} else {
			pred->next = p->next;
		}

		free(p);
	}
}

int main(int argc, char** argv) {
	list** l = malloc(sizeof(list));

	*l = NULL;

	insert_list(l, 1);
	insert_list(l, 2);
	insert_list(l, 3);
	insert_list(l, 4);
	insert_list(l, 5);

	list* f = search_list(l[0], 3);
	if (f == NULL) {
		printf("not found node with value %d\n", 3);
		return 0;
	} else {
		printf("found node with value %d as expected\n", 3);
	}

	delete_list(l, 3);

	list* not_found = search_list(l[0], 3);

	if (not_found) {
		printf("unexpected finding\n");
	} else {
		printf("it works!\n");
	}
}
