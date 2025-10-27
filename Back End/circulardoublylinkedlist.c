#include "resume_architect.h"

// Create new node
struct AdditionalNode* create_additional_node(const char *detail) {
    struct AdditionalNode *newNode = (struct AdditionalNode*)malloc(sizeof(struct AdditionalNode));
    newNode->detail = strdup(detail);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Free circular list
void free_additional_list(struct AdditionalNode *head) {
    if (head == NULL) return;

    struct AdditionalNode *current = head;
    struct AdditionalNode *temp;
    
    // Break the loop
    head->prev->next = NULL; 

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp->detail);
        free(temp);
    }
}

// Inserts at index
struct AdditionalNode* insert_additional_at_index(struct AdditionalNode *head, const char *detail, int index) {
    
    struct AdditionalNode *newNode = create_additional_node(detail);

    if (head == NULL) { // List is empty
        newNode->next = newNode;
        newNode->prev = newNode;
        return newNode;
    }

    if (index == 0) { // Insert at head
        struct AdditionalNode *tail = head->prev;
        
        newNode->next = head;
        head->prev = newNode;
        
        newNode->prev = tail;
        tail->next = newNode;
        
        return newNode; // The new node is the new head
    }

    struct AdditionalNode *current = head;
    int i = 0;
    
    // going before insertion point
    while (i < index - 1) {
        current = current->next;
        if (current == head) break; // Looped complete
        i++;
    }
    
    // Insert after current
    struct AdditionalNode *nextNode = current->next;
    
    current->next = newNode;
    newNode->prev = current;
    
    newNode->next = nextNode;
    nextNode->prev = newNode;
    
    return head; // Head doesn't change
}

// Deletes at index
struct AdditionalNode* delete_additional_at_index(struct AdditionalNode *head, int index) {
    if (head == NULL) return NULL;

    struct AdditionalNode *nodeToDelete = head;
    int i = 0;

    // Traverse at index
    while (i < index) {
        nodeToDelete = nodeToDelete->next;
        if (nodeToDelete == head) return head; // Index out of bounds
        i++;
    }

    // relink listt
    if (nodeToDelete->next == nodeToDelete) {
    // It's the only node
        free(nodeToDelete->detail);
        free(nodeToDelete);
        return NULL; // List is now empty
    }

    nodeToDelete->prev->next = nodeToDelete->next;
    nodeToDelete->next->prev = nodeToDelete->prev;
    
    // dlt head, return new head
    struct AdditionalNode *newHead = (nodeToDelete == head) ? nodeToDelete->next : head;

    //Free the node
    free(nodeToDelete->detail);
    free(nodeToDelete);
    
    return newHead;
}