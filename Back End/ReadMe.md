All the C backend files<br>
with CJSON LIBRARY FILES<br>
all DATA STRUCTURE logic and fucnctions FILES<br>
all the section with C file and H file<br>
all the WEB SERVER FILES<br>

DETAILs<br>
<br>
### ## 0. Shared Files (Used by all sections)<br>

* **`resume_architect.h`**: The master header file defining all data structures and including standard libraries.<br>
* **`cJSON.c`**: The JSON parsing library source code.<br>
* **`cJSON.h`**: The JSON parsing library header file.<br>

### ## 1. Personal Details (Singly Linked List)<br>
<br>
* **`singlylinkedlist.c`**: Contains the generic SLL functions (`create_node`, `insert_at_index`, `delete_at_index`, `update_at_index`, `free_list`).<br>
* **`personal_details.h`**: Declares the specific functions for loading, saving, and serializing personal data, plus the SLL prototypes.<br>
* **`personal_details.c`**: Defines the `load_personal_data`, `save_personal_data`, and `serialize_personal_data` functions.<br>
* **`personal.c`**: The main CGI endpoint program (`personal.exe`) that handles web requests for this section.<br>

### ## 2. Education (Doubly Linked List)<br>
<br>
* **`doublylinkedlist.c`**: Contains the generic DLL functions (`create_education_node`, `insert_education_at_index`, `delete_education_at_index`, `free_education_list`).<br>
* **`education_details.h`**: Declares the specific functions for loading, saving, and serializing education data, plus the DLL prototypes.<br>
* **`education_details.c`**: Defines the `load_education_data`, `save_education_data`, and `serialize_education_data` functions.<br>
* **`education.c`**: The main CGI endpoint program (`education.exe`).<br>

### ## 3. Skills (Queue using SLL)<br>
<br>
* **`queue.c`**: Contains the generic queue functions (`enqueue`, `dequeue`, `free_skill_list`, `get_queue_size`).<br>
* **`skills_details.h`**: Declares the specific functions for loading, saving, and serializing skills data, plus the queue prototypes.<br>
* **`skills_details.c`**: Defines the `load_skills_data`, `save_skills_data`, and `serialize_skills_data` functions.<br>
* **`skills.c`**: The main CGI endpoint program (`skills.exe`).<br>

### ## 4. Achievements (Stack using SLL)<br>
<br>
* **`stack.c`**: Contains the generic stack functions (`push`, `pop`, `free_stack_list`).<br>
* **`achievements_details.h`**: Declares the specific functions for loading, saving, and serializing achievements data, plus the stack prototypes.<br>
* **`achievements_details.c`**: Defines the `load_achievements_data`, `save_achievements_data`, and `serialize_achievements_data` functions.<br>
* **`achievements.c`**: The main CGI endpoint program (`achievements.exe`).<br>

### ## 5. Additional Details (Circular Doubly Linked List)<br>
<br>
* **`circulardoublylinkedlist.c`**: Contains the generic CDLL functions (`create_additional_node`, `insert_additional_at_index`, `delete_additional_at_index`, `free_additional_list`).<br>
* **`additional_details.h`**: Declares the specific functions for loading, saving, and serializing additional data, plus the CDLL prototypes.<br>
* **`additional_details.c`**: Defines the `load_additional_data`, `save_additional_data`, and `serialize_additional_data` functions.<br>
* **`additional.c`**: The main CGI endpoint program (`additional.exe`).<br>

### ## 6. Job Application Cycle (Circular Singly Linked List)<br>
<br>
* **`circularsinglylinkedlist.c`**: Contains the generic CSLL functions (`create_job_node`, `insert_job_at_index`, `delete_job_at_index`, `update_job_status`, `free_job_list`).<br>
* **`job_cycle_details.h`**: Declares the specific functions for loading, saving, and serializing job cycle data, plus the CSLL prototypes.<br>
* **`job_cycle_details.c`**: Defines the `load_job_data`, `save_job_data`, and `serialize_job_data` functions.<br>
* **`job_cycle.c`**: The main CGI endpoint program (`job_cycle.exe`).<br>
