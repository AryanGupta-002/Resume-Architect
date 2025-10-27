#ifndef SKILLS_DETAILS_H
#define SKILLS_DETAILS_H

#include "resume_architect.h"


void enqueue(struct SkillNode **head, struct SkillNode **tail, const char *skill);
char* dequeue(struct SkillNode **head, struct SkillNode **tail);
void free_skill_list(struct SkillNode *head);
int get_queue_size(struct SkillNode *head);


void load_skills_data(struct SkillNode **head, struct SkillNode **tail);
void save_skills_data(struct SkillNode *head);
cJSON* serialize_skills_data(struct SkillNode *head);

#endif