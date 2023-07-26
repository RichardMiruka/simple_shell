#include "main_unique.h"

/**
 * free_replace_variable_list - frees a replace_var_list.
 * @head: head of the linked list.
 * Return: no return.
 */
void free_replace_variable_list(replace_var_list_t **head)
{
	replace_var_list_t *temp;
	replace_var_list_t *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_replace_variable_node - adds a variable at the end of a replace_var_list.
 * @head: head of the linked list.
 * @variable_length: length of the variable.
 * @variable: name of the variable.
 * @value_length: length of the value.
 * Return: address of the head.
 */
replace_var_list_t *add_replace_variable_node(replace_var_list_t **head, int variable_length, char *variable, int value_length)
{
	replace_var_list_t *new, *temp;

	new = malloc(sizeof(replace_var_list_t));
	if (new == NULL)
		return (NULL);

	new->variable_length = variable_length;
	new->variable = variable;
	new->value_length = value_length;

	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}


