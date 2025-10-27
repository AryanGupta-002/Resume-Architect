#include "resume_architect.h"

// new node
struct PersonalNode* create_node(const char *field, const char *value) {
    struct PersonalNode *newNode = (struct PersonalNode*)malloc(sizeof(struct PersonalNode));
    newNode->field = strdup(field);
    newNode->value = strdup(value);
    newNode->next = NULL;
    return newNode;
}

// free linked list
void free_list(struct PersonalNode *head) {
    struct PersonalNode *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->field);
        free(tmp->value);
        free(tmp);
    }
}

// inserts a node
struct PersonalNode* insert_at_index(struct PersonalNode *head, const char *field, const char *value, int index) {
    struct PersonalNode *newNode = create_node(field, value);

    // insert at head
    if (index == 0) { 
        newNode->next = head;
        return newNode;
    }

    struct PersonalNode *current = head;
    int i = 0;
    while (current != NULL && i < index - 1) {
        current = current->next;
        i++;
    }

    // index not found, insert at end
    if (current == NULL) { 
        current = head;
        if (current == NULL) return newNode; // List was empty
        while(current->next != NULL) current = current->next;
        current->next = newNode;
    } else { 
        // Insert in the middle
        newNode->next = current->next;
        current->next = newNode;
    }
    return head;
}

// Delete a node 
struct PersonalNode* delete_at_index(struct PersonalNode *head, int index) {
    if (head == NULL) return NULL;

    struct PersonalNode *temp;

    // Delete head
    if (index == 0) { 
        temp = head;
        head = head->next;
        free(temp->field);
        free(temp->value);
        free(temp);
        return head;
    }

    struct PersonalNode *current = head;
    int i = 0;
    while (current->next != NULL && i < index - 1) {
        current = current->next;
        i++;
    }

    if (current->next == NULL) { // Index not found
        return head; // Do nothing
    }

    // Delete the node
    temp = current->next;
    current->next = temp->next;
    free(temp->field);
    free(temp->value);
    free(temp);
    
    return head;
}

// Updates the value of a node at a specific index
void update_at_index(struct PersonalNode *head, int index, const char *new_value) {
    if (head == NULL) return; // List is empty

    struct PersonalNode *current = head;
    int i = 0;
    
    // Traverse to the node *at* the index
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }
    
    // If we found the node (and it's not NULL), update its value
    if (current != NULL) {
        free(current->value); // Free the old value
        current->value = strdup(new_value); // Set the new one
    }
}