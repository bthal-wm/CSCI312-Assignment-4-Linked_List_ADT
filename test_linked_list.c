#include <stdio.h>
#include <assert.h>
#include "linked_list.h"

// Test counter
static int tests_passed = 0;
static int tests_total = 0;

// Helper macro for testing
#define TEST(name, condition) do { \
    tests_total++; \
    if (condition) { \
        printf("✓ PASS: %s\n", name); \
        tests_passed++; \
    } else { \
        printf("✗ FAIL: %s\n", name); \
    } \
} while(0)

void test_create_destroy(void) {
    printf("\n=== Testing list_create() and list_destroy() ===\n");
    
    LinkedList *list = list_create();
    TEST("list_create returns non-NULL", list != NULL);
    TEST("new list has size 0", list_size(list) == 0);
    TEST("new list is empty", list_is_empty(list) == 1);
    
    list_destroy(list);
    printf("list_destroy completed without crash\n");
}

void test_insert_head(void) {
    printf("\n=== Testing list_insert_head() ===\n");
    
    LinkedList *list = list_create();
    
    TEST("insert 10 at head returns success", list_insert_head(list, 10) == 1);
    TEST("size is 1 after insert", list_size(list) == 1);
    TEST("list is not empty", list_is_empty(list) == 0);
    
    TEST("insert 20 at head returns success", list_insert_head(list, 20) == 1);
    TEST("size is 2 after second insert", list_size(list) == 2);
    
    // Check order (20 should be first, then 10)
    const Node* node = list_get_node_at(list, 0);
    TEST("first node has value 20", node != NULL && node->data == 20);
    
    node = list_get_node_at(list, 1);
    TEST("second node has value 10", node != NULL && node->data == 10);
    
    list_destroy(list);
}

void test_insert_tail(void) {
    printf("\n=== Testing list_insert_tail() ===\n");
    
    LinkedList *list = list_create();
    
    TEST("insert 10 at tail returns success", list_insert_tail(list, 10) == 1);
    TEST("size is 1 after insert", list_size(list) == 1);
    
    TEST("insert 20 at tail returns success", list_insert_tail(list, 20) == 1);
    TEST("size is 2 after second insert", list_size(list) == 2);
    
    // Check order (10 should be first, then 20)
    const Node* node = list_get_node_at(list, 0);
    TEST("first node has value 10", node != NULL && node->data == 10);
    
    node = list_get_node_at(list, 1);
    TEST("second node has value 20", node != NULL && node->data == 20);
    
    list_destroy(list);
}

void test_contains(void) {
    printf("\n=== Testing list_contains() ===\n");
    
    LinkedList *list = list_create();
    
    list_insert_head(list, 10);
    list_insert_head(list, 20);
    list_insert_head(list, 30);
    
    TEST("list contains 10", list_contains(list, 10) == 1);
    TEST("list contains 20", list_contains(list, 20) == 1);
    TEST("list contains 30", list_contains(list, 30) == 1);
    TEST("list does not contain 99", list_contains(list, 99) == 0);
    
    list_destroy(list);
}

void test_delete(void) {
    printf("\n=== Testing list_delete() ===\n");
    
    LinkedList *list = list_create();
    
    list_insert_head(list, 10);
    list_insert_head(list, 20);
    list_insert_head(list, 30);
    // List is now: 30 -> 20 -> 10
    
    TEST("delete 20 returns success", list_delete(list, 20) == 1);
    TEST("size is 2 after delete", list_size(list) == 2);
    TEST("list no longer contains 20", list_contains(list, 20) == 0);
    TEST("list still contains 10", list_contains(list, 10) == 1);
    TEST("list still contains 30", list_contains(list, 30) == 1);
    
    TEST("delete non-existent value returns failure", list_delete(list, 99) == 0);
    TEST("size unchanged after failed delete", list_size(list) == 2);
    
    list_destroy(list);
}

