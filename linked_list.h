#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>  // for size_t

/**
 * Node structure (internal implementation detail)
 * This is the same as before - just the building blocks
 */
typedef struct Node {
    int data;
    struct Node *next;
} Node;

/**
 * LinkedList ADT structure
 * This is NEW - wraps the list to add metadata
 * 
 * @field head Pointer to the first node in the list
 * @field size Number of elements (cached for O(1) lookup!)
 */
typedef struct LinkedList {
    Node *head;
    size_t size;
} LinkedList;

// =============================================================================
// REQUIRED NEW FUNCTIONS (for managing the wrapper struct)
// =============================================================================

/**
 * Create a new empty linked list
 * Returns NULL if allocation fails
 */
LinkedList* list_create(void);

/**
 * Destroy the entire list (free all memory)
 * This replaces free_list() from the original version
 */
void list_destroy(LinkedList *list);

// =============================================================================
// REFACTORED FUNCTIONS FROM ORIGINAL (same logic, new API)
// =============================================================================

/**
 * Print the entire linked list
 * (was: print_list)
 */
void list_print(const LinkedList *list);

/**
 * Insert a new node at the head of the list
 * Returns 1 on success, 0 on failure
 * (was: insert_at_head - returned Node*)
 */
int list_insert_head(LinkedList *list, int value);

/**
 * Insert a new node at the tail of the list
 * Returns 1 on success, 0 on failure
 * (was: insert_at_tail - returned Node*)
 */
int list_insert_tail(LinkedList *list, int value);

/**
 * Delete the first node with the specified value
 * Returns 1 if deleted, 0 if not found
 * (was: delete_node - returned Node*)
 */
int list_delete(LinkedList *list, int value);

/**
 * Get the number of nodes in the list (O(1) now!)
 * (was: get_length - which was O(n))
 */
size_t list_size(const LinkedList *list);

/**
 * Check if the list is empty
 * (was: is_empty)
 */
int list_is_empty(const LinkedList *list);

/**
 * Check if a value exists in the list
 * (was: contains)
 */
int list_contains(const LinkedList *list, int value);

/**
 * Get the node at a specific index (read-only access to data)
 * Returns the Node pointer (NULL if out of bounds)
 * (was: get_node_at)
 */
const Node* list_get_node_at(const LinkedList *list, size_t index);

/**
 * Get the node at a specific index (modifiable access)
 * Returns the Node pointer (NULL if out of bounds)
 * (was: get_node_at_modifiable)
 */
Node* list_get_node_at_modifiable(LinkedList *list, size_t index);

/**
 * Insert a new node at a specific position
 * Returns 1 on success, 0 if index is out of bounds or allocation fails
 * (was: insert_at_position - returned Node*)
 */
int list_insert_at(LinkedList *list, int value, size_t index);

/**
 * Remove the node at a specific index
 * Returns 1 on success, 0 if index is out of bounds
 * (was: remove_element_at - returned Node*)
 */
int list_delete_at(LinkedList *list, size_t index);

/**
 * Reverse the linked list in place
 * (was: reverse_list - returned Node*)
 */
void list_reverse(LinkedList *list);

#endif // LINKED_LIST_H
