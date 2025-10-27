#include "job_cycle_details.h" 

#define JOB_DATA_FILE "D:\\Softwares\\Apache Server\\Server\\htdocs\\job_cycle_data.json"

// Loads the list from the JSON file
struct JobNode* load_job_data() {
    FILE *f = fopen(JOB_DATA_FILE, "r");
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

    struct JobNode *head = NULL;
    struct JobNode *current = NULL;
    struct JobNode *tail = NULL;
    cJSON *node_json;

    // Loop through the JSON array and build a *normal* SLL first
    cJSON_ArrayForEach(node_json, json) {
        char *company = cJSON_GetObjectItem(node_json, "company")->valuestring;
        char *role = cJSON_GetObjectItem(node_json, "role")->valuestring;
        char *status = cJSON_GetObjectItem(node_json, "status")->valuestring;
        
        struct JobNode *newNode = create_job_node(company, role, status);
        
        if (head == NULL) {
            head = newNode;
            current = head;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }
    
    // Now, link the head and tail to make it circular
    if (head != NULL) {
        tail = current; // The last node we processed
        tail->next = head;
    }

    cJSON_Delete(json);
    free(buffer);
    return head;
}

// Saves the list back to the JSON file
void save_job_data(struct JobNode *head) {
    cJSON *root = cJSON_CreateArray(); // Create a JSON ARRAY
    
    if (head != NULL) {
        struct JobNode *current = head;
        
        // Use a do-while loop to handle the circular list
        do {
            cJSON *node_json = cJSON_CreateObject();
            cJSON_AddStringToObject(node_json, "company", current->company);
            cJSON_AddStringToObject(node_json, "role", current->role);
            cJSON_AddStringToObject(node_json, "status", current->status);
            cJSON_AddItemToArray(root, node_json);
            current = current->next;
        } while (current != head); // Stop when we get back to the start
    }

    char *json_string = cJSON_Print(root);
    FILE *f = fopen(JOB_DATA_FILE, "w");
    fprintf(f, "%s", json_string);
    fclose(f);

    cJSON_Delete(root);
    free(json_string);
}

// Serializes the list to a JSON array (for preview)
cJSON* serialize_job_data(struct JobNode *head) {
    cJSON *root = cJSON_CreateArray();
    
    if (head != NULL) {
        struct JobNode *current = head;
        
        do {
            cJSON *node_json = cJSON_CreateObject();
            cJSON_AddStringToObject(node_json, "company", current->company);
            cJSON_AddStringToObject(node_json, "role", current->role);
            cJSON_AddStringToObject(node_json, "status", current->status);
            cJSON_AddItemToArray(root, node_json);
            current = current->next;
        } while (current != head);
    }
    
    return root;
}