void test_get_node_at(void) {
    printf("\n=== Testing list_get_node_at() ===\n");
    
    LinkedList *list = list_create();
    
    list_insert_tail(list, 10);
    list_insert_tail(list, 20);
    list_insert_tail(list, 30);
    // List is: 10 -> 20 -> 30
    
    const Node* node = list_get_node_at(list, 0);
    TEST("get node at index 0 returns non-NULL", node != NULL);
    TEST("node at index 0 has value 10", node != NULL && node->data == 10);
    
    node = list_get_node_at(list, 1);
    TEST("node at index 1 has value 20", node != NULL && node->data == 20);
    
    node = list_get_node_at(list, 2);
    TEST("node at index 2 has value 30", node != NULL && node->data == 30);
    
    node = list_get_node_at(list, 99);
    TEST("get node at invalid index returns NULL", node == NULL);
    
    list_destroy(list);
}

void test_get_node_at_modifiable(void) {
    printf("\n=== Testing list_get_node_at_modifiable() ===\n");
    
    LinkedList *list = list_create();
    
    list_insert_tail(list, 10);
    list_insert_tail(list, 20);
    list_insert_tail(list, 30);
    
    Node* node = list_get_node_at_modifiable(list, 1);
    TEST("get modifiable node returns non-NULL", node != NULL);
    
    if (node != NULL) {
        node->data = 99;  // Modify the node
        const Node* check = list_get_node_at(list, 1);
        TEST("modified node has new value 99", check != NULL && check->data == 99);
    }
    
    list_destroy(list);
}

void test_insert_at(void) {
    printf("\n=== Testing list_insert_at() ===\n");
    
    LinkedList *list = list_create();
    
    // Insert at position 0 in empty list
    TEST("insert at index 0 in empty list succeeds", list_insert_at(list, 10, 0) == 1);
    TEST("size is 1", list_size(list) == 1);
    
    // Insert at head (index 0)
    TEST("insert at index 0 succeeds", list_insert_at(list, 5, 0) == 1);
    TEST("size is 2", list_size(list) == 2);
    
    // Insert in middle
    TEST("insert at index 1 succeeds", list_insert_at(list, 7, 1) == 1);
    TEST("size is 3", list_size(list) == 3);
    
    // Verify order: 5 -> 7 -> 10
    const Node* node = list_get_node_at(list, 0);
    TEST("node at index 0 is 5", node != NULL && node->data == 5);
    node = list_get_node_at(list, 1);
    TEST("node at index 1 is 7", node != NULL && node->data == 7);
    node = list_get_node_at(list, 2);
    TEST("node at index 2 is 10", node != NULL && node->data == 10);
    
    // Insert at end
    TEST("insert at end succeeds", list_insert_at(list, 20, 3) == 1);
    TEST("size is 4", list_size(list) == 4);
    
    // Try invalid index
    TEST("insert at invalid index fails", list_insert_at(list, 99, 100) == 0);
    TEST("size unchanged after failed insert", list_size(list) == 4);
    
    list_destroy(list);
}

void test_delete_at(void) {
    printf("\n=== Testing list_delete_at() ===\n");
    
    LinkedList *list = list_create();
    
    list_insert_tail(list, 10);
    list_insert_tail(list, 20);
    list_insert_tail(list, 30);
    list_insert_tail(list, 40);
    // List is: 10 -> 20 -> 30 -> 40
    
    TEST("delete at index 1 succeeds", list_delete_at(list, 1) == 1);
    TEST("size is 3 after delete", list_size(list) == 3);
    
    // Verify order: 10 -> 30 -> 40
    const Node* node = list_get_node_at(list, 0);
    TEST("node at index 0 is 10", node != NULL && node->data == 10);
    node = list_get_node_at(list, 1);
    TEST("node at index 1 is 30", node != NULL && node->data == 30);
    node = list_get_node_at(list, 2);
    TEST("node at index 2 is 40", node != NULL && node->data == 40);
    
    // Delete at head
    TEST("delete at index 0 succeeds", list_delete_at(list, 0) == 1);
    TEST("size is 2 after delete", list_size(list) == 2);
    
    // Try invalid index
    TEST("delete at invalid index fails", list_delete_at(list, 100) == 0);
    TEST("size unchanged after failed delete", list_size(list) == 2);
    
    list_destroy(list);
}

