#include "job_cycle_details.h" // Our new logic header

// --- MAIN CGI PROGRAM ---
int main(void) {
    struct JobNode *list_head = NULL;
    char *action = NULL;
    cJSON *response_json = NULL;
    cJSON *request_json = NULL;

    // --- 1. Read data from frontend (NEW, CORRECT WAY) ---
    char *content_length_str = getenv("CONTENT_LENGTH");
    if (content_length_str != NULL) {
        int content_length = atoi(content_length_str);
        if (content_length > 0) {
            char *buffer = (char *)malloc(content_length + 1);
            fread(buffer, 1, content_length, stdin);
            buffer[content_length] = '\0';
            request_json = cJSON_Parse(buffer);
            free(buffer);
        }
    }
    // --- END NEW LOGIC ---

    // 2. Find action
    if (request_json != NULL) {
        cJSON *action_item = cJSON_GetObjectItem(request_json, "action");
        if (action_item && cJSON_IsString(action_item)) {
            action = action_item->valuestring;
        }
    }
    
    // --- 3. PERFORM ACTION ---
    
    list_head = load_job_data();

    if (action && strcmp(action, "add") == 0) {
        cJSON *data = cJSON_GetObjectItem(request_json, "data");
        char *company = cJSON_GetObjectItem(data, "company")->valuestring;
        char *role = cJSON_GetObjectItem(data, "role")->valuestring;
        char *status = cJSON_GetObjectItem(data, "status")->valuestring;
        int index = cJSON_GetObjectItem(data, "index")->valueint;
        
        list_head = insert_job_at_index(list_head, company, role, status, index);
        save_job_data(list_head);
        response_json = cJSON_CreateObject();
        cJSON_AddStringToObject(response_json, "status", "success");
        
    } else if (action && strcmp(action, "remove") == 0) {
        cJSON *data = cJSON_GetObjectItem(request_json, "data");
        int index = cJSON_GetObjectItem(data, "index")->valueint;
        
        list_head = delete_job_at_index(list_head, index);
        save_job_data(list_head);
        response_json = cJSON_CreateObject();
        cJSON_AddStringToObject(response_json, "status", "success");
        
    } else if (action && strcmp(action, "update") == 0) {
        cJSON *data = cJSON_GetObjectItem(request_json, "data");
        int index = cJSON_GetObjectItem(data, "index")->valueint;
        char *status = cJSON_GetObjectItem(data, "status")->valuestring;

        update_job_status(list_head, index, status);
        save_job_data(list_head);
        response_json = cJSON_CreateObject();
        cJSON_AddStringToObject(response_json, "status", "success");

    } else if (action && strcmp(action, "preview") == 0) {
        response_json = serialize_job_data(list_head);
    }

    // --- 4. Send Response ---
    printf("Content-Type: application/json\n\n");
    if (response_json) {
        printf("%s\n", cJSON_Print(response_json));
    } else {
        printf("{\"status\":\"error\", \"message\":\"Invalid or missing action\"}\n");
    }

    // --- 5. Clean up ---
    if (request_json) cJSON_Delete(request_json);
    if (response_json) cJSON_Delete(response_json);
    free_job_list(list_head);

    return 0;
}