#include "resume_architect.h" 

struct JobNode* create_job_node(const char *company, const char *role, const char *status) {
    struct JobNode *newNode = (struct JobNode*)malloc(sizeof(struct JobNode));
    newNode->company = strdup(company);
    newNode->role = strdup(role);
    newNode->status = strdup(status);
    newNode->next = NULL;
    return newNode;
}

// Free circular list
void free_job_list(struct JobNode *head) {
    if (head == NULL) return;

    struct JobNode *current = head;
    struct JobNode *temp;
    
    //tail to break loop
    struct JobNode *tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }
    tail->next = NULL; 
    // turn SLL

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp->company);
        free(temp->role);
        free(temp->status);
        free(temp);
    }
}

// Insert at index
struct JobNode* insert_job_at_index(struct JobNode *head, const char *company, const char *role, const char *status, int index) {
    
    struct JobNode *newNode = create_job_node(company, role, status);

    // List is empty
    if (head == NULL) { 
        newNode->next = newNode; // Points to itself
        return newNode;
    }

    // Insert at head
    if (index == 0) { 
        // Find tail node
        struct JobNode *tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }

        // Link the new node
        newNode->next = head;
        tail->next = newNode;
        return newNode; // new node is new head
    }

    struct JobNode *current = head;
    int i = 0;
    
    // going before insertion point
    while (i < index - 1) {
        current = current->next;
        if (current == head) break; // Looped all the way around
        i++;
    }
    
    // Insert after current
    newNode->next = current->next;
    current->next = newNode;
    
    return head; // Head doesn't change
}

// Delete at index
struct JobNode* delete_job_at_index(struct JobNode *head, int index) {
    if (head == NULL) return NULL;

    struct JobNode *nodeToDelete = head;
    struct JobNode *prev = NULL;

    if (index == 0) { // Delete the head
        // Find the tail
        struct JobNode *tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }
        
        if (head == head->next) { // It's the only node
            free(head->company);
            free(head->role);
            free(head->status);
            free(head);
            return NULL; // List is now empty
        }

        // Relink to new head
        tail->next = head->next;
        nodeToDelete = head; // Mark head for deletion
        head = head->next;   // Set the new head
        
    } else { // Delete from middle or end
        prev = head;
        int i = 0;
        // Find the node *before* the one to delete
        while (i < index - 1) {
            prev = prev->next;
            if (prev == head) return head; // Index out of bounds
            i++;
        }
        
        if (prev->next == head) return head; // Index out of bounds

        nodeToDelete = prev->next;
        prev->next = nodeToDelete->next; // Relink
    }

    // Free the node
    free(nodeToDelete->company);
    free(nodeToDelete->role);
    free(nodeToDelete->status);
    free(nodeToDelete);
    
    return head; // Return the new head
}

// Updates the status of a node at a specific index
void update_job_status(struct JobNode *head, int index, const char *new_status) {
    if (head == NULL) return;

    struct JobNode *current = head;
    int i = 0;
    
    // Traverse to the node *at* the index
    while (i < index) {
        current = current->next;
        if (current == head) return; // Index out of bounds
        i++;
    }
    
    // Free the old status and set the new one
    free(current->status);
    current->status = strdup(new_status);
}