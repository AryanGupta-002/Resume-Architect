#include "skills_details.h" // Our new logic header

// --- MAIN CGI PROGRAM ---
int main(void) {
    struct SkillNode *head = NULL;
    struct SkillNode *tail = NULL;
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
    
    load_skills_data(&head, &tail);

    if (action && strcmp(action, "add") == 0) {
        cJSON *data = cJSON_GetObjectItem(request_json, "data");
        char *skill = cJSON_GetObjectItem(data, "skill")->valuestring;
        
        enqueue(&head, &tail, skill);
        save_skills_data(head);
        response_json = cJSON_CreateObject();
        cJSON_AddStringToObject(response_json, "status", "success");
        
    } else if (action && strcmp(action, "remove") == 0) {
        cJSON *data = cJSON_GetObjectItem(request_json, "data");
        int index_to_remove = cJSON_GetObjectItem(data, "index")->valueint;
        
        int queue_size = get_queue_size(head);
        
        for (int i = 0; i < queue_size; i++) {
            char *skill_name = dequeue(&head, &tail);
            if (skill_name == NULL) break; // Safety check
            
            if (i != index_to_remove) {
                enqueue(&head, &tail, skill_name); 
            }
            free(skill_name);
        }
        
        save_skills_data(head);
        response_json = cJSON_CreateObject();
        cJSON_AddStringToObject(response_json, "status", "success");
        
    } else if (action && strcmp(action, "preview") == 0) {
        response_json = serialize_skills_data(head);
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
    free_skill_list(head);

    return 0;
}