void test_reverse(void) {
    printf("\n=== Testing list_reverse() ===\n");
    
    LinkedList *list = list_create();
    
    list_insert_tail(list, 10);
    list_insert_tail(list, 20);
    list_insert_tail(list, 30);
    list_insert_tail(list, 40);
    // List is: 10 -> 20 -> 30 -> 40
    
    list_reverse(list);
    
    TEST("size unchanged after reverse", list_size(list) == 4);
    
    // Verify reversed order: 40 -> 30 -> 20 -> 10
    const Node* node = list_get_node_at(list, 0);
    TEST("node at index 0 is 40", node != NULL && node->data == 40);
    node = list_get_node_at(list, 1);
    TEST("node at index 1 is 30", node != NULL && node->data == 30);
    node = list_get_node_at(list, 2);
    TEST("node at index 2 is 20", node != NULL && node->data == 20);
    node = list_get_node_at(list, 3);
    TEST("node at index 3 is 10", node != NULL && node->data == 10);
    
    // Test reverse on empty list
    LinkedList *empty = list_create();
    list_reverse(empty);
    TEST("reverse on empty list doesn't crash", 1);
    TEST("empty list still has size 0", list_size(empty) == 0);
    
    list_destroy(list);
    list_destroy(empty);
}

void test_print(void) {
    printf("\n=== Testing list_print() ===\n");
    
    LinkedList *list = list_create();
    
    printf("Printing empty list: ");
    list_print(list);
    
    list_insert_tail(list, 10);
    list_insert_tail(list, 20);
    list_insert_tail(list, 30);
    
    printf("Printing list with 3 elements: ");
    list_print(list);
    
    printf("list_print() completed without crash\n");
    
    list_destroy(list);
}

void test_edge_cases(void) {
    printf("\n=== Testing Edge Cases ===\n");
    
    // Test NULL list pointer handling
    TEST("list_size on NULL returns 0", list_size(NULL) == 0);
    TEST("list_is_empty on NULL returns 1", list_is_empty(NULL) == 1);
    TEST("list_contains on NULL returns 0", list_contains(NULL, 10) == 0);
    TEST("list_insert_head on NULL returns 0", list_insert_head(NULL, 10) == 0);
    TEST("list_insert_tail on NULL returns 0", list_insert_tail(NULL, 10) == 0);
    TEST("list_delete on NULL returns 0", list_delete(NULL, 10) == 0);
    
    // Test operations on empty list
    LinkedList *empty = list_create();
    TEST("delete from empty list returns 0", list_delete(empty, 10) == 0);
    TEST("get node from empty list returns NULL", list_get_node_at(empty, 0) == NULL);
    
    list_destroy(empty);
}

int main(void) {
    printf("========================================\n");
    printf("  Linked List ADT Unit Tests\n");
    printf("========================================\n");
    
    test_create_destroy();
    test_insert_head();
    test_insert_tail();
    test_contains();
    test_delete();
    test_get_node_at();
    test_get_node_at_modifiable();
    test_insert_at();
    test_delete_at();
    test_reverse();
    test_print();
    test_edge_cases();
    
    printf("\n========================================\n");
    printf("  Test Summary\n");
    printf("========================================\n");
    printf("Tests passed: %d / %d\n", tests_passed, tests_total);
    
    if (tests_passed == tests_total) {
        printf("🎉 All tests passed!\n");
        return 0;
    } else {
        printf("❌ Some tests failed.\n");
        return 1;
    }
}
