#ifndef ACHIEVEMENTS_DETAILS_H
#define ACHIEVEMENTS_DETAILS_H

#include "resume_architect.h"

void push(struct AchievementNode **head, const char *description);
char* pop(struct AchievementNode **head); 
void free_stack_list(struct AchievementNode *head);

struct AchievementNode* load_achievements_data();
void save_achievements_data(struct AchievementNode *head);
cJSON* serialize_achievements_data(struct AchievementNode *head);

#endif