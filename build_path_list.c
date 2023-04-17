#include "main.h"

/**
 * add_node - adds a new node to the end of a linked list
 * @head: pointer to the head of the linked list
 * @dir: directory name to add to the linked list
 *
 * Return: pointer to the newly added node, or NULL on failure
 */
path_list_t *add_node(path_list_t **head, char *dir)
{
    path_list_t *new_node = malloc(sizeof(path_list_t));
    path_list_t *temp = *head;

    if (!new_node)
        return (NULL);

    new_node->dir = strdup(dir);
    if (!new_node->dir)
    {
        free(new_node);
        return (NULL);
    }

    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        return (new_node);
    }

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = new_node;

    return (new_node);
}

/**
 * build_path_list - Builds a linked list of directories contained in PATH
 *
 * This function takes the PATH environment variable and builds a linked 
 * list of the directories contained in it, with each directory being a 
 * separate node in the list. The function returns a pointer to the head 
 * of the linked list, or NULL if the list could not be built.
 *
 * Return: A pointer to the head of the linked list, or NULL on failure.
 */
path_list_t *build_path_list(void)
{
    path_list_t *head = NULL;
    char *path = getenv("PATH");
    char *token;

    if (path == NULL)
        return (NULL);

    token = strtok(path, ":");

    while (token != NULL)
    {
        if (add_node(&head, token) == NULL)
        {
            /* failed to add node, free list and return NULL */
            while (head != NULL)
            {
                path_list_t *temp = head;
                head = head->next;
                free(temp->dir);
                free(temp);
            }

            return (NULL);
        }

        token = strtok(NULL, ":");
    }

    return (head);
}
