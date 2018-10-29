#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList {
	int value;
	struct LinkedList* next;
} List;

int getListLength(List* list) {
	int i=1;
	while(list->next != NULL) {
		list = list->next;
		i++;
	}
	
	return i;
}

int getItemAtIndex(List* list, int index) {
	for(int i=0;i<index;i++) {
		if(list->next == NULL) {
			return -1;
		} else {
			list = list->next;
		}
	}
	
	return list->value;
}

void addList(List* list, int newValue) {
		while(list->next != NULL) {
			list = list->next;
		}
		List* newList = (List*)malloc(sizeof(List));
		newList->value = newValue;
		newList->next = NULL;
		list->next = newList;
}

void writeAll(List* list) {
	int i=0;
	printf("%d. %d %p\n", i, list->value, list);
	while(list->next != NULL) {
		list = list->next;
		i++;
		printf("%d. %d %p\n", i, list->value, list);
	}
}

void removeAtIndex(List* list, int index) {
	if(getListLength(list) > index) {
		List* temp;
		for(int i=0;i!=index-1;i++) {
			list = list->next;
			if(i == index-3)
				temp = list;
		}		
		temp->next = list->next;
		free(list);
	}
}

void removeAtRange(List* list, int index_min, int index_max) {
	if(getListLength(list) > index_max && index_max > index_min) {
		List* temp;
		for(int i=0;i!=index_max-1;i++) {
			list = list->next;
			if(i == index_min-3)
				temp = list;
		}		
		temp->next = list->next;
		free(list);
	} else if(index_max == index_min)
		removeAtIndex(list, index_max);
}

List newList(int firstValue) {
	List r;
	r.next = NULL;
	r.value = firstValue;
	
	return r;
}

int main(int argc, char **argv)
{
	List list = newList(0);
	for(int i=1;i<100;i++) {
		addList(&list, i);
	}
	
	removeAtRange(&list, 10, 20);
	removeAtIndex(&list, 50);
	
	writeAll(&list);
	
	printf("Number of values in list: %d\n", getListLength(&list));
	
	system("pause");
	
	return 0;
}
