#include "achievements_details.h"

#define ACHIEVEMENTS_DATA_FILE "D:\\Softwares\\Apache Server\\Server\\htdocs\\achievements_data.json"

// Loads the list from the JSON file
struct AchievementNode* load_achievements_data() {
    FILE *f = fopen(ACHIEVEMENTS_DATA_FILE, "r");
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

    struct AchievementNode *head = NULL;
    cJSON *node_json;

    // Loop through the JSON array and build the stack

   int array_size = cJSON_GetArraySize(json);
   for (int i = array_size - 1; i >= 0; i--) {
       node_json = cJSON_GetArrayItem(json, i);
       char *description = cJSON_GetObjectItem(node_json, "description")->valuestring;
       push(&head, description); // Push Oldest, then Middle, then Newest
   }


    cJSON_Delete(json);
    free(buffer);
    return head; // Return the top of the stack
}

// Saves the list back to the JSON file
void save_achievements_data(struct AchievementNode *head) {
    cJSON *root = cJSON_CreateArray(); // Create a JSON ARRAY
    struct AchievementNode *current = head;

    // Loop through the stack (SLL) and build the JSON array
    while (current != NULL) {
        cJSON *node_json = cJSON_CreateObject();
        cJSON_AddStringToObject(node_json, "description", current->description);
        cJSON_AddItemToArray(root, node_json);
        current = current->next;
    }
    
    // Note: The file will be saved with the top of the stack at index 0.
    // [Top, Middle, Bottom]

    char *json_string = cJSON_Print(root);
    FILE *f = fopen(ACHIEVEMENTS_DATA_FILE, "w");
    fprintf(f, "%s", json_string);
    fclose(f);

    cJSON_Delete(root);
    free(json_string);
}

// Serializes the list to a JSON array (for preview)
cJSON* serialize_achievements_data(struct AchievementNode *head) {
    cJSON *root = cJSON_CreateArray();
    struct AchievementNode *current = head;
    while (current != NULL) {
        cJSON *node_json = cJSON_CreateObject();
        cJSON_AddStringToObject(node_json, "description", current->description);
        cJSON_AddItemToArray(root, node_json);
        current = current->next;
    }
    return root;
}