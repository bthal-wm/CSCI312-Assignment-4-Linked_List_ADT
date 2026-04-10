# Linked List Building Worksheet - Part of Assignment 4

Last week, we began implementing a linked list ADT by defining the node structure and creating a `create_node()` function. Since our next class is asynchronous, you will continue building your linked list independently using this guide.

**Important:** Your linked list is **Assignment 4**. Your goal is to implement a complete, working linked list library. This worksheet provides the first basic functions required for us to make a complete linked list. Complete as many functions as possible, and we will review your implementations together when we next meet in person to ensure correctness and good practice. Once we have these functions created, we will dive further into our linked list and implement more advanced functions.

In this worksheet, you will build a working linked list library by implementing key operations. Each exercise builds on the previous one, so complete them in order.

**What you'll build:**
- ✅ Link nodes together
- ✅ Traverse and print lists
- ✅ Insert nodes at the head
- ✅ Insert nodes at the tail
- ✅ Delete nodes
- ✅ Free all memory

**How to work:**
1. Create a file called `linkedlist.c`
2. Start with the provided starter code below
3. Complete each exercise by filling in the function bodies
4. Test after each exercise using the provided test code

---

## Starter Code (Provided)

You already created the `Node` structure and `create_node()` function in class. Copy this into your `linkedlist.c` file:

```c
#include <stdio.h>
#include <stdlib.h>

// Node structure (from class)
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Create a new node (from class)
Node* create_node(int value)
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

// TODO: You will implement the functions below
```

---

## Understanding How Nodes Connect

Before we write functions to manage our list, let's understand the fundamental concept: **how nodes link together**.

### The Basic Idea

