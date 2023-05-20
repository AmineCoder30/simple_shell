#include "shell.h"

alstype *add_alias_end(alstype **head, char *name, char *value);
void func_free_alsList(alstype *head);
lisType *add_node_end(lisType **head, char *dir);
void func_freeList(lisType *head);

/**
 * add_alias_end - function to add a node at the end of linked list.
 * @head: head of linked list.
 * @name: new node fo linked list.
 * @value:  node must be added.
 * Return: null or ptr.
 */
alstype *add_alias_end(alstype **head, char *name, char *value)
{
	alstype *new_node = malloc(sizeof(alstype));
	alstype *last;

	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (stringLen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	copy_string(new_node->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * add_node_end - function to add node to the end of linked ... .
 * @head: head of linked list.
 * @dir: directory path.
 * Return: null or ptr.
 */
lisType *add_node_end(lisType **head, char *dir)
{
	lisType *new_node = malloc(sizeof(lisType));
	lisType *last;

	if (!new_node)
		return (NULL);

	new_node->dir = dir;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * func_free_alsList - function to free linked list.
 * @head: head of linked list.
 */
void func_free_alsList(alstype *head)
{
	alstype *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

/**
 * func_freeList - function to free the linked list.
 * @head: head of linked list.
 */
void func_freeList(lisType *head)
{
	lisType *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
