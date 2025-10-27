#include "skills_details.h"

#define SKILLS_DATA_FILE "D:\\Softwares\\Apache Server\\Server\\htdocs\\skills_data.json"

// Loads the list from the JSON file
// Note: This function now modifies head and tail pointers
void load_skills_data(struct SkillNode **head, struct SkillNode **tail) {
    FILE *f = fopen(SKILLS_DATA_FILE, "r");
    if (f == NULL) {
        *head = NULL;
        *tail = NULL;
        return;
    }

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = (char*)malloc(len + 1);
    fread(buffer, 1, len, f);
    fclose(f);
    buffer[len] = '\0';

    cJSON *json = cJSON_Parse(buffer);
    if (!cJSON_IsArray(json)) { // We expect an ARRAY
        cJSON_Delete(json);
        free(buffer);
        *head = NULL;
        *tail = NULL;
        return;
    }

    *head = NULL;
    *tail = NULL;
    cJSON *node_json;

    // Loop through the JSON array and build the queue using enqueue
    cJSON_ArrayForEach(node_json, json) {
        char *skill = cJSON_GetObjectItem(node_json, "skill")->valuestring;
        enqueue(head, tail, skill); // This correctly builds the list
    }

    cJSON_Delete(json);
    free(buffer);
}

// Saves the list back to the JSON file
void save_skills_data(struct SkillNode *head) {
    cJSON *root = cJSON_CreateArray(); // Create a JSON ARRAY
    struct SkillNode *current = head;

    // Loop through the list and build the JSON array
    while (current != NULL) {
        cJSON *node_json = cJSON_CreateObject();
        cJSON_AddStringToObject(node_json, "skill", current->skill);
        cJSON_AddItemToArray(root, node_json);
        current = current->next;
    }

    char *json_string = cJSON_Print(root);
    FILE *f = fopen(SKILLS_DATA_FILE, "w");
    fprintf(f, "%s", json_string);
    fclose(f);

    cJSON_Delete(root);
    free(json_string);
}

// Serializes the list to a JSON array (for preview)
cJSON* serialize_skills_data(struct SkillNode *head) {
    cJSON *root = cJSON_CreateArray();
    struct SkillNode *current = head;
    while (current != NULL) {
        cJSON *node_json = cJSON_CreateObject();
        cJSON_AddStringToObject(node_json, "skill", current->skill);
        cJSON_AddItemToArray(root, node_json);
        current = current->next;
    }
    return root;
}