#ifndef JOB_CYCLE_DETAILS_H
#define JOB_CYCLE_DETAILS_H

#include "resume_architect.h"

struct JobNode* create_job_node(const char *company, const char *role, const char *status);
void free_job_list(struct JobNode *head);
struct JobNode* insert_job_at_index(struct JobNode *head, const char *company, const char *role, const char *status, int index);
struct JobNode* delete_job_at_index(struct JobNode *head, int index);
void update_job_status(struct JobNode *head, int index, const char *new_status);

struct JobNode* load_job_data();
void save_job_data(struct JobNode *head);
cJSON* serialize_job_data(struct JobNode *head);

#endif