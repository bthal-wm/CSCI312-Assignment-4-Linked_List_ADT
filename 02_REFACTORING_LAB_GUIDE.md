# Lab: Refactoring to a Linked List ADT

**Time:** 80 minutes  
**Goal:** Transform your pointer-based linked list into a proper Abstract Data Type

---

## Learning Objectives

By the end of this lab, you will:
- ✅ Understand why wrapper structs improve API design
- ✅ Implement O(1) size tracking using cached metadata
- ✅ Practice real-world refactoring techniques
- ✅ Compare trade-offs between different design approaches

---

## The Problem with Our Current Design

```c
// Current API - Error prone!
Node* head = NULL;
head = insert_at_head(head, 10);  // Easy to forget return value!
head = insert_at_head(head, 20);  // Must always capture the return

int count = get_length(head);     // O(n) - traverses entire list!
```

**Issues:**
1. ❌ Must remember to capture return value from insertions
2. ❌ Counting elements requires O(n) traversal every time
3. ❌ No encapsulation - internal structure exposed
4. ❌ Can't easily add metadata (size, tail pointer, etc.)

---

## The Solution: Wrapper Struct (ADT)

```c
// New API - Much safer!
LinkedList* list = list_create();
list_insert_head(list, 10);      // Modifies in place - can't forget!
list_insert_head(list, 20);      // Clean and obvious

size_t count = list_size(list);  // O(1) - just returns cached value!
list_destroy(list);              // Clean memory management
```

**Benefits:**
1. ✅ Safer API - functions modify list in place
2. ✅ O(1) size queries - size is cached in struct
3. ✅ Encapsulation - hide implementation details
4. ✅ Extensible - easy to add tail pointer, capacity limits, etc.

---

## Part 1: Understanding the Wrapper Struct (10 min)

### The New Structure

```c
// Internal node - UNCHANGED from your original code
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// NEW: Wrapper struct that encapsulates the list
typedef struct LinkedList {
    Node *head;      // Pointer to first node (same as before)
    size_t size;     // Cached count - enables O(1) lookup!
} LinkedList;
```

**Important:** The Node structure is identical. We're just wrapping it!

### Key Concept: Two Levels of Memory Management

```
Stack/Heap          Heap (nodes)
┌─────────────┐
│ LinkedList  │     ┌──────┐    ┌──────┐    ┌──────┐
│ ┌─────────┐ │     │ data │    │ data │    │ data │
│ │ head  ──┼─┼────→│  10  │───→│  20  │───→│  30  │
│ └─────────┘ │     │ next │    │ next │    │ next │
│ ┌─────────┐ │     └──────┘    └──────┘    └──────┘
│ │ size: 3 │ │
│ └─────────┘ │
└─────────────┘
```

---

## Part 2: Refactoring Pattern (20 min)

### General Refactoring Steps

For each function, follow this pattern:

#### Before (Returns Node*)
```c
Node* insert_at_head(Node *head, int value) {
    Node *new_node = create_node(value);
    if (new_node == NULL) {
        return head;  // Return old head on failure
    }
    
    new_node->next = head;
    return new_node;  // Return new head
}
```

#### After (Returns int status)
```c
int list_insert_head(LinkedList *list, int value) {
    if (list == NULL) {              // 1. Validate list pointer
        return 0;
    }
    
    Node *new_node = create_node(value);
    if (new_node == NULL) {          // 2. Check allocation
        return 0;
    }
    
    new_node->next = list->head;     // 3. Update links (same logic!)
    list->head = new_node;
    list->size++;                    // 4. Update metadata ⭐ NEW!
    
    return 1;                        // 5. Return success status
}
```

### The Refactoring Checklist

For EVERY function that modifies the list:

- [ ] Change parameter from `Node *head` to `LinkedList *list`
- [ ] Add null check for `list` pointer
- [ ] Change `head` references to `list->head`
- [ ] For insertions: add `list->size++`
- [ ] For deletions: add `list->size--`
- [ ] Change return type and return success/failure (or keep `void`)

