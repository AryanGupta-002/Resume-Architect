#ifndef ADDITIONAL_DETAILS_H
#define ADDITIONAL_DETAILS_H

#include "resume_architect.h" 

struct AdditionalNode* create_additional_node(const char *detail);
void free_additional_list(struct AdditionalNode *head);
struct AdditionalNode* insert_additional_at_index(struct AdditionalNode *head, const char *detail, int index);
struct AdditionalNode* delete_additional_at_index(struct AdditionalNode *head, int index);

struct AdditionalNode* load_additional_data();
void save_additional_data(struct AdditionalNode *head);
cJSON* serialize_additional_data(struct AdditionalNode *head);

#endif