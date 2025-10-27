#include "resume_architect.h"

// new node
struct EducationNode* create_education_node(const char *name, const char *course_year, float score) {
    struct EducationNode *newNode = (struct EducationNode*)malloc(sizeof(struct EducationNode));
    newNode->name = strdup(name);
    newNode->course_year = strdup(course_year);
    newNode->score = score;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Free list
void free_education_list(struct EducationNode *head) {
    struct EducationNode *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->name);
        free(tmp->course_year);
        free(tmp);
    }
}

// Inserts a node
struct EducationNode* insert_education_at_index(struct EducationNode *head, const char *name, const char *course_year, float score, int index) {
    
    struct EducationNode *newNode = create_education_node(name, course_year, score);

    // Insert at head
    if (index == 0) { 
        newNode->next = head;
        if (head != NULL) {
            head->prev = newNode;
        }
         // when new node is new head
        return newNode;
    }

    struct EducationNode *current = head;
    int i = 0;
    
    // going to node before insertion point
    while (current != NULL && i < index - 1) {
        current = current->next;
        i++;
    }

    // index not found, insent at end kardiya
    if (current == NULL) { 

        // to to end
        if (head == NULL) return newNode; // List was empty
        current = head;
        while (current->next != NULL) {
            current = current->next;
        }

        // current is now the last node
        current->next = newNode;
        newNode->prev = current;
    } else { 

        // Insert in the middle or at the end (agar current, last node ho toh )
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next != NULL) {
             // If it's not the end
            current->next->prev = newNode;
        }
        current->next = newNode;
    }
    return head;
}

// Deletes a node 
struct EducationNode* delete_education_at_index(struct EducationNode *head, int index) {
    if (head == NULL) return NULL;

    struct EducationNode *nodeToDelete = head;
    int i = 0;

    // Traverse to node at index
    while (nodeToDelete != NULL && i < index) {
        nodeToDelete = nodeToDelete->next;
        i++;
    }

    if (nodeToDelete == NULL) { // index not found then did nothing
        return head;
    }

    // Relink the list

     // Is it the head?
    if (nodeToDelete->prev != NULL) { 
        //No
        nodeToDelete->prev->next = nodeToDelete->next;
    } else { 
        // Yes, it is the head
        head = nodeToDelete->next; // The next node is now the new head
    }

    if (nodeToDelete->next != NULL) { // Is it the tail? No.
        nodeToDelete->next->prev = nodeToDelete->prev;
    }

    // Free the node
    free(nodeToDelete->name);
    free(nodeToDelete->course_year);
    free(nodeToDelete);
    
    return head;
}