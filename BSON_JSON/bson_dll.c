#include "bson_dll.h"

bson_dll *bson_dll_newList()
{
	bson_dll *newList =  (bson_dll *)malloc(sizeof(bson_dll));
	newList->head = 0;
	return newList;
}

bson_dll_node *bson_dll_iterateNode(bson_dll_node *node)
{
	return node->next;
}

void bson_dll_destroy(bson_dll *list)
{
	bson_dll_node *current;
	bson_dll_node *next;
	
	current = list->head;
	
	if(current == 0)
		return;

	while(current->next != 0)
	{
		free(current->data);
		next = current->next;
		free(current);
		current = next;
	}
	free(current);
	free(list);

	return;
}

bson_dll_node *bson_dll_append(bson_dll *addTo, void *data, int isList)
{
	bson_dll_node *current;	
	bson_dll_node *toCreate;
	
	toCreate = (bson_dll_node *)malloc(sizeof(bson_dll_node));
	toCreate->data = data;
	toCreate->next = 0;
	toCreate->previous = 0;
	
	current = addTo->head;
	if(current != 0)
	{
		while(current->next != 0)
			current = current->next;

		toCreate->previous = current;
		current->next = toCreate;
	}
	return toCreate;
}
