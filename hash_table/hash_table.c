#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Node structure
typedef struct Node {
    char* value;
    struct Node* next;
} Node;

// Define the SLList structure
typedef struct SLList {
    Node* head;
} SLList;

// Function prototypes
Node* create_node(const char* value, Node* next_node);
SLList* create_sllist();
void add_first(SLList* list, const char* x);
int contains(SLList* list, const char* x);
int remove_element(SLList* list, const char* x);

typedef struct {
    int size;
    SLList** array;
    int count;
} di_array;

di_array* create_di_array();
int hash_value(di_array* arr, const char* x);
void add(di_array* arr, const char* x);
void remove_str(di_array* arr, const char* x);
void resize(di_array* arr); // Prototype declaration for resize
int contains_in_array(di_array* arr, const char* x);
void free_di_array(di_array* arr);

// Function to create a new Node
Node* create_node(const char* value, Node* next_node) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = strdup(value);  // Duplicate string for storage
    new_node->next = next_node;
    return new_node;
}

// Function to initialize a new SLList
SLList* create_sllist() {
    SLList* list = (SLList*)malloc(sizeof(SLList));
    list->head = NULL;
    return list;
}

// Function to add a new element at the beginning of the list
void add_first(SLList* list, const char* x) {
    Node* new_node = create_node(x, list->head);
    list->head = new_node;
}

// Returns 1 if x is in the list, 0 otherwise
int contains(SLList* list, const char* x) {
    Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->value, x) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Function to remove an element from the list
int remove_element(SLList* list, const char* x) {
    Node* current = list->head;
    Node* previous = NULL;
    while (current != NULL) {
        if (strcmp(current->value, x) == 0) {
            if (previous == NULL) {  // Removing the head
                list->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current->value);
            free(current);
            return 1;  // Indicate that we removed the item
        }
        previous = current;
        current = current->next;
    }
    return 0;  // Indicate that the item was not found
}

// Function to create a new di_array
di_array* create_di_array() {
    di_array* new_array = (di_array*)malloc(sizeof(di_array));
    new_array->size = 11;
    new_array->array = (SLList**)calloc(new_array->size, sizeof(SLList*));
    new_array->count = 0;
    return new_array;
}

// Function to calculate hash value
int hash_value(di_array* arr, const char* x) {
    int B = 31;
    int ans = 0;
    for (int i = 0; x[i] != '\0'; i++) {
        ans = ans * B + x[i];
    }
    return ans % arr->size;
}

// Function to add a string to the array
void add(di_array* arr, const char* x) {
    if ((float)arr->count / arr->size > 1.5) {
        resize(arr);
    }

    int i = hash_value(arr, x);
    if (arr->array[i] == NULL) {
        arr->array[i] = create_sllist();
    }

    if (!contains(arr->array[i], x)) {  // Avoid duplicates
        add_first(arr->array[i], x);
        arr->count++;
    }
}

// Function to remove a string from the array
void remove_str(di_array* arr, const char* x) {
    int i = hash_value(arr, x);
    if (arr->array[i] != NULL) {
        if (remove_element(arr->array[i], x)) {
            arr->count--;
        }
    }
}

// Function to resize the array
void resize(di_array* arr) {
    SLList** old_array = arr->array;
    int old_size = arr->size;

    arr->size *= 2;
    arr->array = (SLList**)calloc(arr->size, sizeof(SLList*));
    arr->count = 0;

    for (int i = 0; i < old_size; i++) {
        if (old_array[i] != NULL) {
            Node* current = old_array[i]->head;
            while (current != NULL) {
                add(arr, current->value);
                current = current->next;
            }
            free(old_array[i]);
        }
    }
    free(old_array);
}

// Returns 1 if the string is in the array, 0 otherwise
int contains_in_array(di_array* arr, const char* x) {
    int i = hash_value(arr, x);
    if (arr->array[i] != NULL) {
        return contains(arr->array[i], x);
    }
    return 0;
}

// Function to free memory used by di_array
void free_di_array(di_array* arr) {
    for (int i = 0; i < arr->size; i++) {
        if (arr->array[i] != NULL) {
            Node* current = arr->array[i]->head;
            while (current != NULL) {
                Node* next = current->next;
                free(current->value);
                free(current);
                current = next;
            }
            free(arr->array[i]);
        }
    }
    free(arr->array);
    free(arr);
}

// Testing the updated hash table with remove functionality
int main() {
    di_array* A = create_di_array();
    add(A, "22222");
    add(A, "pace!");
    printf("%s\n", contains_in_array(A, "22222") ? "True" : "False");  // True
    printf("%s\n", contains_in_array(A, "hello") ? "True" : "False");  // False

    remove_str(A, "22222");
    printf("%s\n", contains_in_array(A, "22222") ? "True" : "False");  // False, since it was removed

    remove_str(A, "pace!");
    printf("%s\n", contains_in_array(A, "pace!") ? "True" : "False");  // False, since it was removed

    // Free the memory
    free_di_array(A);

    return 0;
}