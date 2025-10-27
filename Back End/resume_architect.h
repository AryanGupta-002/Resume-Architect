#ifndef RESUME_ARCHITECT_H
#define RESUME_ARCHITECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

// Structure for Personal Details (Singly Linked List)
struct PersonalNode {
    char *field;
    char *value;
    struct PersonalNode *next;
};

// Structure for Education Details (Doubly Linked List)
struct EducationNode {
    char *name;         
    char *course_year;  
    float score;        
    struct EducationNode *next;
    struct EducationNode *prev;
};

// Structure for Skills (Queue)
struct SkillNode {
    char *skill;
    struct SkillNode *next;
};

// Structure for Achievements (Stack)
struct AchievementNode {
    char *description;
    struct AchievementNode *next;
};

// Structure for Additional Details (Circular Doubly Linked List)
struct AdditionalNode {
    char *detail;
    struct AdditionalNode *next;
    struct AdditionalNode *prev;
};


// Structure for Job Application Cycle (Circular Singly Linked List)
struct JobNode {
    char *company;
    char *role;
    char *status; // e.g., "Applied", "Interview", "Offer"
    struct JobNode *next;
};


#endif