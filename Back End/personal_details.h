#ifndef PERSONAL_DETAILS_H
#define PERSONAL_DETAILS_H

#include "resume_architect.h" 

struct PersonalNode* create_node(const char *field, const char *value);
void free_list(struct PersonalNode *head);
struct PersonalNode* insert_at_index(struct PersonalNode *head, const char *field, const char *value, int index);
struct PersonalNode* delete_at_index(struct PersonalNode *head, int index);
void update_at_index(struct PersonalNode *head, int index, const char *new_value); // <-- ADD THIS LINE

struct PersonalNode* load_personal_data();
void save_personal_data(struct PersonalNode *head);
cJSON* serialize_personal_data(struct PersonalNode *head);

#endif