Each node contains:
- **Data** - the value stored (e.g., `42`)
- **Next pointer** - the memory address of the next node (or `NULL` if it's the last node)

```
┌──────────┬──────────┐
│ data: 42 │ next: ●──┼──→ (points to another Node or NULL)
└──────────┴──────────┘
```

### Manual Linking Example

Let's create three separate nodes and link them together manually:

```c
int main(void)
{
    // Step 1: Create three independent nodes
    Node *first = create_node(10);
    Node *second = create_node(20);
    Node *third = create_node(30);
    
    // At this point, all nodes exist but are NOT connected
    // Each has next = NULL
    
    // Step 2: Link them together by setting next pointers
    first->next = second;   // first → second
    second->next = third;   // second → third
    third->next = NULL;     // third → NULL (already set by create_node)
    
    // Now we have a chain: first → second → third → NULL
    
    // Step 3: We can traverse the chain using the next pointers
    printf("First node: %d\n", first->data);                    // 10
    printf("Second node: %d\n", first->next->data);             // 20
    printf("Third node: %d\n", first->next->next->data);        // 30
    
    // Step 4: Clean up (free each node)
    free(first);
    free(second);
    free(third);
    
    return 0;
}
```

### Visual Representation

**After creating nodes (before linking):**
```
first → [10 | NULL]

second → [20 | NULL]

third → [30 | NULL]

(Three separate nodes, not connected)
```

**After linking (`first->next = second`):**
```
first → [10 | ●]──→ second → [20 | NULL]

third → [30 | NULL]
```

**After all links complete:**
```
first → [10 | ●]──→ [20 | ●]──→ [30 | NULL]
        ↑           ↑           ↑
      first       second      third
```

### Understanding Pointer Chains

When nodes are linked, you can "follow the chain" using the next pointers:

```c
first->data             // Direct access: 10
first->next             // Address of second node
first->next->data       // Follow one link: 20
first->next->next       // Address of third node
first->next->next->data // Follow two links: 30
```

**Key insight:** Once nodes are linked, we only need to keep track of the **head** (first node). We can reach all other nodes by following the `next` pointers!

### The Arrow Operator (`->`)

The `->` operator accesses struct members through a pointer:

```c
first->data      // Same as: (*first).data
first->next      // Same as: (*first).next
```

It's just more convenient syntax for working with pointer-to-struct.

### Why We Need Better Functions

Manual linking works for small examples, but imagine creating a list with 100 nodes! We need functions that:
- Automatically link new nodes to existing lists
- Handle the empty list case (when head is NULL)
- Keep our code clean and reusable

**That's what you'll build in the exercises below!**

---

## Exercise 1: Print the List

### Your Task

Write a function that prints all values in a linked list from head to tail.

**Function signature:**
```c
void print_list(Node *head)
```

**Expected output format:**
```
List: 10 -> 20 -> 30 -> NULL
```

### Steps to Complete

1. Create a pointer called `current` that starts at `head`
2. While `current` is not NULL:
   - Print the current node's data followed by " -> "
   - Move `current` to the next node
3. After the loop, print "NULL\n"

### Write Your Code Here

```c
void print_list(Node *head)
{
    // TODO: Create a current pointer
    
    printf("List: ");
    
    // TODO: Loop through the list
    while (/* YOUR CONDITION HERE */) {
        
        // TODO: Print current->data with " -> "
        
        // TODO: Move to next node
        
    }
    
    printf("NULL\n");
}
```

### Test Your Code

Add this to your `main()` function:

```c
int main(void)
{
    // Manually create and link 3 nodes
    Node *first = create_node(10);
    Node *second = create_node(20);
    Node *third = create_node(30);
    
    first->next = second;
    second->next = third;
    third->next = NULL;  // Already set in create_node, but shown for clarity
    
    // Test print_list
    print_list(first);  // Should print: List: 10 -> 20 -> 30 -> NULL
    
    // Cleanup
    free(first);
    free(second);
    free(third);
    
    return 0;
}
```


### Checkpoint ✓

- [ ] Code compiles without warnings
- [ ] Output shows: `List: 10 -> 20 -> 30 -> NULL`
- [ ] No segmentation faults

---

## Exercise 2: Insert at Head

### Your Task

Write a function that inserts a new node at the **beginning** of the list.

**Function signature:**
```c
Node* insert_at_head(Node *head, int value)
```

**Why return a Node pointer?** The head of the list changes, so we must return the new head.

### Steps to Complete

1. Create a new node with the given value
2. If creation failed, return the original head unchanged
3. Set the new node's `next` pointer to point to the current head
4. Return the new node (it's now the new head)

### Visual Guide

```
Before:  head → [20] → [30] → NULL
Insert 10 at head

After:   head → [10] → [20] → [30] → NULL
```

### Write Your Code Here

```c
Node* insert_at_head(Node *head, int value)
{
    // TODO: Create a new node
    
    // TODO: Check if allocation failed
    
    // TODO: Link new node to current head
    
    // TODO: Return new head
    
}
```

### Test Your Code

Replace your `main()` function with:

```c
int main(void)
{
    Node *list = NULL;  // Start with empty list
    
    // Insert three values at head
    list = insert_at_head(list, 30);  // List: 30
    list = insert_at_head(list, 20);  // List: 20 -> 30
    list = insert_at_head(list, 10);  // List: 10 -> 20 -> 30
    
    print_list(list);  // Should print: List: 10 -> 20 -> 30 -> NULL
    
    // TODO: We'll fix cleanup in a later exercise
    
    return 0;
}
```

### Checkpoint ✓

- [ ] Can insert into an empty list (NULL)
- [ ] Output shows: `List: 10 -> 20 -> 30 -> NULL`
- [ ] Code compiles without warnings

---

## Exercise 3: Insert at Tail

### Your Task

Write a function that inserts a new node at the **end** of the list.

**Function signature:**
```c
Node* insert_at_tail(Node *head, int value)
```

### Steps to Complete

1. Create a new node with the given value
2. If creation failed, return the original head
3. **Special case:** If head is NULL, return the new node (it becomes the head)
4. Otherwise:
   - Traverse to the last node (where `next` is NULL)
   - Set the last node's `next` to point to the new node
5. Return head (it doesn't change)

### Key Question

**Q:** In the traversal loop, should you use `current != NULL` or `current->next != NULL`?

**Think about it:** If you use `current != NULL`, where will you be when the loop stops?

<details>
<summary>Answer</summary>
Use `current->next != NULL` so you stop AT the last node, not AFTER it.
</details>

### Write Your Code Here

```c
Node* insert_at_tail(Node *head, int value)
{
    // TODO: Create new node
    
    // TODO: Check if allocation failed
    
    // TODO: Special case - if head is NULL, return new node
    
    // TODO: Find the last node
    Node *current = head;
    while (/* YOUR CONDITION HERE */) {
        current = current->next;
    }
    
    // TODO: Attach new node to end
    
    // TODO: Return head
    
}
```

### Test Your Code

Update your `main()` function:

```c
int main(void)
{
    Node *list = NULL;
    
    // Build list using insert_at_tail
    list = insert_at_tail(list, 10);  // List: 10
    list = insert_at_tail(list, 20);  // List: 10 -> 20
    list = insert_at_tail(list, 30);  // List: 10 -> 20 -> 30
    
    print_list(list);  // Should print: List: 10 -> 20 -> 30 -> NULL
    
    return 0;
}
```

### Checkpoint ✓

- [ ] Can insert into an empty list
- [ ] Output shows: `List: 10 -> 20 -> 30 -> NULL`
- [ ] Values appear in the order they were inserted

---

## Exercise 4: Destroy Node and Free the List

### Software Engineering Best Practice: Single Responsibility

Following good software engineering principles, we should separate concerns:
- **destroy_node()** - Responsible for freeing a single node
- **free_list()** - Responsible for traversing the list and calling destroy_node()

This makes our code more modular, testable, and maintainable.

### Part A: Destroy a Single Node

Write a helper function that frees a single node and sets the pointer to NULL.

**Function signature:**
```c
void destroy_node(Node **node_ptr)
```

**Why use a double pointer?** We want to set the caller's pointer to NULL after freeing, preventing accidental use-after-free bugs.

### Write Your Code Here

```c
void destroy_node(Node **node_ptr)
{
    // TODO: Check if node_ptr or *node_ptr is NULL
    if (node_ptr == NULL || *node_ptr == NULL) {
        return;
    }
    
    // TODO: Free the node
    
    // TODO: Set caller's pointer to NULL
    
}
```

### Part B: Free the Entire List

Now write a function that frees all nodes in a linked list using destroy_node().

**Function signature:**
```c
void free_list(Node *head)
```

### Critical Warning ⚠️

**This is WRONG and will cause bugs:**
```c
while (head != NULL) {
    free(head);           // Free the memory
    head = head->next;    // ❌ DANGER! Can't use head after freeing!
}
```

Once you call `free(head)`, you cannot safely access `head->next`!

### Solution: Save the Next Pointer First

```c
while (head != NULL) {
    Node *temp = head;      // Save pointer to current node
    head = head->next;      // Move to next BEFORE freeing
    destroy_node(&temp);    // Now safe to destroy (also sets temp to NULL)
}
```

### Write Your Code Here

```c
void free_list(Node *head)
{
    // TODO: Loop while head is not NULL
    
        // TODO: Save current node in temp
        
        // TODO: Move head to next node
        
        // TODO: Call destroy_node on temp (pass &temp)
        
}
```

### Test Your Code

Update your `main()` function:

```c
int main(void)
{
    Node *list = NULL;
    
    // Build a list
    list = insert_at_tail(list, 10);
    list = insert_at_tail(list, 20);
    list = insert_at_tail(list, 30);
    list = insert_at_tail(list, 40);
    list = insert_at_tail(list, 50);
    
    print_list(list);
    
    // Free all memory
    free_list(list);
    printf("All memory freed successfully!\n");
    
    return 0;
}
```

**To check for memory leaks (Linux/Mac):**
```bash
gcc -g -Wall linkedlist.c -o linkedlist
valgrind --leak-check=full ./linkedlist
```

You should see: "All heap blocks were freed -- no leaks are possible"

### Checkpoint ✓

- [ ] Code compiles and runs
- [ ] No segmentation faults
- [ ] Valgrind reports no memory leaks (if available)

---

## Exercise 5: Delete a Node

### Your Task

Write a function that finds and deletes the first node with a given value.

**Function signature:**
```c
Node* delete_node(Node *head, int value)
```

### Challenge: Two Pointers

To delete a node, you need to:
1. Find the node to delete (`current`)
2. Know the **previous** node so you can update its `next` pointer

You must track **two pointers** as you traverse!

### Special Cases to Handle

1. **Empty list:** Return NULL
2. **Deleting the head:** No previous node exists, return new head
3. **Value not found:** Return head unchanged
4. **Deleting middle/tail:** Update previous node's next pointer

### Visual Guide

Delete node with value 20:

```
Before:
head → [10] → [20] → [30] → NULL
       prev   curr

After updating pointers:
head → [10] --------→ [30] → NULL
              [20]  (freed)
```

### Write Your Code Here

```c
Node* delete_node(Node *head, int value)
{
    // TODO: Handle empty list
    if (head == NULL) {
        return NULL;
    }
    
    // TODO: Special case - deleting the head node
    if (head->data == value) {
        // Save the new head
        // Free old head
        // Return new head
        
    }
    
    // TODO: Find the node to delete (track previous)
    Node *current = head;
    Node *prev = NULL;
    
    while (/* node not found AND not at end */) {
        prev = current;
        current = current->next;
    }
    
    // TODO: If not found, return head unchanged
    if (current == NULL) {
        return head;
    }
    
    // TODO: Delete the node
    // Update prev->next to skip current
    // Call destroy_node on current (pass &current)
    // Return head
    
}
```

### Test Your Code

Update your `main()` function:

```c
int main(void)
{
    Node *list = NULL;
    
    // Build list: 10 -> 20 -> 30 -> 40
    list = insert_at_tail(list, 10);
    list = insert_at_tail(list, 20);
    list = insert_at_tail(list, 30);
    list = insert_at_tail(list, 40);
    
    printf("Original: ");
    print_list(list);
    
    // Delete middle node
    list = delete_node(list, 20);
    printf("After deleting 20: ");
    print_list(list);  // Should show: 10 -> 30 -> 40 -> NULL
    
    // Delete head
    list = delete_node(list, 10);
    printf("After deleting 10: ");
    print_list(list);  // Should show: 30 -> 40 -> NULL
    
    // Delete tail
    list = delete_node(list, 40);
    printf("After deleting 40: ");
    print_list(list);  // Should show: 30 -> NULL
    
    // Try to delete non-existent value
    list = delete_node(list, 99);
    printf("After trying to delete 99: ");
    print_list(list);  // Should show: 30 -> NULL (unchanged)
    
    // Cleanup
    free_list(list);
    
    return 0;
}
```

### Expected Output

```
Original: List: 10 -> 20 -> 30 -> 40 -> NULL
After deleting 20: List: 10 -> 30 -> 40 -> NULL
After deleting 10: List: 30 -> 40 -> NULL
After deleting 40: List: 30 -> NULL
After trying to delete 99: List: 30 -> NULL
```

### Checkpoint ✓

- [ ] Can delete a middle node
- [ ] Can delete the head node
- [ ] Can delete the tail node
- [ ] Handles deleting from empty list
- [ ] Handles value not found
- [ ] All tests produce correct output

---

## Common Mistakes to Avoid

### ❌ Mistake 1: Forgetting to Update Head
```c
Node *list = NULL;
insert_at_head(list, 10);  // WRONG! list is still NULL
```

✅ **Correct:**
```c
list = insert_at_head(list, 10);
```

### ❌ Mistake 2: Using Memory After Free
```c
free(node);
printf("%d", node->data);  // WRONG! node is freed
```

### ❌ Mistake 3: Wrong Loop Condition for Tail Insert
```c
while (current != NULL)  // WRONG! Will stop AFTER last node
```

✅ **Correct:**
```c
while (current->next != NULL)  // Stop AT last node
```

## What You've Accomplished! 🎉

✅ Built a working linked list from scratch  
✅ Implemented core operations (insert, delete, traverse)  
✅ Managed dynamic memory correctly  
✅ Handled edge cases (empty list, single element)  
✅ Practiced pointer manipulation  

