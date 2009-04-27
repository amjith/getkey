#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"

void add_node_int(list_node_int **head, list_node_int *a_node) 
{
	if(!a_node) // if incoming node is NULL then return
		return;
	if (*head) // if head != null then ..
	{
		a_node->prev = ((list_node_int *)(*head))->prev;  // incoming node's prev is head's prev
		a_node->next = *head;						  // incoming node's next is head
		((list_node_int*)(((list_node_int *)(*head))->prev))->next = a_node; // head's prev node's next is now incoming node
		((list_node_int *)(*head))->prev = a_node;        // head's next node's prev is now incoming node

	}
	else
	{
		a_node->prev = a_node;
		a_node->next = a_node;
	}
	*head = a_node; // make the a_node to be the head node 
}

// deletes the incoming node and updates the head node if necessary
void delete_node_int(list_node_int **head, list_node_int *d_node)
{
	if( (!d_node) ) // if incoming node is NULL then return
		return;

	if( (d_node == d_node->next) && (d_node == d_node->prev) ) // If d_node is the only node in the list
	{
		*head = NULL;
	}
	else
	{
		((list_node_int*)(d_node->prev) )->next = d_node->next;
		((list_node_int*)(d_node->next) )->prev = d_node->prev;

		if (*head == d_node) //if d_node is the head node
			*head = d_node->next;
	}
	free(d_node);
	return;
}


// Searches through the link list to find the node that matches the key and returns the node
list_node_int* search_node_int(list_node_int *head, unsigned int key)
{
	list_node_int *cur_node = head;

	if(!head)
		return NULL;
	
	do
	{
		if (cur_node->key == key) // if key is found
			return cur_node;      // Retrun the node 
		cur_node = cur_node->next;
	} while(cur_node != head);
	return NULL; 				  // Return NULL if key is not found
}

// Go through the list and print every key in the node
void print_list_int(list_node_int *head)
{
	int i = 0;
	list_node_int *cur_node = head;

	if(!head)
		return ;

	do
	{
		printf("i:%d key:%u\n",i,cur_node->key);
		cur_node = cur_node->next;
		i++;
	}while(cur_node != head);
}

void add_node_str(list_node_str **head, list_node_str *a_node) 
{
	if(!a_node) // if incoming node is NULL then return
		return;
	if (*head) // if head != null then ..
	{
		a_node->prev = ((list_node_str *)(*head))->prev;  // incoming node's prev is head's prev
		a_node->next = *head;						  // incoming node's next is head
		((list_node_str*)(((list_node_str *)(*head))->prev))->next = a_node; // head's prev node's next is now incoming node
		((list_node_str *)(*head))->prev = a_node;        // head's next node's prev is now incoming node

	}
	else
	{
		a_node->prev = a_node;
		a_node->next = a_node;
	}
	*head = a_node; // make the a_node to be the head node 
}

// deletes the incoming node and updates the head node if necessary
void delete_node_str(list_node_str **head, list_node_str *d_node)
{
	if(!d_node) // if incoming node is NULL then return
		return;

	if( (d_node == d_node->next) && (d_node == d_node->prev) ) // If d_node is the only node in the list
	{
		*head = NULL;
	}
	else
	{
		((list_node_str*)(d_node->prev) )->next = d_node->next;
		((list_node_str*)(d_node->next) )->prev = d_node->prev;

		if (*head == d_node) //if d_node is the head node
			*head = d_node->next;
	}
	free(d_node->str);
	free(d_node);
	return;
}

// Searches through the link list to find the node that matches the key and returns the node
list_node_str* search_node_str(list_node_str *head, char* key)
{
	list_node_str *cur_node = head;

	if(!head)
		return NULL;
	
	do
	{
		if (!strcmp(cur_node->str,key)) // if key is found
			return cur_node;      // Retrun the node 
		cur_node = cur_node->next;
	} while(cur_node != head);
	return NULL; 				  // Return NULL if key is not found
}

void clear_list_str(list_node_str **head)
{
	if(!(*head)) // Make sure it ain't pointing to null
		return;
	do 
	{
		delete_node_str(head, (*head)->prev);
	}while(*head); // Traverse the linked list in the reverse order
}

// Go through the list and print every key in the node. This is for debug purposes only.
void print_list_str(list_node_str *head)
{
	int i = 0;
	list_node_str *cur_node = head;

	if(!head)
		return ;

	do
	{
		printf("i:%d key:%s\n",i,cur_node->str);
		cur_node = cur_node->next;
		i++;
	}while(cur_node != head);
}
/*--------------------------------------------------
* int main()
* {
* 	list_node_str *key_list = NULL;
* 	list_node_str *new_node;
* 
* 	new_node = (list_node_str*)malloc(sizeof(list_node_str));
* 	new_node->prev = NULL;
* 	new_node->next = NULL;
* 	new_node->str = (char *) malloc(sizeof(char)*2);
* 	strcpy(new_node->str, "0");
* 	add_node_str(&key_list, new_node);
* 	printf("Added 0\n");
* 	print_list_str(key_list);
* 	new_node = (list_node_str*)malloc(sizeof(list_node_str));
* 	new_node->prev = NULL;
* 	new_node->next = NULL;
* 	new_node->str = (char *) malloc(sizeof(char)*2);
* 	strcpy(new_node->str, "1");
* 	add_node_str(&key_list, new_node);
* 	printf("Added 1\n");
* 	print_list_str(key_list);
* 	new_node = (list_node_str*)malloc(sizeof(list_node_str));
* 	new_node->prev = NULL;
* 	new_node->next = NULL;
* 	new_node->str = (char *) malloc(sizeof(char)*2);
* 	strcpy(new_node->str, "2");
* 	add_node_str(&key_list, new_node);
* 	printf("Added 2\n");
* 	print_list_str(key_list);
* 	delete_node_str(&key_list, search_node_str(key_list, "0"));
* 	printf("Deleted 0\n");
* 	print_list_str(key_list);
* 	delete_node_str(&key_list, search_node_str(key_list, "1"));
* 	printf("Deleted 1\n");
* 	print_list_str(key_list);
* 	delete_node_str(&key_list, search_node_str(key_list, "2"));
* 	printf("Deleted 2\n");
* 	print_list_str(key_list);
* 	return 0;
* }
*--------------------------------------------------*/

