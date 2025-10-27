#include "resume_architect.h"


// Push, top of the stack
void push(struct AchievementNode **head, const char *description) {
    struct AchievementNode *newNode = (struct AchievementNode*)malloc(sizeof(struct AchievementNode));
    newNode->description = strdup(description);
    
    // new node point old head
    newNode->next = *head;
    
    // new node become new head
    *head = newNode;
}

// Pops top off the stack
char* pop(struct AchievementNode **head) {
    if (*head == NULL) {
        return NULL; // Stack empty
    }

    // Saving node to delete
    struct AchievementNode *temp = *head;
    
    // to return
    char *description = strdup(temp->description);
    
    // Move head pointer to next node
    *head = (*head)->next;
    
    // Free old head
    free(temp->description);
    free(temp);
    
    // Return 
    return description;
}

// Free entire stack
void free_stack_list(struct AchievementNode *head) {
    struct AchievementNode *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->description);
        free(tmp);
    }
}