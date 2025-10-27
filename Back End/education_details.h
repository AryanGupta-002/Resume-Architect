#ifndef EDUCATION_DETAILS_H
#define EDUCATION_DETAILS_H

#include "resume_architect.h"


struct EducationNode* create_education_node(const char *name, const char *course_year, float score);
void free_education_list(struct EducationNode *head);
struct EducationNode* insert_education_at_index(struct EducationNode *head, const char *name, const char *course_year, float score, int index);
struct EducationNode* delete_education_at_index(struct EducationNode *head, int index);


struct EducationNode* load_education_data();
void save_education_data(struct EducationNode *head);
cJSON* serialize_education_data(struct EducationNode *head);

#endif