---

## Part 3: Live Coding Together (Minutes 10-30)

### Function 1: Create & Destroy (NEW - not in original)

We'll code these together as a class:

```c
LinkedList* list_create(void);      // Allocate wrapper struct
void list_destroy(LinkedList *list); // Replaces free_list()
```

**Why new?** Because we need to allocate/free the wrapper struct.

### Function 2: Insert at Head (REFACTORED)

We'll refactor your `insert_at_head()` together to show the pattern:

```c
int list_insert_head(LinkedList *list, int value);
```

**Key changes from your original:**
- Parameter: `Node *head` → `LinkedList *list`
- Return: `Node*` → `int` (success/failure)
- Add: `list->size++`

### Function 3: Get Size

We'll see how `get_length()` becomes O(1):

```c
size_t list_size(const LinkedList *list);
```

**This used to traverse the entire list - now it's instant!**

---

## Part 4: Your Turn! (Minutes 30-65)

Refactor these functions on your own (or with a partner). Each function already exists in your original `linked_list.c` - you're just adapting them to the new API!

### ⭐ TIER 1: Basic Functions (Everyone should complete)

1. **`void list_print(const LinkedList *list)`**
   - Original: `print_list(const Node *head)`
   - Hint: Same logic, just use `list->head` for traversal

2. **`int list_insert_tail(LinkedList *list, int value)`**
   - Original: `insert_at_tail(Node *head, int value)` 
   - Hint: Same logic, but add `list->size++` and return status

3. **`int list_delete(LinkedList *list, int value)`**
   - Original: `delete_node(Node *head, int value)`
   - Hint: Don't forget `list->size--` when you delete!

4. **`size_t list_size(const LinkedList *list)`**
   - Original: `get_length(const Node *head)` 
   - Hint: This is now O(1)! Just return `list->size`

5. **`int list_is_empty(const LinkedList *list)`**
   - Original: `is_empty(const Node *head)`
   - Hint: Check if `list->head == NULL`

### ⭐⭐ TIER 2: Intermediate Functions (Try these next)

6. **`int list_contains(const LinkedList *list, int value)`**
   - Original: `contains(const Node *head, int value)`
   - Hint: Same search logic - just change parameters

7. **`const Node* list_get_node_at(const LinkedList *list, size_t index)`**
   - Original: `get_node_at(const Node *head, int index)`
   - Hint: Use `list->size` to validate the index quickly!

8. **`Node* list_get_node_at_modifiable(LinkedList *list, size_t index)`**
   - Original: `get_node_at_modifiable(Node *head, int index)`
   - Hint: Can cast the result from `list_get_node_at()`

9. **`int list_insert_at(LinkedList *list, int value, size_t index)`**
   - Original: `insert_at_position(Node *head, int value, int index)`
   - Hint: Remember to increment `list->size`!

### ⭐⭐⭐ TIER 3: Challenge Functions (For fast finishers)

10. **`int list_delete_at(LinkedList *list, size_t index)`**
    - Original: `remove_element_at(Node *head, int index)`
    - Hint: Validate `index < list->size`, then decrement size

11. **`void list_reverse(LinkedList *list)`**
    - Original: `reverse_list(Node *head)`
    - Hint: The reversal logic is IDENTICAL! Size doesn't change.

---

## Part 5: Testing Your Code (Minutes 65-75)

### Compile and Test

```bash
gcc linked_list.c -o test
./test
```

### Run Unit Tests

A comprehensive test suite is provided to verify all functions:

```bash
# Compile the unit tests
gcc test_linked_list.c linked_list.c -o test_linked_list

# Run the tests
./test_linked_list
```

The unit tests will:
- ✓ Test all functions systematically
- ✓ Report which tests pass/fail
- ✓ Show a summary at the end
- ✓ Verify edge cases (NULL pointers, empty lists, etc.)

