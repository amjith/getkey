#ifndef __list_h__
#define __list_h__

typedef struct list_node_int
{
	struct list_node_int* prev;
	struct list_node_int* next;
	unsigned int key;
}list_node_int;

void add_node_int(list_node_int **head, list_node_int *a_node);
void delete_node_int(list_node_int **head, list_node_int *d_node);
list_node_int* search_node_int(list_node_int *head, unsigned int key);
void print_list_int(list_node_int *head);

typedef struct list_node_str
{
	struct list_node_str* prev;
	struct list_node_str* next;
	char*  str;
}list_node_str;

void add_node_str(list_node_str **head, list_node_str *a_node);
void delete_node_str(list_node_str **head, list_node_str *d_node);
list_node_str* search_node_str(list_node_str *head, char* str);
void print_list_str(list_node_str *head);
#endif
