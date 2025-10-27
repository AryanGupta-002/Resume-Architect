#include "resume_architect.h" 


// Add a skill to the end of the queue
void enqueue(struct SkillNode **head, struct SkillNode **tail, const char *skill) {
    struct SkillNode *newNode = (struct SkillNode*)malloc(sizeof(struct SkillNode));
    newNode->skill = strdup(skill);
    newNode->next = NULL;

    if (*tail == NULL) { // Queue is empty
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

// Removes a skill from the front of the queue

char* dequeue(struct SkillNode **head, struct SkillNode **tail) {
    if (*head == NULL) {
        return NULL; // Queue is empty
    }

    struct SkillNode *temp = *head;
    char *skill_name = strdup(temp->skill);

    *head = (*head)->next;
    if (*head == NULL) { // Queue is now empty
        *tail = NULL;
    }

    free(temp->skill);
    free(temp);
    return skill_name;
}

// Free list
void free_skill_list(struct SkillNode *head) {
    struct SkillNode *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->skill);
        free(tmp);
    }
}

// size of the queue
int get_queue_size(struct SkillNode *head) {
    int count = 0;
    struct SkillNode *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}