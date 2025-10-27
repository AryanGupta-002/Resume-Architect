#include "personal_details.h"

#define DATA_FILE "D:\\Softwares\\Apache Server\\Server\\htdocs\\personal_data.json"

// Loads the list from the JSON file
struct PersonalNode* load_personal_data() {
    FILE *f = fopen(DATA_FILE, "r");
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

    struct PersonalNode *head = NULL;
    struct PersonalNode *current = NULL;
    cJSON *node_json;

    // Loop through the JSON array and build the SLL
    cJSON_ArrayForEach(node_json, json) {
        char *field = cJSON_GetObjectItem(node_json, "field")->valuestring;
        char *value = cJSON_GetObjectItem(node_json, "value")->valuestring;
        
        struct PersonalNode *newNode = create_node(field, value);
        
        if (head == NULL) {
            head = newNode;
            current = head;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    cJSON_Delete(json);
    free(buffer);
    return head;
}

// Saves the list back to the JSON file
void save_personal_data(struct PersonalNode *head) {
    cJSON *root = cJSON_CreateArray(); // Create a JSON ARRAY
    struct PersonalNode *current = head;

    // Loop through the SLL and build the JSON array
    while (current != NULL) {
        cJSON *node_json = cJSON_CreateObject();
        cJSON_AddStringToObject(node_json, "field", current->field);
        cJSON_AddStringToObject(node_json, "value", current->value);
        cJSON_AddItemToArray(root, node_json);
        current = current->next;
    }

    char *json_string = cJSON_Print(root);
    FILE *f = fopen(DATA_FILE, "w");
    fprintf(f, "%s", json_string);
    fclose(f);

    cJSON_Delete(root);
    free(json_string);
}

// Serializes the list to a JSON array (for preview)
cJSON* serialize_personal_data(struct PersonalNode *head) {
    cJSON *root = cJSON_CreateArray();
    struct PersonalNode *current = head;
    while (current != NULL) {
        cJSON *node_json = cJSON_CreateObject();
        cJSON_AddStringToObject(node_json, "field", current->field);
        cJSON_AddStringToObject(node_json, "value", current->value);
        cJSON_AddItemToArray(root, node_json);
        current = current->next;
    }
    return root;
}