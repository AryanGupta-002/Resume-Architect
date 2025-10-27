#include "personal_details.h"

// --- MAIN CGI PROGRAM ---
int main(void) {
    struct PersonalNode *list_head = NULL;
    char *action = NULL;
    cJSON *response_json = NULL;
    cJSON *request_json = NULL; // We'll parse the buffer

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

    list_head = load_personal_data();

    if (action && strcmp(action, "add") == 0) {
        cJSON *data = cJSON_GetObjectItem(request_json, "data");
        char *field = cJSON_GetObjectItem(data, "field")->valuestring;
        char *value = cJSON_GetObjectItem(data, "value")->valuestring;
        int index = cJSON_GetObjectItem(data, "index")->valueint;

        list_head = insert_at_index(list_head, field, value, index);
        save_personal_data(list_head);
        response_json = cJSON_CreateObject();
        cJSON_AddStringToObject(response_json, "status", "success");

    } else if (action && strcmp(action, "remove") == 0) {
        cJSON *data = cJSON_GetObjectItem(request_json, "data");
        int index = cJSON_GetObjectItem(data, "index")->valueint;

        list_head = delete_at_index(list_head, index);
        save_personal_data(list_head);
        response_json = cJSON_CreateObject();
        cJSON_AddStringToObject(response_json, "status", "success");

    } else if (action && strcmp(action, "update") == 0) { // <-- UPDATED BLOCK
        cJSON *data = cJSON_GetObjectItem(request_json, "data");
        int index = cJSON_GetObjectItem(data, "index")->valueint;
        char *value = cJSON_GetObjectItem(data, "value")->valuestring;

        update_at_index(list_head, index, value); // Call the new function
        save_personal_data(list_head);
        response_json = cJSON_CreateObject();
        cJSON_AddStringToObject(response_json, "status", "success");

    } else if (action && strcmp(action, "preview") == 0) {
        response_json = serialize_personal_data(list_head);

    } else if (action && strcmp(action, "init") == 0) {
        if (list_head == NULL) {
            list_head = insert_at_index(list_head, "Name", "", 0);
            list_head = insert_at_index(list_head, "Email", "", 1);
            list_head = insert_at_index(list_head, "Phone", "", 2);
            list_head = insert_at_index(list_head, "LinkedIn", "", 3);
            list_head = insert_at_index(list_head, "GitHub", "", 4);
            list_head = insert_at_index(list_head, "Location", "", 5);
            save_personal_data(list_head);
        }
        response_json = serialize_personal_data(list_head);
    }

    // --- 4. Send Response ---
    printf("Content-Type: application/json\n\n");
    if (response_json) {
        printf("%s\n", cJSON_Print(response_json));
    } else {
        // If action was null or invalid
        printf("{\"status\":\"error\", \"message\":\"Invalid or missing action\"}\n");
    }

    // --- 5. Clean up ---
    if (request_json) cJSON_Delete(request_json);
    if (response_json) cJSON_Delete(response_json);
    free_list(list_head);

    return 0;
}