Expected output:
```
========================================
  Linked List ADT Unit Tests
========================================

=== Testing list_create() and list_destroy() ===
✓ PASS: list_create returns non-NULL
✓ PASS: new list has size 0
...

========================================
  Test Summary
========================================
Tests passed: 75 / 75
🎉 All tests passed!
```

---

## Common Mistakes to Avoid

### ❌ Mistake 1: Forgetting to Update Size
```c
// WRONG - forgot to update metadata
int list_insert_head(LinkedList *list, int value) {
    Node *new_node = create_node(value);
    new_node->next = list->head;
    list->head = new_node;
    // Forgot: list->size++;
    return 1;
}

// CORRECT
int list_insert_head(LinkedList *list, int value) {
    Node *new_node = create_node(value);
    new_node->next = list->head;
    list->head = new_node;
    list->size++;  // ✅ Don't forget this!
    return 1;
}
```

### ❌ Mistake 2: Forgetting List Null Check
```c
// WRONG - will crash if list is NULL!
int list_insert_head(LinkedList *list, int value) {
    list->head = create_node(value);  // Crashes if list is NULL!
    return 1;
}

// CORRECT
int list_insert_head(LinkedList *list, int value) {
    if (list == NULL) return 0;  // Check first!
    // ... rest of function
}
```

### ❌ Mistake 3: Copying Old Logic Incorrectly
```c
// Your original code:
Node* insert_at_tail(Node *head, int value) {
    // ... creates node ...
    return head;  // Returns the head pointer
}

// WRONG refactoring - still returning a pointer
Node* list_insert_tail(LinkedList *list, int value) {
    // ...
    return list->head;  // Wrong return type!
}

// CORRECT refactoring - return success status
int list_insert_tail(LinkedList *list, int value) {
    // ... same logic ...
    list->size++;
    return 1;  // Return success!
}
```

---

## Quick Reference: Function Signature Changes

| Original Function | New ADT Function |
|-------------------|------------------|
| `void print_list(const Node *head)` | `void list_print(const LinkedList *list)` |
| `Node* insert_at_head(Node *head, int v)` | `int list_insert_head(LinkedList *list, int v)` |
| `Node* insert_at_tail(Node *head, int v)` | `int list_insert_tail(LinkedList *list, int v)` |
| `Node* delete_node(Node *head, int v)` | `int list_delete(LinkedList *list, int v)` |
| `int get_length(const Node *head)` | `size_t list_size(const LinkedList *list)` |
| `int is_empty(const Node *head)` | `int list_is_empty(const LinkedList *list)` |
| `int contains(const Node *head, int v)` | `int list_contains(const LinkedList *list, int v)` |
| `const Node* get_node_at(const Node *head, int i)` | `const Node* list_get_node_at(const LinkedList *list, size_t i)` |
| `Node* get_node_at_modifiable(Node *head, int i)` | `Node* list_get_node_at_modifiable(LinkedList *list, size_t i)` |
| `Node* insert_at_position(Node *head, int v, int i)` | `int list_insert_at(LinkedList *list, int v, size_t i)` |
| `Node* remove_element_at(Node *head, int i)` | `int list_delete_at(LinkedList *list, size_t i)` |
| `Node* reverse_list(Node *head)` | `void list_reverse(LinkedList *list)` |
| `void free_list(Node *head)` | `void list_destroy(LinkedList *list)` ⭐ |

⭐ = Also need `list_create()` to allocate the wrapper struct

---

## Resources

- `linked_list.h` - Header file with function signatures
- `linked_list.c` - Your implementation (to complete)
- `test_linked_list.c` - Comprehensive unit tests

---
## Assignment 4 Grading

- Turn in your working `linked_list.c` file to Github Classroom
- Ensure your linked list implementation works with the provided test suite
- All functions must be implemented correctly to receive full credit
- Any failures in the test suite will result in a reduction of points
- All functions implemented for our linked list were discussed in-class, and you should have a working linked list implementation if you followed along.
- If you did not attend class or did not do the worksheet provide, you will need to take additional time to complete your linked list (following the provided worksheet and refactoring guide).
