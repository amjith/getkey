#include<stdio.h>
#include<stdlib.h>
#include"list.h"

// Adds the node to the linked list and
// makes the incoming node to be the head node
void add_node(list_node **head, list_node *a_node) 
{
	if(!a_node) // if incoming node is NULL then return
		return;
	a_node->next = *head;
	a_node->prev = NULL;
	if (*head) // if head != null then ..
	{
		((list_node *)(*head))->prev = a_node;
	}
	*head = a_node; // make the a_node to be the head node 
}

// deletes the incoming node and updates the head node if necessary
void delete_node(list_node **head, list_node *d_node)
{
	if(!d_node) // if incoming node is NULL then return
		return;
	if(*head == d_node) 
	{
		if (d_node->next) // d_node is NOT the last node
		{
			*head = d_node->next;
		}
		else // d_node is the only node in the list
		{
			*head = NULL;
		}
		free(d_node);
		return ;
	}
	if(!d_node->next) // d_node is the last node in the list
	{
		( (list_node*)(d_node->prev) )->next = NULL;
		free(d_node);
		return ;
	}
	( (list_node*)(d_node->prev) )->next = d_node->next;
	( (list_node*)(d_node->next) )->prev = d_node->prev;
	free(d_node);
	return ;
}

// Searches through the link list to find the node that matches the key and returns the node
list_node* search_node(list_node *head, unsigned int key)
{
	list_node *cur_node = head;
	while(cur_node)
	{
		if (cur_node->key == key)
			return cur_node;
		cur_node = cur_node->next;
	}
	return NULL; // This will return NULL if key is not found in the list
}

void print_list(list_node *head)
{
	int i = 0;
	list_node *cur_node = head;
	while(cur_node)
	{
		printf("i:%d key:%u\n",i,cur_node->key);
		cur_node = cur_node->next;
		i++;
	}
	
}
/*
int main()
{
	list_node *key_list = NULL;
	list_node *new_node;

	new_node = (list_node*)malloc(sizeof(list_node));
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->key = 0;
	add_node(&key_list, new_node);
	new_node = (list_node*)malloc(sizeof(list_node));
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->key = 1;
	add_node(&key_list, new_node);
	print_list(key_list);
	delete_node(&key_list, search_node(key_list, 1));
	print_list(key_list);
	return 0;
}
*/
