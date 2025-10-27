#include "education_details.h"

#define EDUCATION_DATA_FILE "D:\\Softwares\\Apache Server\\Server\\htdocs\\educational_data.json"

// Loads the list from the JSON file
struct EducationNode* load_education_data() {
    FILE *f = fopen(EDUCATION_DATA_FILE, "r");
    if (f == NULL) return NULL; // No file

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
        return NULL;
    }

    struct EducationNode *head = NULL;
    struct EducationNode *current = NULL;
    cJSON *node_json;

    // Loop through the JSON array and build the DLL
    cJSON_ArrayForEach(node_json, json) {
        char *name = cJSON_GetObjectItem(node_json, "name")->valuestring;
        char *course_year = cJSON_GetObjectItem(node_json, "course_year")->valuestring;
        float score = (float)cJSON_GetObjectItem(node_json, "score")->valuedouble;

        struct EducationNode *newNode = create_education_node(name, course_year, score);
        
        if (head == NULL) {
            head = newNode;
            current = head;
        } else {
            current->next = newNode;
            newNode->prev = current;
            current = newNode;
        }
    }

    cJSON_Delete(json);
    free(buffer);
    return head;
}

// Saves the list back to the JSON file
void save_education_data(struct EducationNode *head) {
    cJSON *root = cJSON_CreateArray(); // Create a JSON ARRAY
    struct EducationNode *current = head;

    // Loop through the DLL and build the JSON array
    while (current != NULL) {
        cJSON *node_json = cJSON_CreateObject();
        cJSON_AddStringToObject(node_json, "name", current->name);
        cJSON_AddStringToObject(node_json, "course_year", current->course_year);
        cJSON_AddNumberToObject(node_json, "score", current->score);
        cJSON_AddItemToArray(root, node_json);
        current = current->next;
    }

    char *json_string = cJSON_Print(root);
    FILE *f = fopen(EDUCATION_DATA_FILE, "w");
    fprintf(f, "%s", json_string);
    fclose(f);

    cJSON_Delete(root);
    free(json_string);
}

// Serializes the list to a JSON array (for preview)
cJSON* serialize_education_data(struct EducationNode *head) {
    cJSON *root = cJSON_CreateArray();
    struct EducationNode *current = head;
    while (current != NULL) {
        cJSON *node_json = cJSON_CreateObject();
        cJSON_AddStringToObject(node_json, "name", current->name);
        cJSON_AddStringToObject(node_json, "course_year", current->course_year);
        cJSON_AddNumberToObject(node_json, "score", current->score);
        cJSON_AddItemToArray(root, node_json);
        current = current->next;
    }
    return root;
}