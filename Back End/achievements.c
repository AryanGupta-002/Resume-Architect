#include "achievements_details.h" // Our new logic header

// --- MAIN CGI PROGRAM ---
int main(void) {
    struct AchievementNode *list_head = NULL;
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
    
    list_head = load_achievements_data();

    if (action && strcmp(action, "add") == 0) {
        cJSON *data = cJSON_GetObjectItem(request_json, "data");
        char *description = cJSON_GetObjectItem(data, "description")->valuestring;
        
        push(&list_head, description);
        save_achievements_data(list_head);
        response_json = cJSON_CreateObject();
        cJSON_AddStringToObject(response_json, "status", "success");
        
    } else if (action && strcmp(action, "remove") == 0) {
        cJSON *data = cJSON_GetObjectItem(request_json, "data");
        int index_to_remove = cJSON_GetObjectItem(data, "index")->valueint;
        
        struct AchievementNode *temp_stack = NULL;
        char *popped_desc = NULL;
        
        for (int i = 0; i < index_to_remove; i++) {
            popped_desc = pop(&list_head);
            if (popped_desc == NULL) break;
            push(&temp_stack, popped_desc);
            free(popped_desc);
        }

        popped_desc = pop(&list_head);
        if (popped_desc != NULL) {
            free(popped_desc);
        }

        while ( (popped_desc = pop(&temp_stack)) != NULL ) {
            push(&list_head, popped_desc);
            free(popped_desc);
        }
        
        save_achievements_data(list_head);
        response_json = cJSON_CreateObject();
        cJSON_AddStringToObject(response_json, "status", "success");
        
    } else if (action && strcmp(action, "preview") == 0) {
        response_json = serialize_achievements_data(list_head);
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
    free_stack_list(list_head);

    return 0;
}