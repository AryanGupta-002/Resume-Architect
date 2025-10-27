#include "additional_details.h"

#define ADDITIONAL_DATA_FILE "D:\\Softwares\\Apache Server\\Server\\htdocs\\additional_data.json"

// Loads the list from the JSON file
struct AdditionalNode* load_additional_data() {
    FILE *f = fopen(ADDITIONAL_DATA_FILE, "r");
    if (f == NULL) return NULL; // No file

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = (char*)malloc(len + 1);
    fread(buffer, 1, len, f);
    fclose(f);
    buffer[len] = '\0';

    cJSON *json = cJSON_Parse(buffer);
    if (!cJSON_IsArray(json)) {
        cJSON_Delete(json);
        free(buffer);
        return NULL;
    }

    struct AdditionalNode *head = NULL;
    struct AdditionalNode *current = NULL;
    struct AdditionalNode *tail = NULL;
    cJSON *node_json;

    // Loop through the JSON array and build a *normal* DLL first
    cJSON_ArrayForEach(node_json, json) {
        char *detail = cJSON_GetObjectItem(node_json, "detail")->valuestring;
        
        struct AdditionalNode *newNode = create_additional_node(detail);
        
        if (head == NULL) {
            head = newNode;
            current = head;
        } else {
            current->next = newNode;
            newNode->prev = current;
            current = newNode;
        }
    }
    
    // Now, link the head and tail to make it circular
    if (head != NULL) {
        tail = current; // The last node we processed
        tail->next = head;
        head->prev = tail;
    }

    cJSON_Delete(json);
    free(buffer);
    return head;
}

// Saves the list back to the JSON file
void save_additional_data(struct AdditionalNode *head) {
    cJSON *root = cJSON_CreateArray(); // Create a JSON ARRAY
    
    if (head != NULL) {
        struct AdditionalNode *current = head;
        
        // Use a do-while loop to handle the circular list
        do {
            cJSON *node_json = cJSON_CreateObject();
            cJSON_AddStringToObject(node_json, "detail", current->detail);
            cJSON_AddItemToArray(root, node_json);
            current = current->next;
        } while (current != head); // Stop when we get back to the start
    }

    char *json_string = cJSON_Print(root);
    FILE *f = fopen(ADDITIONAL_DATA_FILE, "w");
    fprintf(f, "%s", json_string);
    fclose(f);

    cJSON_Delete(root);
    free(json_string);
}

// Serializes the list to a JSON array (for preview)
cJSON* serialize_additional_data(struct AdditionalNode *head) {
    cJSON *root = cJSON_CreateArray();
    
    if (head != NULL) {
        struct AdditionalNode *current = head;
        
        // Use a do-while loop to handle the circular list
        do {
            cJSON *node_json = cJSON_CreateObject();
            cJSON_AddStringToObject(node_json, "detail", current->detail);
            cJSON_AddItemToArray(root, node_json);
            current = current->next;
        } while (current != head); // Stop when we get back to the start
    }
    
    return root;
}