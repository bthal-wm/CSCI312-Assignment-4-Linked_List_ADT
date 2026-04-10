#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

// =============================================================================
// HELPER FUNCTIONS (Private - not in header)
// These stay the same as before!
// =============================================================================

/**
 * Create a new node (internal helper function)
 * You can copy this from your original linked_list.c
 */
static Node* create_node(int value)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

/**
 * Destroy a single node (internal helper function)
 * You can copy this from your original linked_list.c
 */
static void destroy_node(Node **node_ptr)
{
    if (node_ptr == NULL || *node_ptr == NULL) {
        return;
    }
    free(*node_ptr);
    *node_ptr = NULL;
}

// =============================================================================
// REQUIRED NEW FUNCTIONS
// =============================================================================

LinkedList* list_create(void)
{
    // TODO: We'll implement this together
    // Hint: Allocate a LinkedList, initialize head=NULL and size=0
}

void list_destroy(LinkedList *list)
{
    // TODO: We'll implement this together
    // Hint: Traverse and free all nodes, then free the wrapper struct
    // This replaces free_list() from the original
}

// =============================================================================
// REFACTORED FUNCTIONS
// =============================================================================

void list_print(const LinkedList *list)
{
    // TODO: Refactor print_list() to work with LinkedList*
    // The traversal logic is the same - just use list->head
}

int list_insert_head(LinkedList *list, int value)
{
    // TODO: Refactor insert_at_head()
    // Remember the pattern:
    //   1. Validate list pointer
    //   2. Create new node (same as before!)
    //   3. Update links (same as before!)
    //   4. Increment list->size
    //   5. Return 1 for success, 0 for failure
}

int list_insert_tail(LinkedList *list, int value)
{
    // TODO: Refactor insert_at_tail()
    // Same logic as before, but:
    //   - Check if list is NULL
    //   - Use list->head instead of head
    //   - Increment list->size
    //   - Return success status instead of Node*
}

int list_delete(LinkedList *list, int value)
{
    // TODO: Refactor delete_node()
    // Remember to:
    //   - Check if list is NULL or empty
    //   - Handle deleting the head node specially
    //   - Decrement list->size when you delete
    //   - Return 1 if deleted, 0 if not found
}

size_t list_size(const LinkedList *list)
{
    // TODO: Refactor get_length()
    // This is now O(1) instead of O(n)!
    // Just return list->size (with null check)
}

int list_is_empty(const LinkedList *list)
{
    // TODO: Refactor is_empty()
    // Check if list is NULL or list->head is NULL
}

int list_contains(const LinkedList *list, int value)
{
    // TODO: Refactor contains()
    // The search logic is exactly the same!
}

const Node* list_get_node_at(const LinkedList *list, size_t index)
{
    // TODO: Refactor get_node_at()
    // Same traversal logic, just use list->head
    // Hint: Can use list->size to validate index quickly
}

Node* list_get_node_at_modifiable(LinkedList *list, size_t index)
{
    // TODO: Refactor get_node_at_modifiable()
    // Can just cast the result from list_get_node_at()
}

int list_insert_at(LinkedList *list, int value, size_t index)
{
    // TODO: Refactor insert_at_position()
    // Special case: index == 0 means insert at head
    // Don't forget to increment list->size!
    // Return success status instead of Node*
}

int list_delete_at(LinkedList *list, size_t index)
{
    // TODO: Refactor remove_element_at()
    // Validate: index < list->size
    // Don't forget to decrement list->size!
    // Return success status instead of Node*
}

void list_reverse(LinkedList *list)
{
    // TODO: Refactor reverse_list()
    // The reversal logic is IDENTICAL!
    // Works on list->head, size doesn't change
    // No return value needed - modifies in place
}

int main(void)
{   
    return 0;
}
